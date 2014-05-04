#include <boost/asio.hpp>

#include "status_request_handler.h"
#include "volume_loader_handler.h"
#include "volume_renderer_handler.h"
#include "mpr_handler.h"
#include "volume_manager.h"
#include "volume_loader.h"
#include "loaded_volumes_handler.h"
#include "log.h"


#include "../http_server/server.hpp"
#include "../http_server/file_request_handler.hpp"


#include <boost/bind.hpp>
#include <boost/predef.h>
#include <boost/filesystem.hpp>


#include <iostream>
#include <string>

//#include "system_status.h"

namespace fs = boost::filesystem;

void start(const char* address, const char* port, const char* dicomVolumeRoot, const char* volumeRoot, const char* documentRoot)
{
    LINFO << "Server Root: http://" << address << ":" << port;
    LINFO << "DICOM Volume Root: " << dicomVolumeRoot;
    LINFO << "Volume Root: " << volumeRoot;
    LINFO << "Document Root: " << documentRoot;
    
    // configure the system
    //image_data_service::system_status::instance();
    image_data_service::volume_manager::instance().volume_root(volumeRoot);
    image_data_service::volume_manager::instance().dicom_volume_root(dicomVolumeRoot);
    
    // create, configure and register all request handlers
    http::server::file_request_handler frh(documentRoot);
    http::server::request_router::register_handler("/web", &frh);
    
    image_data_service::status_request_handler srh;
    http::server::request_router::register_handler("/status", &srh);
    
    image_data_service::volume_loader_handler vlh;
    http::server::request_router::register_handler("/volumeLoader", &vlh);
    
    image_data_service::volume_renderer_handler vrh;
    http::server::request_router::register_handler("/volumeRenderer", &vrh);
    
    image_data_service::mpr_handler mh;
    http::server::request_router::register_handler("/mpr", &mh);
    
    image_data_service::loaded_volumes_handler lvh;
    http::server::request_router::register_handler("/loadedVolumes", &lvh);

    
    image_data_service::volume_manager::instance().get("volume3");
    //image_data_service::volume_manager::instance().get("volume1");
    
    // create the http server and run it until stopped
    try {
		http::server::server s(address, port);
		s.run();
	}
	catch(...) 
	{
		std::cout << "unhandled exception caught, terminating process" << endl;
	}
}

static std::string get_data_directory(std::string directory_name)
{
#if BOOST_OS_WINDOWS == 1
    std::string dataRoot = "c:\\ProgramData\\Cornerstone\\VisualizationService";
#else
    std::string dataRoot = "/var/lib/CornerstoneVisualizationService";
#endif
    fs::path data_directory(dataRoot);
    data_directory += directory_name;
    boost::filesystem::create_directory(data_directory);
    return data_directory.string();
}

static std::string get_document_directory()
{
#if BOOST_OS_WINDOWS == 1
	return "C:/src/GitHub/cornerstoneVisualization/src/image_data_service";
#else
	return "/Users/chafey/src/cornerstoneVisualization/src/image_data_service";
#endif
}


int main(int argc, char** argv)
{
    LINFO << "*********************************";
    LINFO << "Cornerstone Visualization Service";
    LINFO << "*********************************";
    LINFO << "Usage: " << argv[0] << " <address> <port> <dicom_volume_root> <volume_root> <doc_root>";
    
    boost::filesystem::path full_path( boost::filesystem::current_path() );
    LINFO << "Current Path: " << full_path;
    
	vtkObject::GlobalWarningDisplayOff();

    try
    {
        if (argc != 5)
        {
            std::string dicomVolumeRoot = get_data_directory("/DICOMVolumes");
            std::string volumeRoot = get_data_directory("/VolumeCache");
			std::string documentRoot(get_document_directory());
			
            start("0.0.0.0", "8080", dicomVolumeRoot.c_str(), volumeRoot.c_str(), documentRoot.c_str());
        }
        else
        {
            start(argv[1], argv[2], argv[3], argv[4], argv[5]);
        }
    }
    catch (std::exception& e)
    {
        LFATAL << "exception: " << e.what() << "\n";
    }
    
    return 0;
}
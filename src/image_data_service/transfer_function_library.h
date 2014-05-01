//
//  transfer_function_library.h
//  cornerstoneVisualizationService
//
//  Copyright (c) 2014 Chris Hafey
//

#ifndef __cornerstoneVisualizationService__transfer_function_library__
#define __cornerstoneVisualizationService__transfer_function_library__

// headers from this project
#include "transfer_function.h"
// headers from other projects
// headers from vtk
// headers from boost
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
// headers from stdlib
#include <string>
#include <map>
// forward declarations


namespace image_data_service {
    
    class transfer_function_library : boost::noncopyable
    {
    public:
        
        static transfer_function_library& instance();
        
        const boost::shared_ptr<transfer_function> get(const std::string& name);

        void add(boost::shared_ptr<transfer_function> tf);
                
    private:
        transfer_function_library();
        
        std::map<std::string, boost::shared_ptr<transfer_function> > transferFunctions_;

    };
    
} // namespace image_data_service


#endif /* defined(__cornerstoneVisualizationService__transfer_function_library__) */


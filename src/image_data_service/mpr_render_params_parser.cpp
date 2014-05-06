#include "mpr_render_params_parser.h"

// include headers from this project
#include "string_helper.h"

// include headers from other projects
#include "../http_server/hef_uri_syntax.hpp"
#include "../http_server/query_parser.hpp"
// include vtk headers
// include boost headers
#include <boost/lexical_cast.hpp>
// include stdlib headers
#include <map>

namespace image_data_service {
    
    mpr_render_params mpr_render_params_parser::from_uri(const std::string& uriString)
    {
        mpr_render_params result;
        
        hef::HfURISyntax uri(uriString);
        std::string query = uri.getQuery();
        std::map<std::string, std::string> parameters = http::server::query_parser::parse(query);
        
        result.volumeId = parameters.count("volumeId") ?
            parameters["volumeId"] : result.volumeId;
        if(parameters.count("axes_direction_cosines")) {
            string_helper::extract_doubles(parameters["axes_direction_cosines"], result.axes_direction_cosines);
        }
        if(parameters.count("reslice_axes_origin")) {
            string_helper::extract_doubles(parameters["reslice_axes_origin"], result.reslice_axes_origin);
        }
        result.blend_mode = parameters.count("blend_mode") ?
            boost::lexical_cast<int>(parameters["blend_mode"]) : result.blend_mode;
        result.window_width = parameters.count("window_width") ?
            boost::lexical_cast<int>(parameters["window_width"]) : result.window_width;
        result.window_level = parameters.count("window_level") ?
            boost::lexical_cast<int>(parameters["window_level"]) : result.window_level;
        result.slab_thickness = parameters.count("slab_thickness") ?
            boost::lexical_cast<double>(parameters["slab_thickness"]) : result.slab_thickness;
        result.slab_resolution = parameters.count("slab_resolution") ?
            boost::lexical_cast<double>(parameters["slab_resolution"]) : result.slab_resolution;

        result.viewport_height = parameters.count("viewport_height") ?
            boost::lexical_cast<int>(parameters["viewport_height"]) : result.viewport_height;
        result.viewport_width = parameters.count("viewport_width") ?
            boost::lexical_cast<int>(parameters["viewport_width"]) : result.viewport_width;
        result.interpolation_mode = parameters.count("interpolation_mode") ?
            boost::lexical_cast<int>(parameters["interpolation_mode"]) : result.interpolation_mode;
        result.background_level = parameters.count("background_level") ?
            boost::lexical_cast<double>(parameters["background_level"]) : result.background_level;

        result.image_type = parameters.count("image_type") ?
            boost::lexical_cast<int>(parameters["image_type"]) : result.image_type;
        result.jpeg_quality = parameters.count("jpeg_quality") ?
            boost::lexical_cast<int>(parameters["jpeg_quality"]) : result.jpeg_quality;
        result.png_compression_level = parameters.count("png_compression_level") ?
            boost::lexical_cast<int>(parameters["png_compression_level"]) : result.png_compression_level;
        result.jpeg_progressive = parameters.count("jpeg_progressive") ?
            boost::lexical_cast<int>(parameters["jpeg_progressive"]) : result.jpeg_progressive;
        
        return result;
    }
    
    
} // namespace image_data_service


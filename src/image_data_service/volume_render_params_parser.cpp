#include "stdafx.h"
#include "volume_render_params_parser.h"
// include headers from this project

// include headers from other projects
#include "../http_server/hef_uri_syntax.hpp"
#include "../http_server/query_parser.hpp"

// include vtk headers

// include boost headers
#include <boost/lexical_cast.hpp>
#include <boost/timer/timer.hpp>

// include stdlib headers

namespace image_data_service {
    
    
    volume_render_params volume_render_params_parser::from_uri(const std::string& uriString)
    {
        volume_render_params result;
        
        hef::HfURISyntax uri(uriString);
        std::string query = uri.getQuery();
        std::map<std::string, std::string> parameters = http::server::query_parser::parse(query);
        
        result.volumeId = parameters.count("volumeId") ?
			parameters["volumeId"] : result.volumeId;
        result.matrix = parameters.count("matrix") ?
			parameters["matrix"] : result.matrix;
        result.blend_mode = parameters.count("blend_mode") ?
			boost::lexical_cast<int>(parameters["blend_mode"]) : result.blend_mode;
        result.transfer_function_name = parameters.count("transfer_function_name") ?
			boost::lexical_cast<std::string>(parameters["transfer_function_name"]) : result.transfer_function_name;
        result.projection_type = parameters.count("projection_type") ?
			boost::lexical_cast<int>(parameters["projection_type"]) : result.projection_type;
        result.window_width = parameters.count("window_width") ?
			boost::lexical_cast<int>(parameters["window_width"]) : result.window_width;
        result.window_level = parameters.count("window_level") ?
			boost::lexical_cast<int>(parameters["window_level"]) : result.window_level;
        result.render_engine = parameters.count("render_engine") ?
			boost::lexical_cast<int>(parameters["render_engine"]) : result.render_engine;
		
        result.desired_update_rate = parameters.count("desired_update_rate") ?
			boost::lexical_cast<double>(parameters["desired_update_rate"]) : result.desired_update_rate;
        result.viewport_height = parameters.count("viewport_height") ?
			boost::lexical_cast<double>(parameters["viewport_height"]) : result.viewport_height;
        result.viewport_width = parameters.count("viewport_width") ?
			boost::lexical_cast<double>(parameters["viewport_width"]) : result.viewport_width;
        result.interpolation_type = parameters.count("interpolation_type") ?
			boost::lexical_cast<int>(parameters["interpolation_type"]) : result.interpolation_type;
        
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


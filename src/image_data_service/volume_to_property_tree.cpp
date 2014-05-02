#include "volume_to_property_tree.h"
// include headers from this project
#include "volume.h"
#include "json_property_tree.h"

// include headers from other projects
// include vtk headers
// include boost headers
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
// include stdlib headers

using boost::property_tree::ptree;
using image_data_service::json_property_tree::put;

namespace image_data_service {
    
    boost::property_tree::ptree volume_to_property_tree::from(volume& vol)
    {
        boost::property_tree::ptree pt;
        int dims[3];
        vol.image_data()->GetDimensions(dims);
        put(pt, "dimensions.x", dims[0]);
        put(pt, "dimensions.y", dims[1]);
        put(pt, "dimensions.z", dims[2]);
        
        double spacing[3];
        vol.image_data()->GetSpacing(spacing);
        put(pt, "spacing.x", spacing[0]);
        put(pt, "spacing.y", spacing[1]);
        put(pt, "spacing.z", spacing[2]);

        put(pt, "size.x", spacing[0] * dims[0]);
        put(pt, "size.x", spacing[1] * dims[1]);
        put(pt, "size.z", spacing[2] * dims[2]);

        put(pt, "dataType", vol.image_data()->GetScalarType());
        put(pt, "actualMemorySizeKB", vol.image_data()->GetActualMemorySize());
        put(pt, "volumeId", vol.volumeId);
        
        return pt;
    }
    
    
    
} // namespace image_data_service


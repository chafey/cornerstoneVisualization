#include "stdafx.h"
#include "matrix_parser.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
#include <boost/lexical_cast.hpp>
// include stdlib headers

namespace image_data_service {
    
    
    vtkSmartPointer<vtkMatrix4x4> matrix_parser::from_string(const std::string& str)
    {
        
        vtkSmartPointer<vtkMatrix4x4> result = vtkSmartPointer<vtkMatrix4x4>::New();
        
        std::string s = str;
        std::string delimiter = ",";
        
        int index = 0;
        
        size_t pos = 0;
        std::string numStr;
        while ((pos = s.find(delimiter)) != std::string::npos) {
            numStr = s.substr(0, pos);
            int j = index / 4;
            int i = index % 4;
            double num = boost::lexical_cast<double>(numStr);
            result->SetElement(i, j, num);
            index++;
            s.erase(0, pos + delimiter.length());
        }
        result->SetElement(3, 3, boost::lexical_cast<double>(s));
        
        return result;
    }

    
    
} // namespace image_data_service


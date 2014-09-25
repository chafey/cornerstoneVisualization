#include "stdafx.h"
#include "transfer_function_library.h"
// include headers from this project
// include headers from other projects
// include vtk headers
// include boost headers
// include stdlib headers
#include <map>

namespace image_data_service {
    
    
    static transfer_function_library* _singleton;
    
    
    static boost::shared_ptr<transfer_function> make_high_contrast()
    {
        boost::shared_ptr<transfer_function> tf(new transfer_function("high contrast"));
        tf->opacity()->AddPoint(0.0, 0.0);
        tf->opacity()->AddPoint(011, 0.0);
        tf->opacity()->AddPoint(202.0, 0.027);
        tf->opacity()->AddPoint(420.0, 0.133);
        tf->opacity()->AddPoint(570, 0.682);
        
        tf->color()->AddRGBPoint(0.0, 0.0, 0.0, 0.0);
        tf->color()->AddRGBPoint(072.0, 0.5, 0.0, 0.0);
        tf->color()->AddRGBPoint(240.0, 1.0, 0.0, 0.0);
        tf->color()->AddRGBPoint(420.0, 1.0, 1.0, 0.0);
        tf->color()->AddRGBPoint(570.0, 1.0, 1.0, 1.0);
        return tf;
    }
    
    static boost::shared_ptr<transfer_function> make_mip()
    {
        boost::shared_ptr<transfer_function> mip(new transfer_function("mip"));
        
        mip->opacity()->AddPoint(0.0, 0.0);
        mip->opacity()->AddPoint(-1024, 1.0);
        mip->opacity()->AddPoint(3096, 1.0);
        
        mip->color()->AddRGBPoint(-1024, 0.0, 0.0, 0.0);
        mip->color()->AddRGBPoint(500, 1.0, 1.0, 1.0);
        return mip;
    }
    
    transfer_function_library& transfer_function_library::instance()
    {
        if(_singleton == 0) {
            _singleton = new transfer_function_library();
        }
        return *_singleton;
    }

    transfer_function_library::transfer_function_library()
    {
        add(make_high_contrast());
        add(make_mip());
    }
    

    
    void transfer_function_library::add(boost::shared_ptr<transfer_function> tf)
    {
        transferFunctions_[tf->name()] = tf;
    }
    
    const boost::shared_ptr<transfer_function> transfer_function_library::get(const std::string& name)
    {
        return transferFunctions_[name];
    }
   
    
} // namespace image_data_service


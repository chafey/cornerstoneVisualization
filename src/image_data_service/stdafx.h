
#pragma warning(disable:4503)

#pragma warning(push)
#pragma warning(disable:4267)

#include <string>
#include <map>
#include <vector>
#include <iostream>


#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <boost/date_time/local_time/local_time.hpp>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/predef.h>
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>


#include <vtkSmartPointer.h>
#include <vtkImageSlabReslice.h>
#include <vtkRenderer.h>
#include <vtkLookupTable.h>
#include <vtkImageMapToColors.h>
#include <vtkImageActor.h>
#include <vtkRenderWindow.h>
#include <vtkPiecewiseFunction.h>
#include <vtkColorTransferFunction.h>
#include <vtkImageData.h>
#include <vtkMatrix4x4.h>
#include <vtkWindowToImageFilter.h>


#include "../../external/easylogging++.h"

#pragma warning(pop)
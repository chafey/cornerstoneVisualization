Cornerstone Visualization Service
=================================

The Cornerstone Visualization Service provides 3D rendering capabilities for
volumetric medical image data sets such as CT, MRI and PET.  The service is intended
to be run on a server and receives incoming rendering requests via HTTP requests and returns
rendered images in PNG or JPEG formats.  The server currently supports both volume renderering
and MPR.

Live Examples
---------------

The best way to see the power of this library is to actually see it in use.

http://lurydemo.hopto.org:8080/web/

Building on Windows 7x64 with Visual Studio 2013
-------------------------------------------------

Install the following dependencies:

* [CMake](http://cmake.org/) 
  * Download the MSI installer (I used 2.8.12.2)
* [boost](http://www.boost.org/) 
  * Download the boost distribution from [here](http://sourceforge.net/projects/boost/files/boost/1.56.0/boost_1_56_0.zip/download) and unzip to C:/local/boost_1_56_0
  * Download the precompiled binaries from [here](http://boost.teeks99.com/bin/1.56.0/boost_1_56_0-msvc-12.0-64.exe) and install to the default directory (C:/local/boost_1_56_0).  
* [vtk](http://www.vtk.org/) 
  * Download the source from [here](http://www.vtk.org/VTK/resources/software.html)
  * Generate the project using cmake for the Visual Studio 2013 x64 configuration 
  * Open the generated solution using visual studio 2013
  * Fix the bug reported [here](http://www.paraview.org/Bug/view.php?id=14971)
  * Build both the debug and release builds (I used 6.1.0 with the source in C:\src\VTK-6.1.0 and the build directory C:\src\VTK-bin)
* [node.js] 
  * Download and run the installer from [here](http://www.nodejs.org) (I used 0.10.28)

Add the VTK and boost DLL's to your path:
C:\local\boost_1_56_0\lib64-msvc-12.0;C:\src\VTK-bin\bin\Release

Add the following environment variables to help CMake find boost:
* Boost_DIR = C:\local\boost_1_56_0
* Boost_INCLUDE_DIR = C:\local\boost_1_56_0
* BOOST_LIBRARYDIR = C:\local\boost_1_56_0\lib64-msvc-12.0
* BOOST_ROOT = C:\local\boost_1_56_0

Open a NODE.JS window and install the following node.js based dependencies for the web component

* [grunt-cli] (https://github.com/gruntjs/grunt-cli) npm install -g grunt-cli
* [bower] (http://bower.io/) npm install -g bower

Initialize the web component

> cd src/image_data_service/web

> bower install

Create a build directory and run cmake to generate an Visual Studio 2010 project

> cd ../../..

> mkdir build

> cd build

> cmake -G "Visual Studio 12 Win64" ..

Open the CMake generated Visual Studio project from build/cornerstoneVisualizationService.sln and build image_data_service

Create the data directory

> mkdir c:\ProgramData/Cornerstone/VisualizationService

Building on Mac OS X Mavericks with XCode 5
-------------------------------------------

Install the following dependencies or install via [homebrew](http://brew.sh/) on Mac OS X:

* [CMake](http://cmake.org/) brew install cmake
* [boost](http://www.boost.org/) brew install boost
* [vtk](http://www.vtk.org/) brew install vtk
* [node.js] (http://www.nodejs.org) brew install node

Install the following node.js based dependencies for the web component

* [grunt-cli] (https://github.com/gruntjs/grunt-cli) npm install -g grunt-cli
* [bower] (http://bower.io/) npm install -g bower

Initialize the web component

> cd src/image_data_service/web

> bower install

Create a build directory and run cmake to generate an XCode project

> cd ../../..

> mkdir build

> cd build

> cmake -G Xcode ..

Open the CMake generated XCode project from build/cornerstoneVisualizationService.xcodeproj
and build image_data_service

Running on Mac OS X Mavericks
-----------------------------

Create a unique directory name under /var/lib/CornerstoneVisualizationService/DICOMVolumes for each volume.
The directory name will be the volumeId for this volume.  Copy all the DICOM files for that volume into the
newly created directory.  The server will automatically load the DICOM files based on the volumeId passed to it.
It will also cache the volume in a VTK format in /var/lib/CornerstoneVisualizationService/VolumeCache which
makes it load faster.  You can safely delete the volumes in the cache and the service will automatically
regenerate them for you.  Once you have the server running, use your web browser to connect to the
status service (e.g. http://localhost:8080/web/)

For now, the easiest thing to do is run the service from within XCode.  In the future, the service will be
launched by another process.

Usage: image_data_service <address> <port> <dicom_volume_root> <volume_root> <doc_root>

address (http://0.0.0.0)

The address to listen for incoming requests.  Use http://0.0.0.0 to listen to requests on all network interfaces.
In real deployments you probably want to have a http server in front of the visualization service to provide authentication
and routing capabilities.  In this case, you probably want the visualization service to listen to localhost only (e.g. http://127.0.0.1)

port (80)

The TCP port to listen for incoming http requests.  This must be unique for each running visualization service.
The port will typically be assigned by the process launching the visualization service.  (NOTE: Alternatively
we can have the service grab any port available and return the port it is using to the launching process via
stdout)

dicom_volume_root (/Users/chafey/DICOMVolumes)

The directory where the visualization service will look for DICOM files to build volumes from.  The volumeId is currently assumed
to be the directory name here that contains the related DICOM files.

volume_root (/Users/chafey/VolumeCache)

The directory where built volumes are stored/cached.  The cached file is the volumeId

doc_root (/Users/chafey/src/cornerstoneVisualization/src/image_data_service)

The directory to server static HTTP files from.

Running on Windows 7
-------------------

Create a unique directory name under c:/ProgramData/Cornerstone/VisualizationService/DICOMVolumes for each volume.
The directory name will be the volumeId for this volume.  Copy all the DICOM files for that volume into the
newly created directory.  The server will automatically load the DICOM files based on the volumeId passed to it.
It will also cache the volume in a VTK format in c:/ProgramData/Cornerstone/VisualizationService/VolumeCache which
makes it load faster.  You can safely delete the volumes in the cache and the service will automatically
regenerate them for you.  Once you have the server running, use your web browser to connect to the
status service (e.g. http://localhost:8080/web/)

For now, the easiest thing to do is run the service from within visual studio.  In the future, the service will be
launched by another process.

Usage: image_data_service <address> <port> <dicom_volume_root> <volume_root> <doc_root>

address (http://localhost)

The address to listen for incoming requests.  Use http://0.0.0.0 to listen to requests on all network interfaces.
Note that connecting to localhost when it is listening on 0.0.0.0 results in very low performance - this needs to be investigated.
In real deployments you probably want to have a http server in front of the visualization service to provide authentication
and routing capabilities.  In this case, you probably want the visualization service to listen to localhost only (e.g. http://localhost)

port (8080)

The TCP port to listen for incoming http requests.  This must be unique for each running visualization service.
The port will typically be assigned by the process launching the visualization service.  (NOTE: Alternatively
we can have the service grab any port available and return the port it is using to the launching process via
stdout)

dicom_volume_root (c:/ProgramData/Cornerstone/VisualizationService/DICOMVolumes)

The directory where the visualization service will look for DICOM files to build volumes from.  The volumeId is currently assumed
to be the directory name here that contains the related DICOM files.

volume_root (c:/ProgramData/Cornerstone/VisualizationService/VolumeCache)

The directory where built volumes are stored/cached.  The cached file is the volumeId

doc_root (C:/src/GitHub/cornerstoneVisualization/src/image_data_service)

The directory to server static HTTP files from.

Features currently implemented
------------------------------

* Cross Platform Server - runs on Windows, Linux and Mac OS X
* HTTP GET interface to rendered images
* Multiple rendered image formats:
  * PNG with user specifiable compression rate
  * JPEG with user specifiable quality factor
* Software based rendering
* Loading volumes from DICOM images
* Caching of built volumes for faster subsequent loading
* Volume Rendering
  * User specifiable blend modes - Volume Renderered or MIP
  * Interactive rendering (lower quality image to improve framerate during interactivity)
  * User specifiable model matrix for rotation, scaling and translation
* MPR
  * User specifiable blend mode - MIP, MinIP and Average
  * User specifiable rotation matrix for oblique cuts
  * User specifiable position and slab thickness
* User specifiable rendered image size
* Web access to system status - volumes loaded, recent activity, memory and cpu used, etc

Backlog
-------

 * GPU accelerated rendering
 * Create volume loader abstraction so volumes can be loaded from various sources (WADO, WADO-RS, etc)
 * Create a separate service that deals with data management for volumes and segmentation masks.
   The rendering service would be a separate process and would access the volumes and segmentation
   masks in the data management service via shared memory mechanisms such as memory  mapped files.
 * Add more default transfer functions
 * Add support for user specifiable transfer functions
 * Add support for presets - defined views that specify the default camera, transfer function and window/level
 * Add support for gantry tilted data sets
 * Add support for segmentation masks
 * Add support for embedded geometry
 * Add support for curved planar reformatting (CPR)
 * Add a simple image viewer to interactively look at the loaded volumes
 * Add support for generating raw 16 bit data for MPR instead of window/leveled 8 bit data

FAQ
---

_What style guidelines are you following?_

Google C++ Style Guidelines: http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml

_Why did you choose vtk over voreen?_

Three reasons:
1. Voreen requires a GPU and I wanted to support software rendering
2. VTK has better documentation and excellent books
3. Voreen does not support Mac OS X as a first class development environment and that is what I am using

_Will you accept a patch adding support for voreen?_

Yes, please contact me to discuss

_Does the server take advantage of multiple cores?_

Yes, VTK utilizes multiple threads internally for various rendering operations.  The visualization service itself
processes incoming HTTP requests using a single thread.  Since rendering is CPU intensive and already threaded by
VTK, there was no need to multi-thread the request handling.  In fact, multi-threading the request handling would
significantly increase the complexity of the system.  Note that it is possible (and assumed) that multiple visualization
services will be running at the same time so concurrent rendering is possible using the multi-process model.  In the future
we may thread the request handling to support cancellation of long running render requests.


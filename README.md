Cornerstone Visualization Service
=================================

The Cornerstone Visualization Service provides 3D rendering capabilities for
volumetric medical image data sets such as CT, MRI and PET.  The service is intended
to be run on a server and receives incoming rendering requests via HTTP requests and returns
rendered images in PNG or JPEG formats.  The server supports volume renderering and MPR.

Live Examples
---------------

The best way to see the power of this library is to actually see it in use.

http://lurydemo.hopto.org:8080/web/

Building
-------

Install the following dependencies or install via [homebrew](http://brew.sh/) on Mac OS X:

* [CMake](http://cmake.org/) brew install cmake
* [boost](http://www.boost.org/) brew install boost
* [vtk](http://www.vtk.org/) brew install vtk

Create a build directory and run cmake from it
> mkdir build
> cd build
> cmake -G Xcode ..

Build the project using the generated project file (e.g. XCode on Mac OS X, Visual Studio on Windows, makefile on linux)

Running
-------

Usage: image_data_service <address> <port> <dicom_volume_root> <volume_root> <doc_root>

<address> (http://0.0.0.0)
The address to listen for incoming requests.  Use http://0.0.0.0 to listen to requests on all network interfaces.
In real deployments you probably want to have a http server in front of the visualization service to provide authentication
and routing capabilities.  In this case, you probably want the visualization service to listen to localhost only (e.g. http://127.0.0.1)

<port> (80)
The TCP port to listen for incoming http requests.  This must be unique for each running visualization service.  The port will
typically be assigned by the process launching the visualization service.

<dicom_volume_root> (/Users/chafey/DICOMVolumes)
The directory where the visualization service will look for DICOM files to build volumes from.  The volumeId is currently assumed
to be the directory name here that contains the related DICOM files.

<volume_root> (/Users/chafey/VolumeCache)
The directory where built volumes are stored/cached.  The cached file is the volumeId

<doc_root> (/Users/chafey/src/cornerstoneVisualization/src/image_data_service)
The directory to server static HTTP files from.

Key Features
------------

* Cross Platform Server - runs on Windows, Linux and Mac OS X
* REST interface
* Multiple rendered image formats:
  * PNG with variable compression rate
  * JPEG with variable quality factor
* Software based rendering
* GPU accelerated rendering
* Building volumes from DICOM images
* Volume Rendering
  * Volume Renderered and MIP blend modes
  * Interactive rendering (lower quality image to improve framerate during interactivity)
* MPR
  * Slabs (variable thickness)
  * Oblique
  * MIP, MinIP and Average Blend Modes

Backlog
-------

 * Consider loading images via WADO and/or WADO-RS
 * Create a separate service that deals with data management for volumes and segmentation masks.  The rendering service would
   be a separate process and would access the volumes and segmentation masks in the data management service via shared memory
   mechanisms such as memory  mapped files.
 * Add more default transfer functions
 * Add support for presets - defined views that specify the default camera, transfer function and window/level
 * Add support for gantry tilted data sets
 * Segmentation masks
 * embedded geometry
 * Curved Planar Reformatting (CPR)
 *

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


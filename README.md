# OpenCV Link
The link to the [OpenCV library](https://opencv.org/) for computer vision

![OpenCV logo](https://opencv.org/wp-content/uploads/2019/02/opencv-logo-1.png)

[Documentation of OpenCV 4.2.0](https://docs.opencv.org/4.2.0/)

Contact: Email [martirosyan.hrach97@gmail.com](martirosyan.hrach97@gmail.com)

## Get set up to build OpenCV from binaries

Here is a list of commands with the help of which developers can set up OpenCV

To install required packages:
  `sudo apt-get install build-essential`
  `sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev`

Time to clone latest stable version of OpenCV and OpenCV Contribution:
  `git clone https://github.com/opencv/opencv.git`
 ` git clone https://github.com/opencv/opencv_contrib.git`

## Build OpenCV using CMake
Install CMake's latest release: [Link to download page](https://cmake.org/download/)

### Using command line CMake:

Run the command

    cmake -S <path-to-source> -B <path-to-build>

Optional parameters:
`        -DCMAKE_BUILD_TYPE=<build type> \ `

`        -DBUILD_SHARED_LIBS=<library built type(ON/OFF)> \ `

`        -DOPENCV_EXTRA_MODULES_PATH=<path to extra modules(The second repository which we have cloned above)> \ `

`        -DCMAKE_INSTALL_PREFIX=<directory, where built binaries has to be installed> \ `


### Using CMake GUI:

* In CMake `Where is the source code` field add the directory where opencv repository has been cloned.
For example `/home/hrachm/Documents/opencv`.

* In `Where to build the binaries` add the directory where you want to build binaries.
Usually it is set in `/home/hrachm/Documents/opencv/BuildDir`.

* Press Configure
* Add optional parameters.

* Press Generate. This will generate `.sln` file for Windows, `Makefile` for Linux and `xcodeproj` for Mac.

### Using install.sh file:
Open the terminal and simply run `install.sh` script. This script except building opencv library with needed modeles,
also builds my video overyling project and will generate VideoOverlying object file.

### Test ###
After doing the steps I mentioned above, simply run `./run.sh` bash script with approrpriate video paths

` ./runs.sh <output video direcory>/ <background video path> <moving objects video paths>(As much as you want)`.

In my case:` /run.sh /home/hrach/Documents/Results/ /home/hrach/Downloads/Results/background.mp4 /home/hrach/Downloads/Results/moving.mp4`.

I'm really sorry for meaningless video example(Anyway i think it is not too bad.) :).

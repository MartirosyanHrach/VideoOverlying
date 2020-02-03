sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

cwd=`pwd`
mkdir project
cd opencv && mkdir build

cmake 	-S$cwd/opencv \
        -B$cwd/opencv/BuildDir\
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_SHARED_LIBS=OFF \
        -DOPENCV_EXTRA_MODULES_PATH=$cwd/opencv_contrib/modules \
        -DBUILD_EXAMPLES=OFF \
        -DCMAKE_INSTALL_PREFIX=$cwd/project/OpenCVBinaries \

cd build 
make -j4 install

cd ../../project

https://github.com/MartirosyanHrach/VideoOverlying.git

cwd=`cwd`
cd VideoOverlying && mkdir build

cmake 	-S$cwd/videoOverlayer \
        -B$cwd/videoOverlayer/BuildDir\
        -DCMAKE_BUILD_TYPE=Debug \

cd build 
make -j4 install
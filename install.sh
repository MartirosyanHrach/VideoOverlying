sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev

git clone https://github.com/opencv/opencv.git
git clone https://github.com/opencv/opencv_contrib.git

cwd=`pwd`
cd opencv && mkdir BuildDir

cmake 	-S$cwd/opencv \
        -B$cwd/opencv/BuildDir\
        -DCMAKE_BUILD_TYPE=Debug \
        -DBUILD_SHARED_LIBS=OFF \
        -DOPENCV_EXTRA_MODULES_PATH=$cwd/opencv_contrib/modules \
        -DBUILD_EXAMPLES=OFF \
        -DCMAKE_INSTALL_PREFIX=$cwd/OpenCVBinaries \

cd BuildDir 
make -j4 install
cd ../../

sudo rm -rf opencv
sudo rm -rf opencv_contrib

cwd=`pwd`

mkdir BuildDir
cmake 	-S$cwd \
        -B$cwd/BuildDir\
        -DCMAKE_BUILD_TYPE=Debug \

cd $cwd/BuildDir
sudo make -j4
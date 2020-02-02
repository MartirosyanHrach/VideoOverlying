project( VideoOverlying  )

set(OpenCV_BINARIES "${CMAKE_CURRENT_SOURCE_DIR}/OpenCVBinaries")

set(OPENCV_BINARY_LOCATION "${OpenCV_BINARIES}/lib")
set(OPENCV_INCLUDE_LOCATION "${OpenCV_BINARIES}/include/opencv4")

set(OpenCV_DIR "${OpenCV_BINARIES}/lib/cmake/opencv4")
find_package( OpenCV REQUIRED )

set(VideoOverlying_Sources "${CMAKE_CURRENT_SOURCE_DIR}/Sources")
set(VideoOverlying_CPP_SOURCES
    ${VideoOverlying_Sources}/CPPSource/Reader.cpp
    ${VideoOverlying_Sources}/CPPSource/Writer.cpp
    ${VideoOverlying_Sources}/CPPSource/Tracker.cpp
    ${VideoOverlying_Sources}/CPPSource/BackgroundSubtractor.cpp
    ${VideoOverlying_Sources}/CPPSource/main.cpp
)

add_executable( VideoOverlying ${VideoOverlying_CPP_SOURCES} )
target_include_directories(VideoOverlying PRIVATE "${VideoOverlying_Sources}/include")

set_target_properties(VideoOverlying PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    CXX_VISIBILITY_PRESET hidden
)

if(MSVC)
    target_compile_options(VideoOverlying
        PRIVATE "/W4"
        PRIVATE "/EHsc"
        PRIVATE "$<$<CONFIG:Debug>:/Zi>"
        PRIVATE "$<$<NOT:$<CONFIG:Debug>>:/O2>"
    )
else()
    target_compile_options(VideoOverlying
        PRIVATE "-std=c++14"
        PRIVATE "-Wall"
        PRIVATE "-Wextra"
        PRIVATE "-pedantic"
        PRIVATE "-Werror-implicit-function-declaration"
        PRIVATE "$<$<NOT:$<CONFIG:Debug>>:-O2>"
    )
endif()

target_link_libraries( VideoOverlying ${OpenCV_LIBS} libstdc++fs.a)

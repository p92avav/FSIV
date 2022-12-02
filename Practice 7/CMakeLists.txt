CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(histopathology_classifier)
ENABLE_LANGUAGE(CXX)
SET (CMAKE_CXX_STANDARD 11) 

FIND_PACKAGE(OpenCV	REQUIRED )
LINK_LIBRARIES(${OpenCV_LIBS})
include_directories ("${OpenCV_INCLUDE_DIRS}")

add_executable(train_val src/train_val.cpp src/common_code.cpp src/common_code.hpp src/metrics.cpp src/metrics.hpp)
add_executable(test_image src/test_image.cpp src/common_code.cpp src/common_code.hpp )

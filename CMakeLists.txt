CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

FIND_PACKAGE(OpenCV REQUIRED)

PROJECT(testwebcam)
SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)
ADD_EXECUTABLE(testwebcam testwebcam.cpp)
TARGET_LINK_LIBRARIES(testwebcam ${OpenCV_LIBS})


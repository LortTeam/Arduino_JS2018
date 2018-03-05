cmake_minimum_required(VERSION 2.8.4)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/cmake/ArduinoToolchain.cmake)
set(PROJECT_NAME Arduino_JS2018)
project(${PROJECT_NAME})

set(${CMAKE_PROJECT_NAME}_SKETCH Regina/manipulator_js_bitronics_new/manipulator_js_bitronics_new.ino)

#### Uncomment below additional settings as needed.
set(${CMAKE_PROJECT_NAME}_BOARD uno)
set(${CMAKE_PROJECT_NAME}_PORT /dev/cu.usbmodem1D121)
set(uno.build.mcu atmega328)
set(uno.upload.protocol wiring)
set(uno.upload.speed 115200)

#generate_arduino_firmware(${CMAKE_PROJECT_NAME})

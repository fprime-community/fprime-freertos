####
# featherM4.cmake:
#
# Adafruit Feather M4 Express support.
####
set(CMAKE_SYSTEM_NAME "Generic")
set(CMAKE_SYSTEM_PROCESSOR "arm")
set(CMAKE_CROSSCOMPILING 1)
set(FPRIME_PLATFORM "FreeRTOS_ArduinoFw")
set(FPRIME_USE_BAREMETAL_SCHEDULER OFF)
set(ARDUINO_BUILD_PROPERTIES)

set(ARDUINO_FQBN "adafruit:samd:adafruit_feather_m4")
add_compile_options(-D_BOARD_FEATHERM4 -DUSE_BASIC_TIMER)
# Run the base arduino setup which should detect settings!
set(ARDUINO_SUPPORT_DIR "${CMAKE_CURRENT_LIST_DIR}/../../../fprime-arduino/cmake/toolchain/support")
include("${ARDUINO_SUPPORT_DIR}/arduino-support.cmake")

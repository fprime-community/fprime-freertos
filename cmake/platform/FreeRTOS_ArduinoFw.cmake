if(NOT DEFINED ARDUINO_FQBN)
    message(FATAL_ERROR "Must defined arduino FQBN")
elseif(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    set(ARDUINO_TYPES_DIR "${FPRIME_PROJECT_ROOT}/fprime-arduino/cmake/platform/types/arm") 
else()
    set(ARDUINO_TYPES_DIR "${FPRIME_PROJECT_ROOT}/fprime-arduino/cmake/platform/types/basic")
endif()
set(ARDUINO_PLATFORM_DIR "${FPRIME_PROJECT_ROOT}/fprime-arduino/cmake/platform")

set(CMAKE_EXECUTABLE_SUFFIX "${FPRIME_ARDUINO_EXECUTABLE_SUFFIX}" CACHE INTERNAL "" FORCE)

# Now that we got FreeRTOS_featherM4.cmake to point to this as the platform 
# file, we want to set the platform back to ArduinoFw so we can utilize the rest
# of the fprime-arduino utilities
set(FPRIME_PLATFORM "ArduinoFw")

# Add FPrime OSAL Implementations
choose_fprime_implementation(Os/File Os_File_Stub)
choose_fprime_implementation(Os/Queue Os_Generic_PriorityQueue)
choose_fprime_implementation(Os/Cpu Os/Cpu/Stub)
choose_fprime_implementation(Os/Memory Os/Memory/Stub)

# Add fprime-freertos OSAL Implementations
choose_fprime_implementation(Os/Task Os_Task_FreeRTOS)
choose_fprime_implementation(Os/Mutex Os_Mutex_FreeRTOS)
choose_fprime_implementation(Os/ConditionVariable Os_ConditionVariable_FreeRTOS)


# Add Arduino OSAL Implementations
choose_fprime_implementation(Os/Console Os_Console_Arduino)
choose_fprime_implementation(Os/RawTime Os_RawTime_Arduino)

include_directories("${ARDUINO_TYPES_DIR}" "${ARDUINO_PLATFORM_DIR}")


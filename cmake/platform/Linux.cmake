####
# Linux.cmake:
#
# Linux platform file for standard linux targets.
####
# Set platform default for baremetal scheduler drivers
if (NOT DEFINED FPRIME_USE_BAREMETAL_SCHEDULER)
   set(FPRIME_USE_BAREMETAL_SCHEDULER OFF)
   message(STATUS "Requiring thread library")
   FIND_PACKAGE ( Threads REQUIRED )
endif()

set(LINUX_TYPES_DIR "${FPRIME_PROJECT_ROOT}/fprime/cmake/platform/types")

choose_fprime_implementation(Os/File Os/File/Posix)
choose_fprime_implementation(Os/Console Os/Console/Posix)

choose_fprime_implementation(Os/Task Os_Task_FreeRTOS)
choose_fprime_implementation(Os/Mutex Os_Mutex_FreeRTOS)
choose_fprime_implementation(Os/ConditionVariable Os_ConditionVariable_FreeRTOS)


choose_fprime_implementation(Os/Queue Os/Generic/PriorityQueue)
choose_fprime_implementation(Os/RawTime Os/RawTime/Posix)

choose_fprime_implementation(Os/Cpu Os/Cpu/Linux)
choose_fprime_implementation(Os/Memory Os/Memory/Linux)

# Use common linux setup
add_definitions(-DTGT_OS_TYPE_LINUX)
set(FPRIME_USE_POSIX ON)

# Add Linux specific headers into the system
include_directories(SYSTEM "${LINUX_TYPES_DIR}")


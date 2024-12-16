####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####

add_custom_target("${FPRIME_CURRENT_MODULE}")

list(APPEND SOURCE_FILES
    "Task.cpp"
    "Mutex.cpp"
    "ConditionVariable.cpp"
)

register_fprime_module(Os_Task_FreeRTOS)
register_fprime_module(Os_Mutex_FreeRTOS)
register_fprime_module(Os_ConditionVariable_FreeRTOS)

register_fprime_implementation(Os/Task Os_Task_FreeRTOS "${CMAKE_CURRENT_LIST_DIR}/DefaultTask.cpp")
register_fprime_implementation(Os/Mutex Os_Mutex_FreeRTOS "${CMAKE_CURRENT_LIST_DIR}/DefaultMutex.cpp")

set(MOD_DEPS

)

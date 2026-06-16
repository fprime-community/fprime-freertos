####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
register_os_implementation("Mutex;ConditionVariable" FreeRTOS)
register_os_implementation("Task" FreeRTOS)

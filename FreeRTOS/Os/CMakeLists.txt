####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####

add_custom_target("${FPRIME_CURRENT_MODULE}")

register_os_implementation("Mutex;ConditionVariable" FreeRTOS)
register_os_implementation("Task" FreeRTOS)

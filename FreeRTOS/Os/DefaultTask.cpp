// ======================================================================
// \title FreeRTOS/Os/DefaultTask.cpp
// \brief sets default Os::Task to FreeRTOS implementation via linker
// ======================================================================
#include "FreeRTOS/Os/Task.hpp"
#include <Os/Delegate.hpp>

namespace Os {

TaskInterface* TaskInterface::getDelegate(TaskHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<TaskInterface, 
                                      Os::FreeRTOS::Task::FreeRTOSTask>(aligned_new_memory);
}

}  // namespace Os

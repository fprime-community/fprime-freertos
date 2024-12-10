// ======================================================================
// \title FreeRTOS/Os/Task.cpp
// \brief FreeRTOS implementation for Os::Task
// ======================================================================
#include "FreeRTOS/Os/Task.hpp"
#include <Fw/Types/Assert.hpp>

namespace Os {
namespace FreeRTOS {
namespace Task {

// FreeRTOS wrapper function to adapt to FreeRTOS task function signature
static void FreeRTOSTaskWrapper(void* arg) {

    // Cast the `void*` argument back to the `Arguments` structure
    Os::TaskInterface::Arguments* arguments = reinterpret_cast<Os::TaskInterface::Arguments*>(arg);
    // Get the task routine and its argument
    Os::TaskInterface::taskRoutine taskRoutine = arguments->m_routine;
    void* routineArg = arguments->m_routine_argument;
    
    // Verify if the casted routine is valid
    if (!taskRoutine) {
        FW_ASSERT(0);
    }
    
    while (1) {
        taskRoutine(routineArg);
    }
}

void FreeRTOSTask::onStart() {
    // Any task-specific startup actions
}

Os::Task::Status FreeRTOSTask::start(const Arguments& arguments) {

    // Dynamically allocate memory for arguments
    Arguments* taskArguments = new Arguments(arguments);

    // Ensure routine is not null
    FW_ASSERT(arguments.m_routine != nullptr);

    // Create task
    BaseType_t taskCreationStatus = xTaskCreate(
        FreeRTOSTaskWrapper,                  // FreeRTOS wrapper function
        arguments.m_name.toChar(),            // Task name
        arguments.m_stackSize,                // Stack size
        static_cast<void*>(taskArguments),    // Argument for the task function
        arguments.m_priority,                 // Task priority
        &(this->m_handle.m_task_descriptor)   // Handle to the created task
    );

    if (taskCreationStatus != pdPASS) {
        return Os::Task::Status::UNKNOWN_ERROR;
    }

    return Os::Task::Status::OP_OK;
}

Os::Task::Status FreeRTOSTask::join() {
    // FreeRTOS does not support a direct join
    return Os::Task::Status::JOIN_ERROR;
}

TaskHandle* FreeRTOSTask::getHandle() {
    return &this->m_handle;
}

void FreeRTOSTask::suspend(Os::Task::SuspensionType /*suspensionType*/) {
    vTaskSuspend(this->m_handle.m_task_descriptor);
}

void FreeRTOSTask::resume() {
    vTaskResume(this->m_handle.m_task_descriptor);
}

Os::Task::Status FreeRTOSTask::_delay(Fw::TimeInterval interval) {
    TickType_t ticks = pdMS_TO_TICKS( (interval.getSeconds()*1000) + interval.getUSeconds());
    vTaskDelay(ticks);
    return Os::Task::Status::OP_OK;
}

}  // end namespace Task
}  // end namespace FreeRTOS
}  // end namespace Os

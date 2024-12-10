// ======================================================================
// \title FreeRTOS/Os/Task.hpp
// \brief FreeRTOS definitions for Os::Task
// ======================================================================
#ifndef OS_FREERTOS_TASK_HPP
#define OS_FREERTOS_TASK_HPP

#include <Os/Task.hpp>
#include <FreeRTOS.h>
#include <task.h>

namespace Os {
namespace FreeRTOS {
namespace Task {

// FreeRTOS task handle structure
struct FreeRTOSTaskHandle : public TaskHandle {
    TaskHandle_t m_task_descriptor = nullptr;  // FreeRTOS task handle
};

// FreeRTOS implementation of Os::Task
class FreeRTOSTask : public TaskInterface {
public:
    //! \brief Constructor to initialize the task
    FreeRTOSTask() = default;

    //! \brief Destructor to clean up the mutex
    ~FreeRTOSTask() = default;

    // Do not allow copy constructor
    FreeRTOSTask(const FreeRTOSTask& other) = delete;
    // Do not allow copy assignment
    FreeRTOSTask& operator=(const FreeRTOSTask& other) = delete;

    //! \brief Called by fprime OS task to allow for required start actions
    void onStart() override;

    //! \brief Creates but does not actually start the task.
    //! Remember the vTaskStartScheduler function must be called to start tasks.
    //! \param arguments: Arguments used to create the task
    //! \return Status of the task creation attempt
    Status start(const Arguments& arguments) override;

    //! \brief Attempt task join, which is note supported by FreeRTOS
    //! \return Will always return Os::Task::Status::JOIN_ERROR
    Status join() override;

    //! \brief Suspend task and indefinitely prevent execution
    //! \param suspensionType: Not used by FreeRTOS
    void suspend(SuspensionType suspensionType) override;

    //! \brief Resume a suspended task
    void resume() override;

    //! \brief Delay task for a given duration
    //! \param interval: The amount of time in milliseconds to delay task
    //! \return Always returns Os::Task::Status::OP_OK
    Status _delay(Fw::TimeInterval interval) override;

    //! \brief Get the underlying task handle
    //! \return Internal task handle representation
    TaskHandle* getHandle() override;

private:
    //! Handle for FreeRTOSTask
    FreeRTOSTaskHandle m_handle;
};

}  // end namespace Task
}  // end namespace FreeRTOS
}  // end namespace Os

#endif  // OS_FREERTOS_TASK_HPP

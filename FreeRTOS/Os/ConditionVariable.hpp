// ======================================================================
// \title fprime-freertos/FreeRTOS/Os/ConditionVariable.hpp
// \brief FreeRTOS definitions for Os::ConditionVariable
// ======================================================================
#ifndef OS_FREERTOS_CONDITION_VARIABLE_HPP
#define OS_FREERTOS_CONDITION_VARIABLE_HPP

#include <Os/Condition.hpp>
#include <FreeRTOS.h>
#include <semphr.h>

namespace Os {
namespace FreeRTOS {

//! \brief FreeRTOS implementation of Os::ConditionVariable
class FreeRTOSConditionVariable : public ConditionVariableInterface {
  public:
    //! \brief Constructor to initialize the condition variable
    FreeRTOSConditionVariable();

    //! \brief Destructor to clean up the condition variable
    ~FreeRTOSConditionVariable() override;

    // Do not allow copy constructor
    ConditionVariableInterface& operator=(const ConditionVariableInterface& other) override = delete;

    //! \brief Wait on the condition variable
    //! \param mutex: The mutex that must be released to wait on condition
    ConditionVariable::Status pend(Os::Mutex& mutex);

    //! \brief Notify a single task waiting on the condition variable
    void notify() override;

    //! \brief Notify all tasks currently waiting on the condition variable
    void notifyAll() override;

    //! \brief Get handle
    ConditionVariableHandle* getHandle() override;

  private:
    //! FreeRTOS semaphore used to implement condition variable feature
    SemaphoreHandle_t m_semaphore;
};

}  // namespace FreeRTOS
}  // namespace Os
#endif  // OS_FREERTOS_CONDITION_VARIABLE_HPP

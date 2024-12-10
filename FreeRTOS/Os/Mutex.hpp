// ======================================================================
// \title FreeRTOS/Os/Mutex.hpp
// \brief FreeRTOS definitions for Os::Mutex
// ======================================================================
#ifndef OS_FREERTOS_MUTEX_HPP
#define OS_FREERTOS_MUTEX_HPP

#include "Os/Mutex.hpp"
#include <FreeRTOS.h>
#include <semphr.h>

namespace Os {
namespace FreeRTOS {
namespace Mutex {

struct FreeRTOSMutexHandle : public MutexHandle {
    SemaphoreHandle_t m_mutex_descriptor = NULL;
};

//! \brief FreeRTOS implementation of Os::Mutex
class FreeRTOSMutex : public MutexInterface {
  public:
    //! \brief Constructor to initialize the mutex
    FreeRTOSMutex();

    //! \brief Destructor to clean up the mutex
    ~FreeRTOSMutex() override;

    //! \brief Get the underlying mutex handle
    //! \return Internal mutex handle representation
    MutexHandle* getHandle() override;

    //! \brief Lock the mutex
    //! \return Status of mutex lock attempt
    Status take() override;

    //! \brief Unlock the mutex
    //! \return Status of mutex unlock attempt
    Status release() override;

  private:
    //! Handle for FreeRTOSMutex
    FreeRTOSMutexHandle m_handle;
};

}  // namespace Mutex
}  // namespace FreeRTOS
}  // namespace Os
#endif  // OS_FREERTOS_MUTEX_HPP

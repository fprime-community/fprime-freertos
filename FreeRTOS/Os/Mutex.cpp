// ======================================================================
// \title FreeRTOS/Os/Mutex.cpp
// \brief FreeRTOS implementation for Os::Mutex
// ======================================================================
#include "FreeRTOS/Os/Mutex.hpp"
#include <Fw/Types/Assert.hpp>

namespace Os {
namespace FreeRTOS {
namespace Mutex {

FreeRTOSMutex::FreeRTOSMutex() : Os::MutexInterface(), m_handle() {
    this->m_handle.m_mutex_descriptor = xSemaphoreCreateMutex();
    FW_ASSERT(this->m_handle.m_mutex_descriptor != NULL);
}

FreeRTOSMutex::~FreeRTOSMutex() {
    vSemaphoreDelete(this->m_handle.m_mutex_descriptor);
    
}

FreeRTOSMutex::Status FreeRTOSMutex::take() {

    // In many other implementations, the OS calls to take the Semaphore will
    // return immediately and provide a unique return value if the current
    // task is already the mutex holder. FreeRTOS has no such protection against
    // deadlock, so we must first check to ensure the current mutex holder is
    // not the current task before proceeding.
    TaskHandle_t current_task = xTaskGetCurrentTaskHandle();
    TaskHandle_t mutex_holder = xSemaphoreGetMutexHolder(reinterpret_cast<QueueHandle_t>(this->m_handle.m_mutex_descriptor));
    
    if (current_task == mutex_holder and current_task != 0) {
        return Os::MutexInterface::Status::ERROR_DEADLOCK;
    } else {
        if (xSemaphoreTake(this->m_handle.m_mutex_descriptor, portMAX_DELAY) == pdTRUE) {
            return Os::MutexInterface::Status::OP_OK;
        } else {
            return Os::MutexInterface::Status::ERROR_OTHER;
        }
        
    }
}

FreeRTOSMutex::Status FreeRTOSMutex::release() {
    if (xSemaphoreGive(this->m_handle.m_mutex_descriptor) == pdTRUE) {
        return Os::MutexInterface::Status::OP_OK;
    } else {
        return Os::MutexInterface::Status::ERROR_OTHER;
    }
}

MutexHandle* FreeRTOSMutex::getHandle() {
    return &this->m_handle;
}

}  // namespace Mutex
}  // namespace FreeRTOS
}  // namespace Os

// ======================================================================
// \title FreeRTOS/Os/DefaultMutex.cpp
// \brief sets default Os::Mutex FreeRTOS implementation via linker
// ======================================================================
#include "FreeRTOS/Os/Mutex.hpp"
#include "FreeRTOS/Os/ConditionVariable.hpp"
#include <Os/Delegate.hpp>


namespace Os {

//! \brief Get a delegate for MutexInterface that intercepts calls for FreeRTOS
//! \param aligned_new_memory: Aligned memory to fill
//! \return: Pointer to delegate
MutexInterface* MutexInterface::getDelegate(MutexHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<MutexInterface, 
                                      Os::FreeRTOS::Mutex::FreeRTOSMutex>(aligned_new_memory);
}

//! \brief Get a delegate for ConditionVariable that intercepts calls for FreeRTOS
//! \param aligned_new_memory: Aligned memory to fill
//! \return: Pointer to delegate
ConditionVariableInterface* ConditionVariableInterface::getDelegate(
    ConditionVariableHandleStorage& aligned_new_memory) {
    return Os::Delegate::makeDelegate<ConditionVariableInterface, 
                                      Os::FreeRTOS::FreeRTOSConditionVariable,
                                      ConditionVariableHandleStorage>(aligned_new_memory);
}

}  // namespace Os

// ======================================================================
// \title  OsResources.cpp
// \author laboratory10
// \brief  cpp file for OsResources component implementation class
// ======================================================================

#include "FreeRTOS/Svc/OsResources/OsResources.hpp"
#include <FreeRTOS.h>
#include <task.h>

#include <Arduino.h>

extern char __end__;
extern "C" char __StackTop;
extern "C" char* sbrk(int incr); // Current heap end

namespace FreeRTOS {      

#define MAX_TASKS 10
static TaskStatus_t statusArray[MAX_TASKS];

struct TaskTelemetryEntry {
    UBaseType_t taskNumber; 
    uint64_t latestStackWatermark;
    char taskName[16];
    bool active;
};

static TaskTelemetryEntry taskTelemetry[MAX_TASKS] = {0};

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

OsResources ::OsResources(const char* const compName) : OsResourcesComponentBase(compName) {}

OsResources ::~OsResources() {}

// ----------------------------------------------------------------------
// Handler implementations for user-defined typed input ports
// ----------------------------------------------------------------------

void OsResources ::Run_handler(const FwIndexType portNum, U32 tick_time_hz) {
    this->tlmWrite_FREERTOS_HEAP_FREE(xPortGetFreeHeapSize());
    this->tlmWrite_FREERTOS_HEAP_FREE_LOW_WATERMARK(xPortGetMinimumEverFreeHeapSize());

    //intptr_t heap_used = sbrk(0) - &__end__;
    intptr_t heap_stack_gap = (intptr_t)&__StackTop - (intptr_t)sbrk(0);
    U32 ram_available = heap_stack_gap > 0 ? static_cast<U32>(heap_stack_gap) : 0;
    this->tlmWrite_RAM_AVAILABLE(ram_available);
    
    uint32_t totalRunTime;
    //This will return number of actual tasks, or zero if there are more than MAX_TASKS
    UBaseType_t numTasks = uxTaskGetSystemState(statusArray, MAX_TASKS, &totalRunTime);

    for (UBaseType_t i = 0; i < numTasks; i++) {
        //For each task in the system state, search for existing entry in the TaskTelemetryEntry array
        bool found_entry = false;
        for (UBaseType_t j = 0; j < numTasks; j++) {
            if (statusArray[i].xTaskNumber == taskTelemetry[j].taskNumber) {
                taskTelemetry[j].latestStackWatermark = statusArray[i].usStackHighWaterMark*4;
                found_entry = true;
                break;
            }
        }

        //If the table didn't have an entry for this task, try to create one
        if (!found_entry) {
            for (UBaseType_t j = 0; j < MAX_TASKS; j++) {
                if (taskTelemetry[j].active == false) {
                    taskTelemetry[j].taskNumber = statusArray[i].xTaskNumber;
                    taskTelemetry[j].latestStackWatermark = statusArray[i].usStackHighWaterMark*4;
                    taskTelemetry[j].active = true;
                    strncpy(taskTelemetry[j].taskName, statusArray[i].pcTaskName, sizeof(taskTelemetry[j].taskName) - 1);
                    taskTelemetry[j].taskName[sizeof(taskTelemetry[j].taskName) - 1] = '\0';
                    break;
                }
            }
        }
    }
    
    /*Serial.println(F("---- Task Telemetry ----"));
    for (UBaseType_t i = 0; i < MAX_TASKS; i++) {
        if (taskTelemetry[i].active) {
            const char* name = "<unknown>";

            // try to find matching task in statusArray for name lookup
            for (UBaseType_t j = 0; j < MAX_TASKS; j++) {
                if (statusArray[j].xTaskNumber == taskTelemetry[i].taskNumber) {
                    name = statusArray[j].pcTaskName;
                    break;
                }
            }

            Serial.print(F("Entry "));
            Serial.print(i);
            Serial.print(F(": TaskName="));
            Serial.print(name);
            Serial.print(F(" | TaskNumber="));
            Serial.print(taskTelemetry[i].taskNumber);
            Serial.print(F(" | Watermark="));
            Serial.print(taskTelemetry[i].latestStackWatermark);
            Serial.println(F(" | Active=1"));
        } else {
            Serial.print(F("Entry "));
            Serial.print(i);
            Serial.println(F(": (inactive)"));
        }
    }
    Serial.println(F("------------------------"));*/
    
    if (taskTelemetry[0].active) {
        this->tlmWrite_TASK_1_NAME(Fw::String(taskTelemetry[0].taskName));
        this->tlmWrite_TASK_1_STACK_FREE_LOW_WATERMARK(taskTelemetry[0].latestStackWatermark);
    }
    if (taskTelemetry[1].active) {
        this->tlmWrite_TASK_2_NAME(Fw::String(taskTelemetry[1].taskName));
        this->tlmWrite_TASK_2_STACK_FREE_LOW_WATERMARK(taskTelemetry[1].latestStackWatermark); 
    }
    if (taskTelemetry[2].active) {
        this->tlmWrite_TASK_3_NAME(Fw::String(taskTelemetry[2].taskName));
        this->tlmWrite_TASK_3_STACK_FREE_LOW_WATERMARK(taskTelemetry[2].latestStackWatermark); 
    }
    if (taskTelemetry[3].active) {
        this->tlmWrite_TASK_4_NAME(Fw::String(taskTelemetry[3].taskName));
        this->tlmWrite_TASK_4_STACK_FREE_LOW_WATERMARK(taskTelemetry[3].latestStackWatermark); 
    }
    if (taskTelemetry[4].active) {
        this->tlmWrite_TASK_5_NAME(Fw::String(taskTelemetry[4].taskName));
        this->tlmWrite_TASK_5_STACK_FREE_LOW_WATERMARK(taskTelemetry[4].latestStackWatermark); 
    }
    if (taskTelemetry[5].active) {
        this->tlmWrite_TASK_6_NAME(Fw::String(taskTelemetry[5].taskName));
        this->tlmWrite_TASK_6_STACK_FREE_LOW_WATERMARK(taskTelemetry[5].latestStackWatermark); 
    }
    if (taskTelemetry[6].active) {
        this->tlmWrite_TASK_7_NAME(Fw::String(taskTelemetry[6].taskName));
        this->tlmWrite_TASK_7_STACK_FREE_LOW_WATERMARK(taskTelemetry[6].latestStackWatermark); 
    }
    if (taskTelemetry[7].active) {
        this->tlmWrite_TASK_8_NAME(Fw::String(taskTelemetry[7].taskName));
        this->tlmWrite_TASK_8_STACK_FREE_LOW_WATERMARK(taskTelemetry[7].latestStackWatermark); 
    }
    if (taskTelemetry[8].active) {
        this->tlmWrite_TASK_9_NAME(Fw::String(taskTelemetry[8].taskName));
        this->tlmWrite_TASK_9_STACK_FREE_LOW_WATERMARK(taskTelemetry[8].latestStackWatermark); 
    }
    if (taskTelemetry[9].active) {
        this->tlmWrite_TASK_10_NAME(Fw::String(taskTelemetry[9].taskName));
        this->tlmWrite_TASK_10_STACK_FREE_LOW_WATERMARK(taskTelemetry[9].latestStackWatermark); 
    }
}

}  // namespace FreeRTOS

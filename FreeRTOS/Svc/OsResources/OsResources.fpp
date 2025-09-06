module FreeRTOS {

    @ Component that reports key FreeRTOS resource information
    passive component OsResources {

        @ Run port
        guarded input port Run: [1] Svc.Sched

        @ FreeRTOS heap space remaining in bytes
        telemetry FREERTOS_HEAP_FREE: U64 id 0 \
        format "{} bytes"

        @ FreeRTOS heap space remaining low watermark in bytes
        telemetry FREERTOS_HEAP_FREE_LOW_WATERMARK: U64 id 1 \
        format "{} bytes"

        @ Free SRAM in bytes(not part of heap, stack, or the FreeRTOS heap inside bss)
        telemetry RAM_AVAILABLE: U64 id 2 \
        format "{} bytes"

        @ Task 1 name
        telemetry TASK_1_NAME: string size 16 id 3 \
        format "{}"

        @ Task 1 stack space remaining low watermark in bytes
        telemetry TASK_1_STACK_FREE_LOW_WATERMARK: U64 id 4 \
        format "{} bytes"

        @ Task 2 name
        telemetry TASK_2_NAME: string size 16 id 5 \
        format "{}"

        @ Task 2 stack space remaining low watermark in bytes
        telemetry TASK_2_STACK_FREE_LOW_WATERMARK: U64 id 6 \
        format "{} bytes"

        @ Task 3 name
        telemetry TASK_3_NAME: string size 16 id 7 \
        format "{}"

        @ Task 3 stack space remaining low watermark in bytes
        telemetry TASK_3_STACK_FREE_LOW_WATERMARK: U64 id 8 \
        format "{} bytes"

        @ Task 4 name
        telemetry TASK_4_NAME: string size 16 id 9 \
        format "{}"

        @ Task 4 stack space remaining low watermark in bytes
        telemetry TASK_4_STACK_FREE_LOW_WATERMARK: U64 id 10 \
        format "{} bytes"

        @ Task 5 name
        telemetry TASK_5_NAME: string size 16 id 11 \
        format "{}"

        @ Task 5 stack space remaining low watermark in bytes
        telemetry TASK_5_STACK_FREE_LOW_WATERMARK: U64 id 12 \
        format "{} bytes"

        @ Task 6 name
        telemetry TASK_6_NAME: string size 16 id 13 \
        format "{}"

        @ Task 6 stack space remaining low watermark in bytes
        telemetry TASK_6_STACK_FREE_LOW_WATERMARK: U64 id 14 \
        format "{} bytes"

        @ Task 7 name
        telemetry TASK_7_NAME: string size 16 id 15 \
        format "{}"

        @ Task 7 stack space remaining low watermark in bytes
        telemetry TASK_7_STACK_FREE_LOW_WATERMARK: U64 id 16 \
        format "{} bytes"

        @ Task 8 name
        telemetry TASK_8_NAME: string size 16 id 17 \
        format "{}"

        @ Task 8 stack space remaining low watermark in bytes
        telemetry TASK_8_STACK_FREE_LOW_WATERMARK: U64 id 18 \
        format "{} bytes"

        @ Task 9 name
        telemetry TASK_9_NAME: string size 16 id 19 \
        format "{}"

        @ Task 9 stack space remaining low watermark in bytes
        telemetry TASK_9_STACK_FREE_LOW_WATERMARK: U64 id 20 \
        format "{} bytes"

        @ Task 10 name
        telemetry TASK_10_NAME: string size 16 id 21 \
        format "{}"

        @ Task 10 stack space remaining low watermark in bytes
        telemetry TASK_10_STACK_FREE_LOW_WATERMARK: U64 id 22 \
        format "{} bytes"

        ###############################################################################
        # Standard AC Ports: Required for Channels, Events, Commands, and Parameters  #
        ###############################################################################
        @ Port for requesting the current time
        time get port timeCaller

        @ Port for sending telemetry channels to downlink
        telemetry port tlmOut

    }
}
#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <avr/io.h>

#define configUSE_PREEMPTION		0		// 1
#define configUSE_IDLE_HOOK			1		//1 когда есть задача бездействия
#define configUSE_TICK_HOOK			0
#define configCPU_CLOCK_HZ			( ( unsigned long ) 8000000 )
#define configTICK_RATE_HZ			( ( portTickType ) 1000 ) //1000
#define configMAX_PRIORITIES		( ( unsigned portBASE_TYPE ) 4 )
#define configMINIMAL_STACK_SIZE	( ( unsigned short ) 85 )
#define configTOTAL_HEAP_SIZE		( (size_t ) ( 4500 ) )
#define configMAX_TASK_NAME_LEN		( 8 )
#define configUSE_TRACE_FACILITY	0
#define configUSE_16_BIT_TICKS		1		// =1 для 8-разрядных МК
#define configIDLE_SHOULD_YIELD		1
#define configQUEUE_REGISTRY_SIZE	0
#define configUSE_MUTEXES			1		// используем мьютексы
#define configUSE_COUNTING_SEMAPHORES  1

//#define configUSE_TIMERS			1		// включаем программные таймеры
//#define configTIMER_TASK_PRIORITY   

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		1	//1
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */

#define INCLUDE_vTaskPrioritySet		0
#define INCLUDE_uxTaskPriorityGet		0
#define INCLUDE_vTaskDelete				1
#define INCLUDE_vTaskCleanUpResources	0
#define INCLUDE_vTaskSuspend			0
#define INCLUDE_vTaskDelayUntil			0//1
#define INCLUDE_vTaskDelay				0//1
#define INCLUDE_xSemaphoreCreateMutex	1

#endif /* FREERTOS_CONFIG_H */

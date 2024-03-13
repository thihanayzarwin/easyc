#include <stdio.h> 
#include "FreeRTOS.h"
#define MONITOR_STACK_SIZE    configMINIMAL_STACK_SIZE * 2


TaskHandle_t xMonitorTaskHandle;

static void prvMonitorTask(void *pvParameters) {
  TickType_t xLastUpdateTime = xTaskGetTickCount();
  const TickType_t xMonitoringPeriod = pdMS_TO_TICKS(1000);

  while (1) {
    
    vTaskDelayUntil(&xLastUpdateTime, xMonitoringPeriod);

    TaskStatus_t xTaskDetails[uxTaskGetNumberOfTasks()];
    uint32_t ulTotalRunTime = uxTaskGetSystemState(xTaskDetails, sizeof(xTaskDetails), NULL);

    
    #ifdef USE_MONITOR_OUTPUT
    printf("*** Task Monitoring Report ***\n");
    printf("Task Name\tCurrent State\tRun Time (ms)\n");
    for (int i = 0; i < uxTaskGetNumberOfTasks(); i++) {
      printf("%-16s\t%s\t\t%d\n", xTaskDetails[i].pcTaskName,
             (xTaskDetails[i].eCurrentState == eReady) ? "Ready" : "Running",
             (xTaskDetails[i].ulRunTimeCounter * portTICK_PERIOD_MS));
    }
    printf("Total System Run Time: %d ms\n\n", ulTotalRunTime);
    #endif
  }
}

void vStartMonitorTask(void) {
  xTaskCreate(prvMonitorTask, "Monitor", MONITOR_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, &xMonitorTaskHandle);
  if (xMonitorTaskHandle == NULL) {
   
  }
}

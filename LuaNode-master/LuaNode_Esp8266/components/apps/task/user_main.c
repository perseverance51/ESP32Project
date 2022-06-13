
#include "esp_common.h"
#include "lua.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "c_stdio.h"


void my_task(void *pvParameters) {
    printf("task init\n");

	while (1)
	{
		printf("repost\n");
		vTaskDelay(1000);
	}

	//vTaskDelete(NULL);
}

/******************************************************************************
 * FunctionName : user_init
 * Description  : entry of user application, init user function here
 * Parameters   : none
 * Returns      : none
*******************************************************************************/
void user_init(void)
{
    printf("SDK version:%s\n", system_get_sdk_version());

	uart_init_new();

	xTaskCreate(my_task, "my_task", 128, NULL, 4, NULL);
}


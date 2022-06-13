#include <stdio.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "freertos/event_groups.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "esp_log.h"
#include "nvs_flash.h"
#include "espconn.h"
#include "tmr.h"

#define FEEDBACK_DATA			"ESP32_Data"
#define EXAMPLE_WIFI_SSID		"TP-LINK_93D966"
#define EXAMPLE_WIFI_PASS		"123456"
#define TMP_TASK_PRIORITY		13
#define TCP_TASK_PRIORITY		12
#define LOCAL_PORT				11000
#define REMOTE_PORT				6000

static struct espconn *_ptrUDPServer;
static EventGroupHandle_t wifi_event_group;
static int srv_timeout = 60 * 60;	// disconnect when the server didn't receive data in the past 1 hour
const int CONNECTED_BIT = BIT0;
static const char *TAG = "main";

static esp_err_t event_handler(void *ctx, system_event_t *event)
{
    switch(event->event_id) {
    case SYSTEM_EVENT_STA_START:
		ESP_LOGI(TAG, "STA start");
        esp_wifi_connect();
        break;
    case SYSTEM_EVENT_STA_GOT_IP:
        xEventGroupSetBits(wifi_event_group, CONNECTED_BIT);
        break;
    case SYSTEM_EVENT_STA_DISCONNECTED:
        /* This is a workaround as ESP32 WiFi libs don't currently
           auto-reassociate. */
        esp_wifi_connect();
        xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);
		free(_ptrUDPServer);
		free(_ptrUDPServer->proto.udp);
        break;
    default:
        break;
    }
    return ESP_OK;
}

static void initialise_wifi(void)
{
	wifi_config_t wifi_config = {
        .sta = {
            .ssid = EXAMPLE_WIFI_SSID,
            .password = EXAMPLE_WIFI_PASS,
        },
    };
	tcpip_adapter_init();
    wifi_event_group = xEventGroupCreate();
	esp_event_loop_init(event_handler, NULL);
	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_storage(WIFI_STORAGE_RAM));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(ESP_IF_WIFI_STA, &wifi_config));
	ESP_ERROR_CHECK(esp_wifi_start());
}

void disconnect_cb(void *arg)
{
	ESP_LOGI(TAG, "disconnected");
}

void receive_cb(void *arg, char *pdata, unsigned short len)
{
	struct espconn *pespconn = (struct espconn *) arg;
	ESP_LOGI(TAG, "received data");
	ESP_LOGI(TAG, "received data: %s, len=%d", pdata, len);
	//espconn_sent(pespconn, (uint8*)FEEDBACK_DATA, strlen(FEEDBACK_DATA));
}

void send_cb(void *arg)
{
	ESP_LOGI(TAG, "sent data");
}

void connect_cb(void *arg)
{
	struct espconn *pespconn = (struct espconn *) arg;
	ESP_LOGI(TAG, "connected");
	espconn_regist_disconcb(pespconn, disconnect_cb);
	espconn_regist_recvcb(pespconn, receive_cb);
	espconn_regist_sentcb(pespconn, send_cb);
	//espconn_sent(pespconn, (uint8*)FEEDBACK_DATA, strlen(FEEDBACK_DATA));
}

static void tmp_task(void *pvParameters)
{
	while(1) {
		xEventGroupWaitBits(wifi_event_group, CONNECTED_BIT, false, true, portMAX_DELAY);
        ESP_LOGI(TAG, "Got IP");
		xEventGroupClearBits(wifi_event_group, CONNECTED_BIT);

		// start espconn
		_ptrUDPServer = (struct espconn *) malloc(sizeof(struct espconn));
		_ptrUDPServer->type = ESPCONN_TCP;
		_ptrUDPServer->state = ESPCONN_NONE;
		_ptrUDPServer->proto.tcp = (esp_tcp *) malloc(sizeof(esp_tcp));
		_ptrUDPServer->proto.tcp->local_port = LOCAL_PORT;
		//_ptrUDPServer->proto.tcp->remote_port = REMOTE_PORT;

		espconn_regist_connectcb(_ptrUDPServer, connect_cb);
		ESP_LOGI(TAG, "wait for client");
		espconn_accept(_ptrUDPServer);
		espconn_regist_time(_ptrUDPServer, srv_timeout, 0);

		while(1) {
			tmr_delay_msec(5000);
			ESP_LOGI(TAG, "tmp_task loop");
		}
	}
	vTaskDelete(NULL);
}

void app_main()
{
	nvs_flash_init();
    initialise_wifi();

	xTaskCreate(&tmp_task, "tmp_task", 4096, NULL, TMP_TASK_PRIORITY, NULL);

}

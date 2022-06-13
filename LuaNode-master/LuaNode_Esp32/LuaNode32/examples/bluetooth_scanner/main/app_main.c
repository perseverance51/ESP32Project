/**
 * A bluetooth scanner sample
 * 
 * Nicholas3388
 * 2017.02.24
 */

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#include <bt.h>
#include <esp_bt_main.h>
#include <esp_gap_ble_api.h>
#include <esp_log.h>

#include "sdkconfig.h"

#define BT_BD_ADDR_STR         "%02x:%02x:%02x:%02x:%02x:%02x"
#define BT_BD_ADDR_HEX(addr)   addr[0], addr[1], addr[2], addr[3], addr[4], addr[5]

static const char *bt_event_type_to_string(uint32_t eventType);
static const char *bt_gap_search_event_type_to_string(uint32_t searchEvt);
static const char *bt_addr_t_to_string(esp_ble_addr_type_t type);
static const char *bt_dev_type_to_string(esp_bt_dev_type_t type);

static const char tag[] = "ble1";

static void dump_adv_payload(uint8_t *payload) {
	uint8_t length;
	uint8_t ad_type;
	uint8_t sizeConsumed = 0;
	int finished = 0;
	int i;
	char text[31*2+1];
	//sprintf(text, "%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x%.2x")
	while(!finished) {
		length = *payload;
		payload++;
		if (length != 0) {
			ad_type = *payload;
			payload += length;
			ESP_LOGD(tag, "Type: 0x%.2x, length: %d", ad_type, length);

		}

		sizeConsumed = 1 + length;
		if (sizeConsumed >=31 || length == 0) {
			finished = 1;
		}
	} // !finished
} // dump_adv_payload


static void gap_event_handler(uint32_t event, void *param) {
	ESP_LOGI(tag, "Received a GAP event: %s", bt_event_type_to_string(event));
	esp_ble_gap_cb_param_t *p = (esp_ble_gap_cb_param_t *)param;
	switch (event) {
	case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
		ESP_LOGI(tag, "status: %d", p->scan_param_cmpl.status);
		break;
    case ESP_GAP_BLE_SCAN_RESULT_EVT:
        {
			ESP_LOGI(tag, "device address (bda): %02x:%02x:%02x:%02x:%02x:%02x", BT_BD_ADDR_HEX(p->scan_rst.bda));
			ESP_LOGI(tag, "device type: %s", bt_dev_type_to_string(p->scan_rst.dev_type));
			ESP_LOGI(tag, "search_evt: %s", bt_gap_search_event_type_to_string(p->scan_rst.search_evt));
			ESP_LOGI(tag, "addr_type: %s", bt_addr_t_to_string(p->scan_rst.ble_addr_type));
			ESP_LOGI(tag, "rssi: %d", p->scan_rst.rssi);
			ESP_LOGI(tag, "flag: %d", p->scan_rst.flag);
			ESP_LOGI(tag, "num_resps: %d", p->scan_rst.num_resps);

			if (p->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
				ESP_LOGI(tag, "payload:");
				uint8_t len;
				uint8_t *data = esp_ble_resolve_adv_data(p->scan_rst.ble_adv, ESP_BLE_AD_TYPE_NAME_CMPL, &len);
				ESP_LOGI(tag, "len: %d, %.*s", len, len, data);
				ESP_LOGI(tag, "dump -");
				dump_adv_payload(p->scan_rst.ble_adv);
			}
			ESP_LOGI(tag, "");
		}
        break;
    default:
        break;
    }
	
} // gap_event_handler

static const char *bt_dev_type_to_string(esp_bt_dev_type_t type) {
	switch(type) {
	case ESP_BT_DEVICE_TYPE_BREDR:
		return "ESP_BT_DEVICE_TYPE_BREDR";
	case ESP_BT_DEVICE_TYPE_BLE:
		return "ESP_BT_DEVICE_TYPE_BLE";
	case ESP_BT_DEVICE_TYPE_DUMO:
		return "ESP_BT_DEVICE_TYPE_DUMO";
	default:
		return "Unknown";
	}
} // bt_dev_type_to_string

static const char *bt_addr_t_to_string(esp_ble_addr_type_t type) {
	switch(type) {
		case BLE_ADDR_TYPE_PUBLIC:
			return "BLE_ADDR_TYPE_PUBLIC";
		case BLE_ADDR_TYPE_RANDOM:
			return "BLE_ADDR_TYPE_RANDOM";
		case BLE_ADDR_TYPE_RPA_PUBLIC:
			return "BLE_ADDR_TYPE_RPA_PUBLIC";
		case BLE_ADDR_TYPE_RPA_RANDOM:
			return "BLE_ADDR_TYPE_RPA_RANDOM";
		default:
			return "Unknown addr_t";
	}
} // bt_addr_t_to_string

static const char *bt_gap_search_event_type_to_string(uint32_t searchEvt) {
	switch(searchEvt) {
		case ESP_GAP_SEARCH_INQ_RES_EVT:
			return "ESP_GAP_SEARCH_INQ_RES_EVT";
		case ESP_GAP_SEARCH_INQ_CMPL_EVT:
			return "ESP_GAP_SEARCH_INQ_CMPL_EVT";
		case ESP_GAP_SEARCH_DISC_RES_EVT:
			return "ESP_GAP_SEARCH_DISC_RES_EVT";
		case ESP_GAP_SEARCH_DISC_BLE_RES_EVT:
			return "ESP_GAP_SEARCH_DISC_BLE_RES_EVT";
		case ESP_GAP_SEARCH_DISC_CMPL_EVT:
			return "ESP_GAP_SEARCH_DISC_CMPL_EVT";
		case ESP_GAP_SEARCH_DI_DISC_CMPL_EVT:
			return "ESP_GAP_SEARCH_DI_DISC_CMPL_EVT";
		case ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT:
			return "ESP_GAP_SEARCH_SEARCH_CANCEL_CMPL_EVT";
		default:
			return "Unknown event type";
	}
} // bt_gap_search_event_type_to_string

/*
 * Convert a BT GAP event type to a string representation.
 */
static const char *bt_event_type_to_string(uint32_t eventType) {
	switch(eventType) {
		case ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT:
			return "ESP_GAP_BLE_ADV_DATA_SET_COMPLETE_EVT";
		case ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT:
			return "ESP_GAP_BLE_SCAN_PARAM_SET_COMPLETE_EVT";
		case ESP_GAP_BLE_SCAN_RESULT_EVT:
			return "ESP_GAP_BLE_SCAN_RESULT_EVT";
		case ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT:
			return "ESP_GAP_BLE_SCAN_RSP_DATA_SET_COMPLETE_EVT";
		default:
			return "Unknown event type";
	}
} // bt_event_type_to_string


void bt_task(void *ignore) {
	int errRc;
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	esp_bt_controller_init(&bt_cfg);
	int ret = esp_bluedroid_init();
    if (ret) {
        ESP_LOGE(tag, "init bluedroid failed\n");
        return;
    }

    ret = esp_bluedroid_enable();
    if (ret) {
        ESP_LOGE(tag, "init bluedroid failed2\n");
        return;
    }

	errRc = esp_ble_gap_register_callback(gap_event_handler);
	if (errRc != ESP_OK) {
		ESP_LOGE(tag, "esp_ble_gap_register_callback: rc=%d", errRc);
		goto end;
	}
	static esp_ble_scan_params_t ble_scan_params = {
	    .scan_type              = BLE_SCAN_TYPE_ACTIVE,
	    .own_addr_type          = BLE_ADDR_TYPE_PUBLIC,
	    .scan_filter_policy     = BLE_SCAN_FILTER_ALLOW_ALL,
	    .scan_interval          = 0x80,
	    .scan_window            = 0x30
	};
	errRc = esp_ble_gap_set_scan_params(&ble_scan_params);
	if (errRc != ESP_OK) {
		ESP_LOGE(tag, "esp_ble_gap_set_scan_params: rc=%d", errRc);
		goto end;
	}

	while (1) {
		ESP_LOGI(tag, "Start scanning ...");
		ESP_LOGI(tag, "");
		errRc = esp_ble_gap_start_scanning(15);
		if (errRc != ESP_OK) {
			ESP_LOGE(tag, "esp_ble_gap_start_scanning: rc=%d", errRc);
			goto end;
		}
		vTaskDelay(15000 / portTICK_PERIOD_MS);

		int i;
		for (i=10; i>0; i--) {
			ESP_LOGI(tag, "Rescan countdown %d", i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
	}
	
end:
	vTaskDelete(NULL);
} // bt_task


void app_main(void)
{
  xTaskCreatePinnedToCore(&bt_task, "btTask", 2048, NULL, 5, NULL, 0);
}

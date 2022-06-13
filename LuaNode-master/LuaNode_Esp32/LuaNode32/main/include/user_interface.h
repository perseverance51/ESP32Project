/*
 *  Copyright (C) 2013 -2014  Espressif System
 *
 */

#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

typedef enum _auth_mode {
    AUTH_OPEN           = 0,
    AUTH_WEP,
    AUTH_WPA_PSK,
    AUTH_WPA2_PSK,
    AUTH_WPA_WPA2_PSK,
    AUTH_MAX
} AUTH_MODE;

void system_restore(void);
void system_restart(void);
uint32 system_get_free_heap_size(void);

enum sleep_type {
	NONE_SLEEP_T	= 0,
	LIGHT_SLEEP_T,
	MODEM_SLEEP_T
};

#endif

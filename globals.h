#include <stdbool.h>


#ifndef GLOBALS_H
#define GLOBALS_H

int time_repeat;
char coin[10];

bool allow_spread_thread;
bool allow_alert_thread;
bool spread_alarm_activated;
bool alert_alarm_activated;
bool dual;


int alert_price;
int spread_neg;
int spread_pos;

#endif

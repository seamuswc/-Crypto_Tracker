
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../globals.h"
#include "../api/api.h"
#include "../threads/threads.h"

#ifndef COMMANDS_H
#define COMMANDS_H

//prints the coin to two decimal points, adds /n
//now
void print_coin_now();

//time
void change_time(char * arg2);

//coin
void change_coin(char * arg2);

//alert
int alert(char * price);

//spread
int spread(char * spread);

//stop & reset
int stop_alert();
void reset_alert();

//dual - prints BTC & ETH
void set_dual();

//exit
//this is handled in input exit(0)

//help
void list_commands();

#endif




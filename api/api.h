#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <sys/types.h> //Testing wifi connection
#include <sys/socket.h> //Testing wifi connection
#include <netinet/in.h> //Testing wifi connection
#include <math.h>
#include "../globals.h"

#ifndef API_H
#define API_H

struct memory {
    char *memory;
    size_t size;
};

//TEST
void test_api_returns_number(float (*func)(), const char* testName);

//parse api and gets price
float json_price(struct memory *chunk);

//CURL callback functions
size_t writecallback(char *buffer, size_t itemsize, size_t nitems, struct memory* chunk);

//get the BITCOIN price feed from Coinbase
float api();

//tests if internet exists
int test_wifi();


#endif
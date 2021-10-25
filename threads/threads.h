#include <pthread.h>
#include <unistd.h>
#include "../globals.h"
#include "../api/api.h"


#ifndef THREADS_H
#define THREADS_H

void * price_thread(void * arg);
int start_price_thread();

pthread_t pricethread;
pthread_t musicthread;
int thread_number;

int play_alert();
void * music();

void print_coin();

void _dual();

#endif


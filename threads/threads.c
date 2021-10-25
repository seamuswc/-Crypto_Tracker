#include "threads.h"

void _dual() {
    strcpy(coin, "btc");
    float btc = api();
    strcpy(coin, "eth");
    float eth = api();
    printf("BTC: %.2f \t ETH: %.2f \n", btc, eth);
}

void print_coin() {
    
    if(dual) {
        _dual();
        return;
    }

    bool allow_play_alert = false;
    float price = api();

    if (price != -1) {  
        printf("%.2f\n", price);
    
        if(price >= alert_price && allow_alert_thread == true) {
            alert_alarm_activated = true;
            allow_play_alert = true;
        }  

        if ( (price <= spread_neg || price >= spread_pos) && allow_spread_thread == true) {
            spread_alarm_activated = true;
            allow_play_alert = true;
        } 

        if(allow_play_alert)
            play_alert();
    }
    if(price == -1) {
        printf("\n%s is not found on the exchange, switching to BTC & ETH\n", coin);
        dual = true;   
    }
}

void * price_thread(void * arg) {
    int cancel = thread_number;
    while(1) {
        sleep(time_repeat);
        if(cancel != thread_number) {    //if a new thread that does the same thing, this one closes.
            pthread_exit(NULL);
        }
        print_coin();
    }
    return NULL;
}

int start_price_thread() {
  pthread_create(&pricethread, NULL, price_thread, NULL);
  thread_number++;  
  return 1;
}

//----

int play_alert() {
    pthread_create(&musicthread, NULL, music, NULL);
    return 0;
}



void * music() {
    while(1) {
       
        if(!allow_spread_thread && !allow_alert_thread) {   //shuts the thread down if user has asked it to stop
            pthread_exit(NULL); 
        }
        
        if(spread_alarm_activated) 
            system("say SPREAD SPREAD SPREAD");

        if(alert_alarm_activated )
            system("say ALERT ALERT ALERT");

        sleep(7);

    }
}



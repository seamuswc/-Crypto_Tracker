#include "commands.h"


//MAN pages
char commands_abc[9][150] = {
    "now, n\n"
    "\tPrints the price of current selected coin",
    "time-#, t-#\n"
    "\tSets the repeat time for price display\n"
    "\tDefault is 10\n"
    "\tDenominated in seconds\n"
    "\tLeave out -# to get current Time setting",
    "coin-TICKER, c-TICKER\n"
    "\tSets the coin to track\n"
    "\tWhen Ticker not set prints current coin\n"
    "\tDefualts to BTC",
    "alert-#\n"
    "\tPlays audio when price target is met\n"
    "\tLeave out -# to get current Alert setting",
    "spread-#\n"
    "\tPlays audio when spread+- is passed\n"
    "\tLeave out -# to get current Spread setting",
    "stop\n"
    "\tStops the alert and/or spread audio",
    "resets\n"
    "\tresets the alert and/or spread",
    "exit\n"
    "\tExits the program",
    "dual\n"
    "\tprints btc & eth"
};

void set_dual() {
    reset_alert();
    dual = true;
    _dual();
}

void print_coin_now() {
    float price = api();
    printf("%.2f\n", price);
}

void change_coin(char * arg2) {

    if( arg2 == NULL ) {
        fprintf(stderr, "%s %s %s", "Coin is set to" , coin , "\n");
        return;
    }
    
    if( arg2[0] == '\0' || arg2[0] == ' ' ) {
        fprintf(stderr, "%s %s %s", "No coin entered, currently tracking" , coin , "\n");
        return;
    }

    if(strlen(arg2) > 5) {
        fprintf(stderr, "%s", "Coin abbrvetion too big\n");
        return;
    }
    
    if(dual) {
        dual = false;
        printf("Coin has been switch from DUAL to %s \n", arg2);
        strcpy(coin, arg2);
    } else {
        char old_coin[10];
        strcpy(old_coin, coin); //need for the puts message below
        strcpy(coin, arg2);
        printf("Coin has been switch from %s to %s \n",  old_coin, arg2);
    }
    reset_alert(); //old alerts and spreads need to reset
    print_coin();
}

void change_time(char * arg2) {
    if(arg2 == NULL) {
        fprintf(stderr, "%s %d %s", "Time set to" , time_repeat, "\n");
        return;
    }

    if(!isdigit(*arg2)) { //trigger on single digits>
        fprintf(stderr, "%s", "Time must be a digit\n");
        return;
    }

    time_repeat = atoi(arg2);
    start_price_thread();
}

//--------------------------------------------------------------//



int alert(char * price) {
    if(dual) {
        printf("Cannot set alerts/spreads on DUAL\n");
        return 1;
    }
    if(price == NULL) {printf("Alert currently set to: %d\n", alert_price);}
    if(price != NULL) {
        //check for , & . and let use know this doenst work
        int new_price = atoi(price);
        if (new_price < 1)
        {
            puts("Alert Command only accepts numbers as a parameter. Example: alert-100000");
            return 0;
        }
        alert_price = new_price; 
        allow_alert_thread = true;
    }
    return 0;
}


int spread(char * _spread) {
    if(dual) {
        printf("Cannot set alerts/spreads on DUAL");
        return 1;
    }
    if(_spread == NULL) {printf("Spread currently set to: %d \t %d \n", spread_neg, spread_pos);}
    if(_spread != NULL) {
        //check for , & . and let use know this doenst work
        int new_spread = atoi(_spread);
        if (new_spread < 1)
        {
            puts("Spread Command only accepts numbers as a parameter. Example: spread-200");
            return 0;
        }
        float price = api();
        spread_neg = price - new_spread; 
        spread_pos = price + new_spread; 
        allow_spread_thread = true;
    }
    return 0;
}

int stop_alert() {
        
    if(spread_alarm_activated) {
        allow_spread_thread = false;
        spread_alarm_activated = false;
        spread_neg = 0;
        spread_pos = 0;
        puts("Spread has been reset!");
    }

    if(alert_alarm_activated) {
        allow_alert_thread = false;
        alert_alarm_activated = false;
        alert_price = 0;
        puts("Alert has been reset!");
    }

    return 0;
}

void reset_alert() {
        
    if(allow_spread_thread) {
        allow_spread_thread = false;
        spread_alarm_activated = false;
        spread_neg = 0;
        spread_pos = 0;
        puts("Spread has been reset!");
    }

    if(allow_alert_thread) {
        allow_alert_thread = false;
        alert_alarm_activated = false;
        alert_price = 0;
        puts("Alert has been reset!");
    }
}


void list_commands() {
    int l = sizeof(commands_abc) / sizeof(commands_abc[0]);
    printf("\n\n");
    for(int i = 0; i <= l; i++) {
        printf("%s\n\n", commands_abc[i]);
    }
}
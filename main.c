
#include "globals.h"
#include "commands/commands.h"
#include "IO/input.h"

int main(void) {
    time_repeat = 10;
    strcpy(coin, "btc");
    thread_number = 0;
    alert_price=0;
    spread_neg = 0;
    spread_pos = 0;
    allow_alert_thread = false;
    allow_spread_thread = false;
    spread_alarm_activated = false;
    alert_alarm_activated = false;

    print_coin();
    start_price_thread();

    while(1) {
        get_command();
    }

    pthread_join(pricethread, NULL);

return 0;


/*TESTS
    test_api_returns_number( &api , "test_api_returns_number\n\n");    
*/
}
#include "input.h"

int MAX_COMMAND_LENGTH = 100;

void get_command() {
    char * command_pointer = input();
    char * second = second_arg(command_pointer); //second needs to be before first
    char * first = first_arg(command_pointer);   //becuase first adds a /0 
    choose(first, second);
    free(command_pointer);   
}

char * input() {
  char * str = malloc(MAX_COMMAND_LENGTH);   
  if (fgets(str, MAX_COMMAND_LENGTH, stdin) != NULL) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n') {
      str[--len] = '\0';
    }
  }
  return str;
}

char * first_arg(char * arg) {  
    char * j = strchr(arg, '-');
    if(j==NULL) {
        return arg;
    }
    *j = '\0';
    return arg;
}

char * second_arg(char * arg) {  
    char * j = strchr(arg, '-');
    if( j==NULL  ) {
        return NULL;
    }
    return ++j; 
}


int choose(char * arg1, char *arg2) {

  if (strcmp(arg1, "now") == 0) {
    print_coin_now();
  } else if (strcmp(arg1, "n") == 0) {
    print_coin_now();
  } else if (strcmp(arg1, "c") == 0) {
    change_coin(arg2);
  } else if (strcmp(arg1, "time") == 0) {
    change_time(arg2);
  } else if (strcmp(arg1, "t") == 0) {
    change_time(arg2);
  } else if (strcmp(arg1, "coin") == 0) {
    change_coin(arg2);
  } else if (strcmp(arg1, "alert") == 0) {
    alert(arg2);
  } else if (strcmp(arg1, "spread") == 0) {
    spread(arg2);
  } else if (strcmp(arg1, "stop") == 0) {
    stop_alert();
  } else if (strcmp(arg1, "reset") == 0) {
    reset_alert();
  } else if (strcmp(arg1, "exit") == 0) {
    exit(0);
  } else if (strcmp(arg1, "help") == 0) {
    list_commands();
  } else if (strcmp(arg1, "dual") == 0) {
    set_dual();
  } else {
    puts("Command not Found");
  }
  return 0;
}

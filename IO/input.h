#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../globals.h"
#include "../commands/commands.h"

#ifndef INPUT_H
#define INPUT_H

//max text allowed to enter
extern int MAX_COMMAND_LENGTH;

//call the below functions to get, pars, execute command
void get_command();

//get the user's command
//return a malloc pointer that needs to be freed
char * input();

//parses the second part of the command
char * first_arg(char * arg);

//parses the first part of the command
char * second_arg(char * arg);

//Matches the users commands with functions to execute
int choose(char * arg1, char *arg2);

#endif




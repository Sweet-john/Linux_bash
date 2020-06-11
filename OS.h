#include <stdio.h>
#include <stdlib.h>
using namespace std;

//use "go" command to change the directory
void go(char *const argv[]);

//check if the command is "go" or "history" or "pid" then jump to the corresponding function
bool checkSpecialOrder(char *const argv[]);

//execute the command using fork() and execvp() function
void execute(char *const argv[]);

//store history commands in an array to be ready for user input "history" command
void setHistory();

//when user input "history" command, this function would output all history command in the array
void printHistory();

//store pids of child processes in a vector to be ready for user input "pid" command
void setPid(int pid);

//when user input "pid" command, this function would output 5 recent pid of child processes
void printPid();

//Bonus!! a user-friendly prompt which initialize the host name and current working directory
//before the money sign
void prompt();

void freeMemory();
/*
char *historyCommand[5000];
int historyCount=0;
vector<int>pidList;
char Command[80];
char originalCommand[80];
*/

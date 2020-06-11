#include <stdlib.h>
#include <stdio.h>
#define RUN 1
#define SUSPEND 2
#define TERMINATE 3


void kill_sig_handler(int sig);
void stp_sig_handler(int sig);
void cont(char*arg);
void printJobs();
void printStatus();
void bg(char*arg);
void fg(char*arg);

#include <stdio.h>
#include <stdlib.h>
using namespace std;

//divide multiple commands into unique command one by one and execute them
bool multiple(char *argv[],int size);

//if a command include "<" or ">", redirect its input or output, then recover it
//if a command include "|", jump to  pipe()
bool Redirection(char *argv[], int size);

//create a pipe , execute the command, then recover the output
void pipe(char *input[], char* output[]);

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <vector>
#include <fcntl.h>
#include "OS.h"
#include "OS2.h"
using namespace std;

bool multiple(char*argv[],int size)
{
 int n = 1;
 bool check = false;
	for (int i = 0; i<size; i++)
	{
	 	if (strchr(argv[i],';')!=NULL||i==size-1)
		{
		check = true;
		char* temp[20];
		int j;
		char *out;
		if (strcmp(argv[i],";")!=0)
		out = strtok(argv[i],";");
		for (j = 0; j < n; j++)
			{
			if (j == n-1 && strcmp(argv[i],";")!=0)
			temp[j] = out;
			else if (j == n-1 && strcmp(argv[i],";")==0)
			temp[j] = NULL;
			else
			temp[j] = argv[i+j-n+1];
			}
		temp[j]=NULL;
		if (Redirection(temp,n)) 
			{
			n = 1;
			continue;
			}
		n = 0;
		bool isSpecial = checkSpecialOrder(temp);
		if (!isSpecial)
		execute(temp);
		}
	 n++;
	}
 return check;
}

bool Redirection(char *argv[], int size)
{
 bool check = false;
	for (int i = 0 ; i < size ; i++)
	{

	if (check == true)
		break;

	if (strcmp(argv[i],">")==0)
		{
		check = true;
		int fdo = dup(STDOUT_FILENO);
		int fd = open(argv[i+1],O_WRONLY|O_CREAT,0666);
		int fd2 = dup2(fd,STDOUT_FILENO);
		int j = 0;
		char* temp[20];
		while(j<i)
			{
			temp[j]=argv[j];
			j++;
			}
		temp[j]=NULL;
		bool isSpecial = checkSpecialOrder(temp);
		if (!isSpecial)
		execute(temp);
		close(fd2);
		dup2(fdo,STDOUT_FILENO);
		}
	if (strcmp(argv[i],"<")==0)
		{
		check = true;
		int fdi = dup(STDIN_FILENO);
		int fd = open(argv[i-1],O_RDONLY);
		if (fd<0)
			{
			perror("Open error ");
			return check;
			}
		int fd2 = dup2(fd,STDIN_FILENO);
		char* temp[20];
		int j;
		for (j = 0; j < size-i-1 ; j++)
			temp[j]=argv[j+i+1];
		temp[j]=NULL;
		bool isSpecial = checkSpecialOrder(temp);
		if (!isSpecial)
		execute(temp);
		close(fd2);
		dup2(fdi,STDIN_FILENO);
		}
	if (strcmp(argv[i],"|")==0)
		{
		check = true;
		char* input[20];
		char* output[20];
		int j = 0;		
		while(j<i)
			{
			input[j]=argv[j];
			j++;
			}
		input[j]=NULL;
		
		for (j = 0; j < size-i-1 ; j++)
			output[j]=argv[j+i+1];
		output[j]=NULL;
		
		pipe(input,output);
		}
	}
 return check;
}

void pipe(char* input[], char* output[])
{
int fd[2];
 pipe(fd);
 if (fork()!=0)
 {
  close(fd[0]);
  int fdo = dup(STDOUT_FILENO);
  close(1);
  dup(fd[1]);
  close(fd[1]);
  bool isSpecial = checkSpecialOrder(input);
  if (!isSpecial)
  execute(input);
  dup2(fdo,STDOUT_FILENO);
  wait(NULL);
 }
else
 {
  close(fd[1]);
  close(0);
  dup(fd[0]);
  close(fd[0]);
  bool isSpecial = checkSpecialOrder(output);
  if (!isSpecial)
  execute(output);
  exit(0); 
 }
}

			



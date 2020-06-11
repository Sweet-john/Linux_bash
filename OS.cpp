#include <stdio.h>
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <vector>
#include "OS.h"
#include "OS2.h"
#include "OS3.h"
using namespace std;

char *historyCommand[5000];
int historyCount=0;
vector<int>pidList;
char Command[80];
int pid;
siginfo_t info;

bool checkSpecialOrder(char *const argv[])
{
 bool check = false;
 if (strcmp(argv[0],"go")==0)
	 {check = true ; go(argv);}
 else if
	 (strcmp(argv[0],"history")==0) {check = true ; printHistory();}
 else if
	 (strcmp(argv[0],"pid")==0) {check = true ; printPid();}
 else if 
	 (strcmp(argv[0],"continue")==0) {check = true ; cont(argv[1]);}
 else if 
	 (strcmp(argv[0],"jobs")==0) {check = true ; printJobs();}
 else if 
	 (strcmp(argv[0],"status")==0) {check = true ; printStatus();}
 return check;
}

void go(char *const argv[])
{
 if (chdir(argv[1])<0)
 perror("change directory fail");
 else
 cout<<"change directory success\n";
}

void setHistory()
{
 historyCommand[historyCount]=(char *)malloc(50*sizeof(char));
 memset(historyCommand[historyCount],0,50*sizeof(char));
 strcpy(historyCommand[historyCount],Command);
 historyCount++;
}

void printHistory()
{
 for(int i = 0; i<historyCount; i++)
 cout<<historyCommand[i]<<"\n";
}

void setPid(int id)
{
 pidList.push_back(id);
}

void printPid()
{
 int i = 0;
 int size = pidList.size();
 int j = 1;
 if (i<size-5)
  i = size - 5; 
  while(i<size)
  {
   cout<<"["<<size-i<<"] "<<pidList[size-j]<<"\n";
   i++;
   j++;
  }
}
 
void execute(char *const argv[])
{ 
 pid=fork();
 int success;
 if (pid!=0)
 { /*waitpid(pid,&success,0);
   if (WEXITSTATUS(success)==0)
	{
	setPid(pid);
	}*/
	waitid(P_PID,pid,&info,WEXITED|WSTOPPED);
	setPid(pid);
 }
 else
 {
	if (execvp(argv[0],argv)<0)
        {
		perror("Exec error ");
		exit(-1);
	}
 }
}

void prompt()
{
 char host[50];
 char cwd[50];
 gethostname(host,sizeof(host));
 getcwd(cwd,sizeof(cwd));
 cout<<"["<<host<<":"<<cwd<<"] $ ";
}

void freeMemory()
{
for (int i=0 ; i<historyCount;i++)
  free(historyCommand[i]);
}


int main()
{

 signal(SIGINT,kill_sig_handler);
 signal(SIGTSTP,stp_sig_handler);

 while(1)
 {
 prompt();
 cin.getline(Command,80);

 if (strcmp(Command,"exit")==0)
	{
	freeMemory();
	exit(0);
	}
 else if (Command == NULL)
 continue;
 
 setHistory();
 //check space
 char *temp = strtok(Command," ");
 vector<char*>obj;
 while (temp)
 	{
  	obj.push_back(temp);
  	temp = strtok(NULL," ");
 	}
 
 //obj to char
 char* a[obj.size()];
 int s;
 for (s = 0; s < obj.size() ;s++ )
	{
	  a[s]=obj[s];
 	}
 a[s]=NULL;

 multiple(a,obj.size());
 }
return 0;
}


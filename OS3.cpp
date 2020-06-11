#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <vector>
#include <fcntl.h>
#include "OS.h"
#include "OS2.h"
#include "OS3.h"




extern int pid;
extern siginfo_t info;

struct job
{
	int id;
	int status;
};

vector<struct job> jobList;

void kill_sig_handler(int sig)
{
	kill(pid,SIGINT);
	
	for (int i=0; i<jobList.size();i++)
	{
		if (pid==jobList[i].id)
			jobList[i].status = TERMINATE;
	}
	printf("\nThe current process has been killed\n");	
}

void stp_sig_handler(int sig)
{
	bool check = false;
	int sus;
	kill(pid,SIGSTOP);
	
	for (int i=0; i<jobList.size();i++)
	{
		if (pid!=jobList[i].id)
			continue;
		else
			{check = true; jobList[i].status = SUSPEND; sus = i+1; break;}
	}
	
	if (check == false)	
	{
		job temp;
		temp.id = pid;
		temp.status = SUSPEND;
		jobList.push_back(temp);
		sus = jobList.size();
	}
	printf("[%d] Suspend\n",sus);
}

void cont(char *arg)
{
	int i = atoi(arg);
	
	if (jobList[i-1].status == SUSPEND)
	{
	
	kill(jobList[i-1].id,SIGCONT);
	pid = jobList[i-1].id;
	jobList[i-1].status = RUN;
	
	waitid(P_PID,jobList[i-1].id,&info,WEXITED|WSTOPPED);
	
	if (info.si_code == CLD_STOPPED)
	jobList[i-1].status = SUSPEND;
	else if (info.si_code == CLD_EXITED || info.si_code == CLD_KILLED)
	jobList[i-1].status = TERMINATE;
	
	}
	else
	printf("Not a suspend job!\n");	
}

void printJobs()
{
	for (int i=0; i<jobList.size();i++)
	{
		switch (jobList[i].status)
		{
		case 1: printf("[%d] Running\n",i+1); break;
		case 2: printf("[%d] Suspended\n",i+1); break;
		case 3: printf("[%d] Terminated\n",i+1); break;
		}
	}	
}

void printStatus()
{
	printf("%d\n",info.si_status);		
}

void bg(char *arg)
{

		
}



void fg(char *arg)
{

}








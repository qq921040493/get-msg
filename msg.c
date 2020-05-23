#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>
#define MAX 1024
#define KEY 75
struct mymsg{ // 消息结构体
		long int mymsgtype; // 消息类型
		int text; // 消息内容
		}msg;
int main()
{
	pid_t pids;pid_t pidc;int msgid; int i=1;
	msgid=msgget(KEY,0666|IPC_CREAT);// 获得一个消息的描述符
	if((pids=fork())==0){ // 创建 Server 子进程
				while(i<11)
				{
					msg.mymsgtype=11-i;
					msg.text=i;
					printf("the sended message is %d th\n",i);i++;
					msgsnd(msgid,&msg,MAX,0);
					 // 向 msgid 指定的消息队列发送消息，长度为 1K
				}
				exit(0);
			     }
		else
		{
			i=10;
			if((pidc=fork())==0){ // 创建 Client 子进程
			while(i!=1)
			{
				msgrcv(msgid,&msg,MAX,0,0); 
				// 从 msgid 指定的消息队列接收消息
				printf("the message is %d th\n",msg.text);
				i=msg.mymsgtype;
			}
			exit(0);
		}
	else
	{
		 wait(0); 
		 wait(0);
		 exit(0);
	}
}
}

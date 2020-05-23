#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#define MAX 11
#define KEY 75
main()
{
	int i,child1,child2,running=1;// 定义子进程号
	int id;int *list;
	id=shmget(KEY,sizeof(int)*MAX,IPC_CREAT|0666); 
	// 建立一块共享存储区，返回该共享存储区的描述符 id
	list=(int*)shmat(id,0,0); // 将 list 指针指向共享存储区
	if((child1=fork())==-1)
	{
	 printf("error in fork a\n");
	 exit(1);
	}
	if(child1==0)
	{ 
	sleep(1);
	for(i=0;i<=10;i++)
	printf("your message is: %d \n",list[i]);
	exit(0);
	}
else
{
	if((child2=fork())==-1)
	{
	printf("error in fork a\n");
	exit(1);
	}
	if(child2==0)
	{ 
	i=0;
	while(1)
		{ 
			list[i]=i; // 向缓冲区里写入数据
			printf("the message sent is : %d\n",list[i]);
			if(list[i]==10)break;
			i++;
		}
	exit(0);
}
else
{ 
	wait(0);
	wait(0);
	shmdt(list); // 将共享存储区与进城断开
	shmctl(id,IPC_RMID,0);// 将共享存储区标志为被销毁的
	exit(0);
}
}
}

// ETC_test_tool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define  _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "ethercat.h"
#include "motor_def.h"

extern OSAL_THREAD_FUNC simpletest(void *ptr);
extern OSAL_THREAD_FUNC ecatcheck(void *ptr);
OSAL_THREAD_HANDLE thread1;
OSAL_THREAD_HANDLE thread2;


int main()
{
	printf("尔智机器人Ethercat测试小工具\n");
	char* buf[256] = { NULL };
	int choice = -1;
	int n = 1;

	ec_adaptert * adapter = NULL;
	printf("可用网卡:\n");
	adapter = ec_find_adapters();
	while (adapter != NULL)
	{
		printf("%d, 描述 : %s, 使用名称: %s\n", n, adapter->desc, adapter->name);
		buf[n - 1] = adapter->name;
		n++;
		adapter = adapter->next;
	}
	printf("请选择网卡(描述前数字):\n");

	while (1)
	{
		scanf("%d", &choice);
		if (choice > 0 && choice <= n) break;
		printf("输入不合法请重新输入.\n");
	}

	osal_thread_create(&thread1, 128000, &ecatcheck, (void*)&ctime);

	osal_thread_create(&thread2, 128000, &simpletest, (void*)(buf[choice - 1]));

	osal_usleep(2000000);

	if (ec_slavecount <= 0)
	{
		return 1;
	}

	while (1)
	{
		choice = -1;
		printf("\n\n选择要进行的操作:\n");
		printf("1.使能所有电机\n");
		printf("2.使能单一电机\n");
		printf("3.打印电机信息\n");
		printf("4.点动电机\n");
		printf("请输入之前的数字:");
		while (1)
		{
			scanf("%d", &choice);
			if (choice > 0 && choice <= 4) break;
			printf("输入不合法请重新输入.\n");
		}

		switch (choice)
		{
		case 1:
			enalbe_motor(-1);
			break;
		case 2:
			printf("选择电机(0~%d)\n", ec_slavecount - 1);
			choice = -1;
			while (1)
			{
				scanf("%d", &choice);
				if (choice >= 0 && choice < ec_slavecount) break;
				printf("输入不合法请重新输入.\n");
			}
			enalbe_motor(choice);
			break;
		case 3:
			print_infomation();
			break;
		case 4:
			int id, pos, time;
			printf("依次输入电机号(0~%d)，运动增量（单位千分之一度），运动时间（单位秒）。\n", ec_slavecount - 1);
			scanf("%d %d %d", &id, &pos, &time);
			run_motor(id, pos, time);
		default:
			break;
		}
		printf("指令执行结束.\n");

	}
	printf("程序运行结束\n");
	return (0);
}

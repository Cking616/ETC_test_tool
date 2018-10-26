#include "ethercat.h"
#include "motor_def.h"

void enalbe_motor(int i)
{
	if (i == -1)
	{
		for (int j = 0; j < ec_slavecount; j++)
		{
			if ((motion_rx_buf[j].status_word & 0xff) != 0x37)
			{
				motion_tx_buf[j].control_word = 15; //打开电机
				motion_tx_buf[j].mod = 8;
				motion_tx_buf[j].target_position = motion_rx_buf[j].actual_position;
			}
		}
	}
	else if (i >= 0 && i < 6)
	{
		motion_tx_buf[i].control_word = 15; //打开电机
		motion_tx_buf[i].mod = 8;
		motion_tx_buf[i].target_position = motion_rx_buf[0].actual_position;
	}
}

void print_infomation(void)
{
	for (int i = 0; i < ec_slavecount; i++)
	{
		printf("motor %d:\n", i);
		printf("status word: %4.4x ", motion_rx_buf[i].status_word);
		printf("extern position: %d ", motion_rx_buf[i].actual_external_position);
		printf("position: %d ", motion_rx_buf[i].actual_position);
		printf("velocity: %d ", motion_rx_buf[i].actual_velocity);
		printf("control mod: %d\n", motion_rx_buf[i].display_mod);
	}
}

void run_motor(int i, int pos, int time)
{
	if (i < 0 || i >= ec_slavecount)
	{
		printf("请选择正确的电机！\n");
	}

	if (motion_tx_buf[i].control_word != 15)
	{
		printf("电机未使能！\n");
	}

	int spec = time * 1000 / 5;
	int res = pos % spec;
	int pec = pos / spec;
	int target_pos = pos + motion_rx_buf[i].actual_position;
	int cur_pos = motion_rx_buf[i].actual_position;

	motion_tx_buf[i].target_position = cur_pos + res;
	while (1)
	{
		osal_usleep(CONTROL_PERIOD);
		if (motion_tx_buf[i].target_position == target_pos) break;
		motion_tx_buf[i].target_position += pec;
	}
}

#pragma once

#pragma pack(1)
// 实时发送数据
typedef struct
{
	unsigned short control_word; //关节控制字
	int			   target_position; //位置环-目标位置
	int			   target_velocity; //速度环-目标速度
	short		   target_torque;	//力矩环-目标力矩
	char		   mod;				//模式- 8:位置环控制，9:速度环控制，10:力矩环控制
	char		   unused;
}tx_pdo_struct;

// 实时接收数据
typedef struct
{
	unsigned short status_word;
	int			   actual_position; //光编位置
	int			   actual_velocity;
	int			   actual_external_position; //磁编位置
	short		   actual_torque;
	char		   display_mod;
	char		   unused;
}rx_pdo_struct;
#pragma pack()

extern tx_pdo_struct motion_tx_buf[6];
extern rx_pdo_struct motion_rx_buf[6];

void enalbe_motor(int i);
void print_infomation(void);
void run_motor(int i, int pos, int time);
#define CONTROL_PERIOD 5000  //主站控制周期5ms
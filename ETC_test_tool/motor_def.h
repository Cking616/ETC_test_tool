#pragma once

#pragma pack(1)
// ʵʱ��������
typedef struct
{
	unsigned short control_word; //�ؽڿ�����
	int			   target_position; //λ�û�-Ŀ��λ��
	int			   target_velocity; //�ٶȻ�-Ŀ���ٶ�
	short		   target_torque;	//���ػ�-Ŀ������
	char		   mod;				//ģʽ- 8:λ�û����ƣ�9:�ٶȻ����ƣ�10:���ػ�����
	char		   unused;
}tx_pdo_struct;

// ʵʱ��������
typedef struct
{
	unsigned short status_word;
	int			   actual_position; //���λ��
	int			   actual_velocity;
	int			   actual_external_position; //�ű�λ��
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
#define CONTROL_PERIOD 5000  //��վ��������5ms
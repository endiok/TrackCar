#include "MPU6050.h"

u8 mpu6050_write(u8 addr, u8 reg, u8 len, u8* buf)//����ֵ 0�����ɹ�  -1����ʧ��
{ 
		 unsigned char i;
     addr=addr<<1;                     //ע��dma���ַ���������һλ����Ҫ��λ
		 MPU6050_IIC_Start();              //��������
		 MPU6050_IIC_Send_Byte(addr);      //����������ַ           
		 MPU6050_IIC_Send_Byte(reg);       //���������ӵ�ַ

		 for(i=0;i<len;i++)            
			 MPU6050_IIC_Send_Byte(*buf++);  //��������
		 MPU6050_IIC_Stop();               //��������

		 return 0;
}

u8 mpu6050_read(u8 addr, u8 reg, u8 len, u8 *buf)//����ֵ 0�����ɹ�  -1����ʧ��
{
		 unsigned char i;
     addr=addr<<1;                     //ע��dma���ַ���������һλ����Ҫ��λ
		 MPU6050_IIC_Start();              //��������           
		 MPU6050_IIC_Send_Byte(addr);      //����������ַ            
		 MPU6050_IIC_Send_Byte(reg);       //���������ӵ�ַ

		 MPU6050_IIC_Start();              //������������
		 MPU6050_IIC_Send_Byte(addr+1);
		 for(i=0;i<len-1;i++)  
			 *buf++=MPU6050_IIC_Read_Byte(0);//��������
		 *buf=MPU6050_IIC_Read_Byte(1);
		 MPU6050_IIC_Stop();               //��������
	
		 return 0;
}

void mpu6050_write_reg(u8 reg, u8 dat)
{
   mpu6050_write(SlaveAddress,reg,1,&dat);
}

u8   mpu6050_read_reg (u8 reg)
{
	 u8 dat;
   mpu6050_read(SlaveAddress,reg,1,&dat);
	 return dat;
}

void MPU6050_Init(void)
{
    MPU6050_IIC_IO_Init(); 
 	
		mpu6050_write_reg(PWR_MGMT_1,	 0X00);	//����MPU6050 
    mpu6050_write_reg(SMPLRT_DIV,  0x07); //�����ǲ�����125Hz
    mpu6050_write_reg(CONFIG,      0x06); //��ͨ�˲�Ƶ��5Hz
	  mpu6050_write_reg(GYRO_CONFIG, 0x18); //�������Լ켰������Χ:���Լ죬2000deg/s
	  mpu6050_write_reg(ACCEL_CONFIG,0x01); //���ټ��Լ졢������Χ����ͨ�˲�Ƶ��:���Լ죬2G��5Hz
}
 

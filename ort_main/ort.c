
#include "ort.h"
#include "mpu6050.h"
#include "speedcalc.h"
#include "main.h"
#include "adc.h"
//#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "gpio.h"
#include "MY_NRF24.h"
#include "stdio.h"

MPU6050_t MPU6050;
//////////////////////////shoot
unsigned int adc_value;
#define min_adc 1500
#define max_adc 1900
unsigned int a=0;    // a calculate in exam
//////////////////////////////

////////////////////////NRF
uint8_t spiData[2];
	uint64_t RxpipeAddrs = 0x11223344AA;
char myRxData[50];
char myAckPayload[32] = "Ack by STMF7!";
uint64_t TxpipeAddrs = 0x11223344AA;
char myTxData[32]; //= "Ehsan";
char AckPayload[32];
/////////////////////////////


/////////////////////spi
signed short send_data_arm_to_fpga[5]={0};  
signed char recive_data_arm_to_fpga[2]={0};	
/////////////////////

void setup()
{
	HAL_Delay(500);
//	MPU6050_Init(&hi2c2);
	HAL_Delay(500);
	while(HAL_ADCEx_Calibration_Start(&hadc1)!=HAL_OK)
	{};
//	while (MPU6050_Init(&hi2c2) == 1)
	{
//		HAL_Delay(100);
	};
	
	
	
	
	///spi nrf
	//HAL_SPI_Receive_IT(&hspi2,(uint8_t*)recive_data_arm_to_fpga, 2);	
	///////////////

	/////////////NRF

	//recive
	//NRF24_begin(GPIOA,CSN_GPIO_Port,CE_GPIO_Port, CSN_Pin, CE_Pin, hspi1);
	//**** TRANSMIT - ACK ****//

	/*NRF24_startListening();
	NRF24_openReadingPipe(1, RxpipeAddrs);
	
	NRF24_setAutoAck(true);
	NRF24_setChannel(52);
	NRF24_setPayloadSize(32);
	

	NRF24_enableDynamicPayloads();
	NRF24_enableAckPayload();*/
	
	//send
	/*NRF24_stopListening(); 
	NRF24_openWritingPipe(TxpipeAddrs);
	
	
	NRF24_setAutoAck(true);
	NRF24_setChannel(52);
	NRF24_setPayloadSize(32);
	
	NRF24_enableDynamicPayloads();
	NRF24_enableAckPayload();*/
	
	/////////////////////
	
	
}
void loop()
{
	while(1)
		{
			////////////////////shoot 
		HAL_ADC_Start_IT(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 1000);
		adc_value = HAL_ADC_GetValue(&hadc1);
		//HAL_ADC_Stop (&hadc1);
				if(adc_value > a)
			{
				HAL_GPIO_WritePin(LED_L3_GPIO_Port,LED_L3_Pin,GPIO_PIN_SET);//LED OFF
				HAL_GPIO_WritePin(FPGA_1_GPIO_Port,FPGA_1_Pin,GPIO_PIN_SET);//stop charg
				a=min_adc;
			}
		else
			{
				HAL_GPIO_WritePin(LED_L3_GPIO_Port,LED_L3_Pin,GPIO_PIN_RESET);//LED ON
				HAL_GPIO_WritePin(FPGA_1_GPIO_Port,FPGA_1_Pin,GPIO_PIN_RESET);//charging
				a=max_adc;
			}
			////////////////////
				
				
			//////////////////////////raed all gyro data
	//		MPU6050_Read_All(&hi2c2, &MPU6050);
	//		MPU6050_Read_Temp(&hi2c2, &MPU6050);
			///////////////////////////
			
		//	HAL_SPI_Transmit(&hspi2,(uint8_t*)tx,
			
			//////////NRF
		/*	HAL_GPIO_WritePin(CSN_GPIO_Port,CSN_Pin,GPIO_PIN_SET);
			HAL_Delay(10);
			//Read Data
			//1. put csn low
			HAL_GPIO_WritePin(CSN_GPIO_Port,CSN_Pin,GPIO_PIN_RESET);
			//2. transmit register address
			spiData[0]=0x05;
			HAL_SPI_Transmit(&hspi1,spiData,1,10);
			//3. read
			HAL_SPI_Receive(&hspi1,&spiData[1],1,10);
			//4. bring cs high
			HAL_GPIO_WritePin(CSN_GPIO_Port,CSN_Pin,GPIO_PIN_SET);
			*/
			
			
			
			
			
			
			//send
			/*myTxData[0] = 1;
			NRF24_write(myTxData, 32);
			HAL_Delay(100);
			myTxData[0] = 0;
			NRF24_write(myTxData, 32);
			HAL_Delay(100);*/
			
			
		
			//recive
			//if(NRF24_available())
			/*	{
				NRF24_available();
		NRF24_read(myRxData, 32);
		if(myRxData[0]==0){
		HAL_GPIO_WritePin(LED_L3_GPIO_Port,LED_L3_Pin,GPIO_PIN_SET);
		
		}
		
		if(myRxData[0]==1){
		HAL_GPIO_WritePin(LED_L3_GPIO_Port,LED_L3_Pin,GPIO_PIN_RESET);
		
		}
		
		}*/
			
			//
			
			
			//////////////////
			
			
			
			
				
			////////////////////////////recive data from fpga
			//while(HAL_SPI_Receive_DMA(&hspi1,(uint8_t*)recive_data_arm_to_fpga,2)!=HAL_OK)
		//	{
			//	HAL_GPIO_WritePin(LED_L3_GPIO_Port,LED_L3_Pin,GPIO_PIN_RESET);
			//}	
		//	HAL_SPI_Transmit_DMA(&hspi1,(uint8_t*)send_data_arm_to_fpga,5);
			//////////////////////////////////
			
			
			
			//wheels_velocity_calculate( recive_data_arm_to_fpga[0], recive_data_arm_to_fpga[1], MPU6050.Gy, MPU6050.KalmanAngleY );
		}
}
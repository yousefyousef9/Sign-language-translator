#include "main.h"

// VARIABLES
UART_HandleTypeDef UART1_settings ;
TIM_HandleTypeDef TIM_settings ;

GPIO_PinState state;

uint8_t start_the_game = 0 ;
uint8_t b1 = 1 ;
uint8_t b2 = 2 ;
uint8_t b3 = 3 ;

 
 uint8_t ADC1_VALUE;
 ADC_HandleTypeDef Adc1_settings;
	ADC_ChannelConfTypeDef ADC_ChannelStruct1;
 
 uint8_t ADC2_VALUE;
 ADC_HandleTypeDef Adc2_settings;
 	ADC_ChannelConfTypeDef ADC_ChannelStruct2;

 uint8_t ADC3_VALUE;
 ADC_HandleTypeDef Adc3_settings;
 	ADC_ChannelConfTypeDef ADC_ChannelStruct3;



void button_SETTINGS (void){
	
	__HAL_RCC_GPIOA_CLK_ENABLE();								 
	
	GPIO_InitTypeDef PushButton_settings;  				
	
	PushButton_settings.Mode = GPIO_MODE_INPUT;	 
	PushButton_settings.Pin = GPIO_PIN_0;			  	
	PushButton_settings.Pull = GPIO_NOPULL; 			
	
	HAL_GPIO_Init(GPIOA, &PushButton_settings);		

}

 













//
void uart_SETTINGS (void) {

// RX - PA10
// TX - PA9
	__HAL_RCC_GPIOA_CLK_ENABLE(); 
	GPIO_InitTypeDef GPIO_UART_SETTINGS ; 
	
	GPIO_UART_SETTINGS.Mode = GPIO_MODE_AF_PP ; 
	GPIO_UART_SETTINGS.Pin = GPIO_PIN_10 | GPIO_PIN_9 ;  
	GPIO_UART_SETTINGS.Pull = GPIO_NOPULL; 
	GPIO_UART_SETTINGS.Speed = GPIO_SPEED_HIGH ;
	GPIO_UART_SETTINGS.Alternate = GPIO_AF7_USART1 ;
	HAL_GPIO_Init(GPIOA, &GPIO_UART_SETTINGS); 
	
	

__HAL_RCC_USART1_CLK_ENABLE ();
	
UART1_settings.Instance = USART1;
	
UART1_settings.Init.BaudRate = 			9600 ;
UART1_settings.Init.WordLength = 		UART_WORDLENGTH_8B ;
UART1_settings.Init.OverSampling =	UART_OVERSAMPLING_16;
UART1_settings.Init.HwFlowCtl = 		UART_HWCONTROL_NONE ;
UART1_settings.Init.Mode = 					UART_MODE_TX_RX ;
UART1_settings.Init.Parity = 				UART_PARITY_NONE ;
UART1_settings.Init.StopBits = 			UART_STOPBITS_1 ;

HAL_UART_Init (&UART1_settings) ;

}


//
void timer_SETTINGS (void) {
		__HAL_RCC_TIM2_CLK_ENABLE();	
	
	TIM_settings.Instance 						= TIM2;					
	TIM_settings.Init.Prescaler   		= 1000;
	TIM_settings.Init.CounterMode 		= TIM_COUNTERMODE_UP;
	TIM_settings.Init.Period 						= 8000;
																
	while (HAL_TIM_Base_Init(&TIM_settings)!= HAL_OK){}

	HAL_TIM_Base_Start(&TIM_settings);

	
}
//
//
void ADC_GPIO_Config(void);
void ADC1_Config(void);
void ADC2_Config(void);
void ADC3_Config(void) ;

//
int main(void)
{
  HAL_Init();
  SystemClock_Config();

	button_SETTINGS ();
	uart_SETTINGS () ;
	timer_SETTINGS () ;
	
	ADC_GPIO_Config();
	
	ADC1_Config();
	HAL_ADC_Start (&Adc1_settings );

	ADC2_Config();
	HAL_ADC_Start (&Adc2_settings );

		ADC3_Config();
	HAL_ADC_Start (&Adc3_settings );

	while (1) {
		state = HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0); 
    
		ADC1_VALUE = HAL_ADC_GetValue(&Adc1_settings);
		ADC2_VALUE = HAL_ADC_GetValue(&Adc2_settings);
		ADC3_VALUE = HAL_ADC_GetValue(&Adc3_settings);
}
}
//
void TIM2_IRQHandler(void){
	HAL_TIM_IRQHandler ( &TIM_settings );
	
	if(state)
	{
	 HAL_UART_Transmit(&UART1_settings, &start_the_game , 1 , 0xFF );
	}
	
	 HAL_UART_Transmit(&UART1_settings, &b1 , 1 , 0xFF );
	 HAL_UART_Transmit(&UART1_settings, &ADC1_VALUE , 1 , 0xFF );
	
	 HAL_UART_Transmit(&UART1_settings, &b2 , 1 , 0xFF );
	 HAL_UART_Transmit(&UART1_settings, &ADC2_VALUE , 1 , 0xFF );

	 HAL_UART_Transmit(&UART1_settings, &b3 , 1 , 0xFF );
	 HAL_UART_Transmit(&UART1_settings, &ADC3_VALUE , 1 , 0xFF );
}




//
void ADC_GPIO_Config(void)
	{
	GPIO_InitTypeDef GPIO_InitStruct;

	__HAL_RCC_GPIOC_CLK_ENABLE();	

	GPIO_InitStruct.Pin 	=GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2  ;
												//channel 10  	11 			 			12
	GPIO_InitStruct.Mode 	= GPIO_MODE_ANALOG;
	GPIO_InitStruct.Pull 	= GPIO_NOPULL;
		
	HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

}


//
void ADC1_Config(void)
{


	
	__HAL_RCC_ADC1_CLK_ENABLE();

	Adc1_settings.Instance 											= ADC1;
	Adc1_settings.Init.ClockPrescaler 					= ADC_CLOCKPRESCALER_PCLK_DIV2;
	Adc1_settings.Init.Resolution 							= ADC_RESOLUTION_8B;
	Adc1_settings.Init.ScanConvMode 						= DISABLE;								// 1 Channel
	Adc1_settings.Init.ContinuousConvMode 			= ENABLE;
	Adc1_settings.Init.DiscontinuousConvMode 	= DISABLE;
	Adc1_settings.Init.NbrOfDiscConversion 		= 0;
	Adc1_settings.Init.ExternalTrigConvEdge 		= ADC_EXTERNALTRIGCONVEDGE_NONE;
	Adc1_settings.Init.ExternalTrigConv 				= ADC_EXTERNALTRIGCONV_T1_CC1;
	Adc1_settings.Init.DataAlign 							= ADC_DATAALIGN_RIGHT;
	Adc1_settings.Init.NbrOfConversion 				= 1;
	Adc1_settings.Init.DMAContinuousRequests 	= ENABLE;
	Adc1_settings.Init.EOCSelection 						= DISABLE;

	HAL_ADC_Init(&Adc1_settings);

		ADC_ChannelStruct1.Channel = ADC_CHANNEL_11;
	ADC_ChannelStruct1.Rank = 1;
	ADC_ChannelStruct1.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC_ChannelStruct1.Offset = 0;

if (HAL_ADC_ConfigChannel(&Adc1_settings, &ADC_ChannelStruct1) != HAL_OK)
	{
		Error_Handler();
	}

}
//
void ADC2_Config(void)
{


		__HAL_RCC_ADC2_CLK_ENABLE();


	Adc2_settings.Instance 											= ADC2;
	Adc2_settings.Init.ClockPrescaler 					= ADC_CLOCKPRESCALER_PCLK_DIV2;
	Adc2_settings.Init.Resolution 							= ADC_RESOLUTION_8B;
	Adc2_settings.Init.ScanConvMode 						= DISABLE;								// 1 Channel
	Adc2_settings.Init.ContinuousConvMode 			= ENABLE;
	Adc2_settings.Init.DiscontinuousConvMode 	= DISABLE;
	Adc2_settings.Init.NbrOfDiscConversion 		= 0;
	Adc2_settings.Init.ExternalTrigConvEdge 		= ADC_EXTERNALTRIGCONVEDGE_NONE;
	Adc2_settings.Init.ExternalTrigConv 				= ADC_EXTERNALTRIGCONV_T1_CC1;
	Adc2_settings.Init.DataAlign 							= ADC_DATAALIGN_RIGHT;
	Adc2_settings.Init.NbrOfConversion 				= 1;
	Adc2_settings.Init.DMAContinuousRequests 	= ENABLE;
	Adc2_settings.Init.EOCSelection 						= DISABLE;

	HAL_ADC_Init(&Adc2_settings);

		ADC_ChannelStruct2.Channel = ADC_CHANNEL_10;
	ADC_ChannelStruct2.Rank = 1;
	ADC_ChannelStruct2.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC_ChannelStruct2.Offset = 0;

if (HAL_ADC_ConfigChannel(&Adc2_settings, &ADC_ChannelStruct2) != HAL_OK)
	{
		Error_Handler();
	}

}

//
void ADC3_Config(void)
{


		__HAL_RCC_ADC3_CLK_ENABLE();


	Adc3_settings.Instance 											= ADC3;
	Adc3_settings.Init.ClockPrescaler 					= ADC_CLOCKPRESCALER_PCLK_DIV2;
	Adc3_settings.Init.Resolution 							= ADC_RESOLUTION_8B;
	Adc3_settings.Init.ScanConvMode 						= DISABLE;								// 1 Channel
	Adc3_settings.Init.ContinuousConvMode 			= ENABLE;
	Adc3_settings.Init.DiscontinuousConvMode 	= DISABLE;
	Adc3_settings.Init.NbrOfDiscConversion 		= 0;
	Adc3_settings.Init.ExternalTrigConvEdge 		= ADC_EXTERNALTRIGCONVEDGE_NONE;
	Adc3_settings.Init.ExternalTrigConv 				= ADC_EXTERNALTRIGCONV_T1_CC1;
	Adc3_settings.Init.DataAlign 							= ADC_DATAALIGN_RIGHT;
	Adc3_settings.Init.NbrOfConversion 				= 1;
	Adc3_settings.Init.DMAContinuousRequests 	= ENABLE;
	Adc3_settings.Init.EOCSelection 						= DISABLE;

	HAL_ADC_Init(&Adc3_settings);

		ADC_ChannelStruct3.Channel = ADC_CHANNEL_12;
	ADC_ChannelStruct3.Rank = 1;
	ADC_ChannelStruct3.SamplingTime = ADC_SAMPLETIME_480CYCLES;
	ADC_ChannelStruct3.Offset = 0;

if (HAL_ADC_ConfigChannel(&Adc3_settings, &ADC_ChannelStruct3) != HAL_OK)
	{
		Error_Handler();
	}

}
//

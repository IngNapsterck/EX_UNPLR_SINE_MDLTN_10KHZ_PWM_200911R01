/*
 * este programa genera una señal de PWM senoidal de tipo unipolar
 * para la modulacion se usa cmo base la simulacion de Matlab Simulink
 * llamada INVRTR_UNPLR200304R01.slx.
 *
 * para la generacion de las señales de salida del PWM se emplea una
 * interrrupcion por flanco de caida de la señal de PWM donde se
 * hacen los calculos que luego seran empleados para cargar el valor
 *  de la nuevo valor de duracion de pulso.
 *
 *  la señal de salida esta armada por pulsos con sus señales negadas para
 *  poder dsparar un inversor monofasico con latopologia en puente H.
 *  la construccion del puente emplea transistores de tipo P para la parte
 *  superior y de tipo N para la seccion inferior.
 *  se inserta un Dead time entre las señales simetricas del PWM con
 *  valor de 115 Bits.
 *
 *  la frecuencia es ajustable por medio de un pulsador que al detectar una
 *  interrupcion por flanco de subida, este incrementa 10 Hz a la frecuencia
 *  de salida de las señales senoidales del modulador.
 *
 *  tambien se crean dos pines que permiten señalar el cambio de estado
 *  de la interrupcion por finalizacion del PWM y por activacion de la
 *  interrupcion del boton para el cambio de frecuencia.
 *
 *  Para la generacion de la señal PWM se emplea en Timer1.
 *  la senal PWM es tiene una frecuencia de 10.33 KHz y 11 bits de resolucion
 *  el reloj del uC esta trabajando a 170 MHz
 *  Este programa corre dentro de la plataforma Cube IDE de ST.
 *  Para la generacion del algoritmo de calculo de la duracion de los pulsos
 *  se emplea la  libreria CMSIS DSP sobre el microcontrolador STM32G474RE.
 *  por problemas de interferencia entre los canales 1 y 2 de las salidas PWM
 *  se emplean los canales 1 y 3 del Timer1 como salidas PWM
 *
 *  +++++ Al actualizar los valores del PWM con una interrrupcion por flnaco de bajada
 *  +++++ nos aseguramos que el PWM haya terminado su accion y actualicemos su valor con cada
 *  +++++ nueva activacion de la señal
 *
 *  los pines de salida son los siguentes:
 *
 *  señal senoidal sin desfase
 *
 *  PC0 como señal PWM no negada
 *  PA11 como señal PWM negada
 *
 *  señal senoidal defasada 180°
 *
 *  PC2 como señal PWM no negada
 *  PB1 como señal PWM negada
 *
 *  PA12 como pin de salida llamado Flag
 *
 *  PC13 como entrada de interrupcion por flanco de subida
 */


/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/

#define ARM_MATH_CM4 // se incluyen la directiva del procesador a usar
#include "arm_math.h" // se agrega la libreria matematica de DSP


/* Private define ------------------------------------------------------------*/

#define pi 3.1415926 // se define el valor de Pi en este programa
#define step 10		// se asignan los pasos de cambio de frecuencia



/* USER CODE BEGIN PV */
float32_t w, f, sine_step = 0; //variables para almacenar los valores de la frecuencia en radianes y el valor del PWM
uint16_t counter = 0;		   // contador para saber cuanto desplazar el valor de X de la senoidal de 0 a 2pi
uint16_t pwm_sine1, pwm_sine2 = 0;// valores a cargar en los PWM para el sigeuinte disparo de PWM 1 y 3


/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);



int main(void)
{

  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_TIM1_Init();


HAL_TIM_PWM_Start_IT(&htim1, TIM_CHANNEL_1); // configuracion de canal 1 del timer1 como salida PWM NO negada y ademas como interrupcion
HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);// configuracion de la salida PWM negada del canal 1

HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);// configuracion de la salida PWM NO negada del canal 3
HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_3);// configuracion de la salida PWM negada del canal 1


  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}


void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage 
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1_BOOST);
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV6;
  RCC_OscInitStruct.PLL.PLLN = 85;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_8) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)// interrupcion por accion del boton PC13
{

	HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET); // encendemos en LED de señalizacion mientras el programa entre en esta interrupcion.

	f = f + step ;// incrementamos los valores de la frencuencia 10 Hz.
	if(f >= 120)
	{
		f = 0; // si f alcanza una frecuencia de 120 Hz regresa a una frecuencia de 0 Hz
	}
}

void HAL_TIM_PWM_PulseFinishedCallback(TIM_HandleTypeDef *htim)
{

	w = 2 * pi * f; // calcula el valor de la frecuencia en radianes por segundo
	sine_step = ( w / 10333 ); // si el PWM es de 10.33 kHz, calcula cuanto debe de avanzar x en radianes para que cada segundo se de la frecuencia w

	pwm_sine1 = (uint16_t) (2046 / 2) * ( arm_sin_f32( counter * sine_step ) + 1 ); // se calcula el valor de la señal senoidal sin desafase
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, pwm_sine1);// se carga el nuevo valor de la señal seno en el registro PWM para su activacion.

	w = w + pi; // se hace el desafase de la señal 180° o un valor de pi radianes
	pwm_sine2 = (uint16_t) (2046 / 2) * ( arm_sin_f32( (counter * sine_step) + pi ) + 1 );// se calcula el valor de la señal senoidal con desafase
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, pwm_sine2);// se carga el nuevo valor de la señal seno en el registro PWM para su activacion.

	counter++; // se salta un paso para que la siguiente interrupcion se valcule un nuevo valor de la senoidal
	if(counter > 10333)
	{
		counter = 0;// si la señal senoidal ha terminado de formarse se reinicia el valor de x para comenzar de nuevo a armar la senoidal
	}

	if(f == 0) // si la frecuencia de entrada  es cero  que no se active las señales PWM de ningun canal
	{
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);// PWM1 apagado
		__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);// PWM3 apagado
	}

}


/* USER CODE END 4 */

void Error_Handler(void)
{


}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

# EX_UNPLR_SINE_MDLTN_10KHZ_PWM_200911R01
este programa permite generar una salida PWM senoidal de tipo unipolar, para un inversor monofasico de puente completo


este programa genera una señal de PWM senoidal de tipo unipolar
 * para la modulacion se usa como base la simulacion de Matlab Simulink
 * llamada INVRTR_UNPLR200304R01.slx.
 *
 * para la generacion de las señales de salida del PWM se emplea una
 * interrrupcion por flanco de caida de la señal de PWM donde se
 * hacen los calculos que luego seran empleados para cargar el valor
 *  de la nuevo valor de duracion de pulso.
 *
 *  la señal de salida esta armada por pulsos con sus señales negadas para
 *  poder dsparar un inversor monofasico con la topologia en puente H.
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
 *  +++++ Al actualizar los valores del PWM con una interrupcion por flnaco de bajada
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

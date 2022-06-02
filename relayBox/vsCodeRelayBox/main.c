
#define F_CPU 12000000UL
#include "mega8.h"
#include "dio.h"
#include "uart.h"
#include "softwareDelay.h"

#define RELAY_1_GPIO    GPIOC
#define RELAY_1_PIN     PIN5
#define RELAY_2_GPIO    GPIOC
#define RELAY_2_PIN     PIN4
#define RELAY_3_GPIO    GPIOC
#define RELAY_3_PIN     PIN3
#define RELAY_4_GPIO    GPIOC
#define RELAY_4_PIN     PIN2

uint8 relay_1_State = 0;
uint8 relay_2_State = 0;
uint8 relay_3_State = 0;
uint8 relay_4_State = 0;
uint8 rxFlag = 0;

int main(void)
{
    DIO_Cfg_s str_Dio;

    str_Dio.GPIO = RELAY_1_GPIO;
    str_Dio.pins = RELAY_1_PIN;
    str_Dio.dir = OUTPUT;
    DIO_init(&str_Dio);
    
    str_Dio.GPIO = RELAY_2_GPIO;
    str_Dio.pins = RELAY_2_PIN;
    DIO_init(&str_Dio);
    
    str_Dio.GPIO = RELAY_3_GPIO;
    str_Dio.pins = RELAY_3_PIN;
    DIO_init(&str_Dio);
    
    str_Dio.GPIO = RELAY_4_GPIO;
    str_Dio.pins = RELAY_4_PIN;
    DIO_init(&str_Dio);

    UART_cfg_s str_Uart = {0};
    str_Uart.Resceive_Cbk_ptr = NULL;
    str_Uart.DataRegisterEmpty_Cbk_ptr = NULL;
    str_Uart.Transmit_Cbk_ptr = NULL;
    str_Uart.u32_BaudRate = 9600;
    str_Uart.u8_DataSize = UART_8_BIT;
    str_Uart.u8_DesiredOperation = TRANSCEIVER;
    str_Uart.u8_DoubleSpeed = UART_NO_DOUBLE_SPEED;
    str_Uart.u8_InterruptMode = UART_POLLING;
    str_Uart.u8_ParityBit = UART_NO_PARITY;
    str_Uart.u8_StopBit = UART_ONE_STOP_BIT;
    UART_Init(&str_Uart);

    while(1)
    {
        while (! (UCSRA & RXC));
		relay_1_State = UDR;
        SwDelay_ms(100);
        while (! (UCSRA & RXC));
		relay_2_State = UDR;
        SwDelay_ms(100);
        while (! (UCSRA & RXC));
		relay_3_State = UDR;
        SwDelay_ms(100);
        while (! (UCSRA & RXC));
		relay_4_State = UDR;
        SwDelay_ms(100);
        
        if(relay_1_State == '1')
        {
            DIO_Write(RELAY_1_GPIO, RELAY_1_PIN, HIGH);
        }
        else if(relay_1_State == '0')
        {
            DIO_Write(RELAY_1_GPIO, RELAY_1_PIN, LOW);
        }
        else
        {
            /* Do not change relay 1 state */
        }
        if(relay_2_State == '1')
        {
            DIO_Write(RELAY_2_GPIO, RELAY_2_PIN, HIGH);
        }
        else if(relay_2_State == '0')
        {
            DIO_Write(RELAY_2_GPIO, RELAY_2_PIN, LOW);
        }
        else
        {
            /* Do not change relay 2 state */
        }
        if(relay_3_State == '1')
        {
            DIO_Write(RELAY_3_GPIO, RELAY_3_PIN, HIGH);
        }
        else if(relay_3_State == '0')
        {
            DIO_Write(RELAY_3_GPIO, RELAY_3_PIN, LOW);
        }
        else
        {
            /* Do not change relay 3 state */
        }
        if(relay_4_State == '1')
        {
            DIO_Write(RELAY_4_GPIO, RELAY_4_PIN, HIGH);
        }
        else if(relay_4_State == '0')
        {
            DIO_Write(RELAY_4_GPIO, RELAY_4_PIN, LOW);
        }
        else
        {
            /* Do not change relay 4 state */
        }
    }
    return 0;
}
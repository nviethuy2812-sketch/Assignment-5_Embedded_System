#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "string.h"
#include "stdio.h"

#define MAX 100

char vrc_Getc;
int  vri_Stt;
int  vri_Count = 0;
char vrc_Res[MAX];

void uart_Init(void);
void uart_SendChar(char _chr);
void uart_SendStr(char *str);
uint16_t UARTx_Getc(USART_TypeDef* USARTx);
void led_Init(void);

int main(void){
    uart_Init();	
    led_Init();

    uart_SendStr("Hello from STM32!\r\n");

    while(1){
        if(vri_Stt){
            vri_Stt = 0; 

            if(strcmp(vrc_Res,"ON") == 0){
                GPIO_ResetBits(GPIOA, GPIO_Pin_4); // LED ON
                uart_SendStr("batden\r\n");
            }
            else if(strcmp(vrc_Res,"OFF") == 0){
                GPIO_SetBits(GPIOA, GPIO_Pin_4);   // LED OFF
                uart_SendStr("tatden\r\n");
            }
            else if(strlen(vrc_Res) == 1){
                uart_SendChar(vrc_Res[0]);
                uart_SendStr("\r\n");
            }

            // reset buffer 
            vrc_Res[0] = 0;
            vri_Count = 0;
        }
    }
}

void led_Init(void){
    GPIO_InitTypeDef gpio_typedef;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    gpio_typedef.GPIO_Pin = GPIO_Pin_4;
    gpio_typedef.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &gpio_typedef);

    GPIO_SetBits(GPIOA, GPIO_Pin_4); // LED OFF 
}

void uart_Init(void){
    GPIO_InitTypeDef gpio_typedef;
    USART_InitTypeDef usart_typedef;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

    // TX - PA9
    gpio_typedef.GPIO_Pin = GPIO_Pin_9;
    gpio_typedef.GPIO_Mode = GPIO_Mode_AF_PP;
    gpio_typedef.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&gpio_typedef);	

    // RX - PA10
    gpio_typedef.GPIO_Pin = GPIO_Pin_10;
    gpio_typedef.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA,&gpio_typedef);

    usart_typedef.USART_BaudRate = 9600;
    usart_typedef.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_typedef.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
    usart_typedef.USART_Parity = USART_Parity_No;
    usart_typedef.USART_StopBits = USART_StopBits_1;
    usart_typedef.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1, &usart_typedef);

    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
    NVIC_EnableIRQ(USART1_IRQn);

    USART_Cmd(USART1, ENABLE);
}

void uart_SendChar(char _chr){
    USART_SendData(USART1,_chr);
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE)==RESET);
}

void uart_SendStr(char *str){
    while(*str){
        uart_SendChar(*str++);
    }
}

uint16_t UARTx_Getc(USART_TypeDef* USARTx){
    return USART_ReceiveData(USARTx);
}

void USART1_IRQHandler(void){
    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET){
        vrc_Getc = UARTx_Getc(USART1);

        if(vrc_Getc == '\r' || vrc_Getc == '\n'){

#include "led.h"
#include "stm32f10x.h"

void led_init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // ʹ�� GPIOA ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    // ���� PA0��PA1��PA2 Ϊ�������ģʽ���ٶ�Ϊ 50MHz
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void led_on(void)
{
    // �� PA0��PA1��PA2
    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}

void led_off(void)
{
    // �ر� PA0��PA1��PA2
    GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2);
}

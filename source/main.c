#include "stdafx.h"



int main(void)
{
    volatile uint32_t ui32Loop;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    while(1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++){}
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        for(ui32Loop = 0; ui32Loop < 2000000; ui32Loop++){}
    }
}

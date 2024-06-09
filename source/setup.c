//
// Created by calper on 6/9/24.
//

#include "../include/setup.h"

void SetupClock(void) {
    SysCtlClockFreqSet((SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240), 120000000);
}

void SetupUserLed(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF)) {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTF_AHB_BASE, (GPIO_PIN_0 | GPIO_PIN_4));

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, (GPIO_PIN_0 | GPIO_PIN_1));
}

void UARTSend(const uint8_t* pui8Buffer, uint32_t ui32Count) {
    while (ui32Count--) {
        UARTCharPut(UART0_BASE, *pui8Buffer++);
    }
}

void UARTPrintf(const char *pcFormat, ...) {
    char buffer[128];
    va_list args;
    va_start(args, pcFormat);
    vsnprintf(buffer, sizeof(buffer), pcFormat, args);
    va_end(args);
    // Prepend the carriage return character
    char formatted_buffer[129];
    snprintf(formatted_buffer, sizeof(formatted_buffer), "\r%s", buffer);
    UARTSend((uint8_t*)formatted_buffer, strlen(formatted_buffer));
}

void SetupUart(void) {
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(
            UART0_BASE, 120000000, 115200, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));
}
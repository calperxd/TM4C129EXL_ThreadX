#include "stdafx.h"
#include "tx_api.h"

TX_THREAD my_thread;
TX_THREAD uart_thread;
static ULONG my_thread_stack[1024];
static ULONG uart_thread_stack[1024];

void uartThread(ULONG thread_input) {

}

void thread_entry(ULONG thread_input) {
    volatile uint32_t ui32Loop;
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)) {
    }
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
    while (1) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++) {
        }
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        for (ui32Loop = 0; ui32Loop < 200000; ui32Loop++) {
        }
    }
}

int main(void) {
    tx_kernel_enter();
    return 0;
}

void tx_application_define(void* first_unused_memory) {
    tx_thread_create(&my_thread, "My Thread", thread_entry, 0, my_thread_stack, sizeof(my_thread_stack), 1, 1,
            TX_NO_TIME_SLICE, TX_AUTO_START);

    tx_thread_create(&uart_thread, "UART", uartThread, 0, uart_thread_stack, sizeof(uart_thread_stack), 1, 1,
            TX_NO_TIME_SLICE, TX_AUTO_START);
}

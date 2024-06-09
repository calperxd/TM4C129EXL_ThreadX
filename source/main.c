#include "stdafx.h"
#include "tx_api.h"


TX_THREAD my_thread;
TX_THREAD uart_thread;
static ULONG my_thread_stack[1024];
static ULONG uart_thread_stack[1024];

void UartThread(ULONG thread_input) {
    while (1) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        tx_thread_sleep(1);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0x0);
        tx_thread_sleep(1);
    }
}

void HeartBeatThread(ULONG thread_input) {
    while (1) {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
        tx_thread_sleep(10);
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
        tx_thread_sleep(10);
    }
}

int main(void) {
    SetupClock();
    SetupUserLed();
    SetupUart();
    tx_kernel_enter();
    return 0;
}

void tx_application_define(void* first_unused_memory) {
    if ((tx_thread_create(&uart_thread, "UART", UartThread, 0, uart_thread_stack, sizeof(uart_thread_stack), 1, 1,
                 TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)) {
        UARTPrintf("Error during creation of UART Thread\n");
    }

    if ((tx_thread_create(&my_thread, "My Thread", HeartBeatThread, 0, my_thread_stack, sizeof(my_thread_stack), 1, 1,
                TX_NO_TIME_SLICE, TX_AUTO_START)) != TX_SUCCESS) {
        UARTPrintf("Error during creation of My Thread Thread\n");
    }
    UARTPrintf("\rThreads successfully created \n");
}

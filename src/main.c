#include <stdbool.h>
#include <stdint.h>
#include <inc/hw_memmap.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "tx_api.h"
#include "tx_user.h"


TX_BYTE_POOL byte_pool_0;
TX_THREAD my_thread;

int main( ) {
	/* Enter the ThreadX kernel. */
	tx_kernel_enter( );
}

void my_thread_entry(ULONG thread_input) {
	SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240, 120000000);
	SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
	while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}
	GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
	/* Enter into a forever loop. */
	while(1) {
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
		tx_thread_sleep();
		GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
	}
}

void tx_application_define(void *first_unused_memory) {
	/* Create my_thread! */
	tx_thread_create(&my_thread, "My Thread",
					 my_thread_entry, 0x1234, first_unused_memory, 1024,
					 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}

#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "tx_api.h"


TX_BYTE_POOL byte_pool_0;


//static int hello() {
//	uint32_t x = 2;
//	uint32_t y = 1;
//	uint32_t z;
//	z = x + y;
//	return x;
//
//}
//
//
//const uint8_t * test = "Legall";
//SysCtlClockFreqSet(SYSCTL_XTAL_25MHZ | SYSCTL_OSC_MAIN | SYSCTL_USE_PLL | SYSCTL_CFG_VCO_240, 120000000);
//SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
//while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION)){}
//GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_0);
//hello();
//while(1) {
//GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, GPIO_PIN_0);
//for(uint32_t i = 0; i < 200000; i++){}
//GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_0, 0x0);
//for(uint32_t i = 0; i < 200000; i++){}
//}

unsigned long my_thread_counter = 0;
TX_THREAD my_thread;

int main( ) {
	/* Enter the ThreadX kernel. */
	tx_kernel_enter( );
}

void my_thread_entry(ULONG thread_input) {
	/* Enter into a forever loop. */
	while(1) {
		/* Increment thread counter. */
		my_thread_counter++;
		/* Sleep for 1 tick. */
		tx_thread_sleep(1);
	}
}

void tx_application_define(void *first_unused_memory) {
	/* Create my_thread! */
	tx_thread_create(&my_thread, "My Thread",
					 my_thread_entry, 0x1234, first_unused_memory, 1024,
					 3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);
}

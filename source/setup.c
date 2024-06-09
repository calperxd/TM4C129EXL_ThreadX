//
// Created by calper on 6/9/24.
//

#include "../include/setup.h"


void setupUart(void) {
    uint32_t status;
    status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);
}
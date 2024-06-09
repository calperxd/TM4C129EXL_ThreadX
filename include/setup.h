//
// Created by calper on 6/9/24.
//

#ifndef HELLO_SETUP_H
#define HELLO_SETUP_H

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "driverlib/uart.h"
#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"

void SetupClock();
void SetupUserLed();
void SetupUart();
void UARTPrintf(const char* pcFormat, ...);

#endif  // HELLO_SETUP_H

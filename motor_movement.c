#include <stdint.h>
#include "platform.h"

#ifndef _SIFIVE_HIFIVE1_H
#error "'motor_movement' only supports the HiFive1 Dev board."
#endif

static void _putc(char c) {
    while ((int32_t) UART0_REG(UART_REG_TXFIFO) < 0);
    UART0_REG(UART_REG_TXFIFO) = c;
}

int _getc(char * c) {
    int32_t val = (int32_t) UART0_REG(UART_REG_RXFIFO);
    if (val > 0) {
        *c =  val & 0xFF;
        return 1;
    }
    return 0;
}


static void _puts(const char * s) {
    while (*s != '\0'){
        _putc(*s++);
    }
}

static void setupUartToPrint() {

    // Configure UART to print
    GPIO_REG(GPIO_OUTPUT_VAL) |= IOF0_UART0_MASK;
    GPIO_REG(GPIO_OUTPUT_EN)  |= IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_SEL)    &= ~IOF0_UART0_MASK;
    GPIO_REG(GPIO_IOF_EN)     |= IOF0_UART0_MASK;

    // 115200 Baud Rate
    UART0_REG(UART_REG_DIV) = 138;
    UART0_REG(UART_REG_TXCTRL) = UART_TXEN;
    UART0_REG(UART_REG_RXCTRL) = UART_RXEN;

    // Wait a bit to avoid corruption on the UART.
    // (In some cases, switching to the IOF can lead
    // to output glitches, so need to let the UART
    // receiver time out and resynchronize to the real
    // start of the stream.
    volatile int i = 0;
    while (i < 10000) {
        i++;
    }
}

static void setupClock() {

    // Make sure the HFROSC is on before the next line:
    PRCI_REG(PRCI_HFROSCCFG) |= ROSC_EN(1);

    // Run off 16 MHz Crystal for accuracy. Note that the
    // first line is
    PRCI_REG(PRCI_PLLCFG) = (PLL_REFSEL(1) | PLL_BYPASS(1));
    PRCI_REG(PRCI_PLLCFG) |= (PLL_SEL(1));

    // Turn off HFROSC to save power
    PRCI_REG(PRCI_HFROSCCFG) &= ~(ROSC_EN(1));
}

// 100 ticks @ 62.5kHz is 1.6ms
static const uint16_t PULSE_WIDTH = 100;

 // 2^8 scaling (16mHz / 2^8)
static const uint16_t PERIOD_SCAlING = 8;


static void setupPwm() {
    // setup pwm1
    PWM1_REG(PWM_CFG) = 0;
    PWM1_REG(PWM_CFG) = (PWM_CFG_ENALWAYS | PWM_CFG_ZEROCMP);
    PWM1_REG(PWM_COUNT) = 0;

    // set the pwm corners
    PWM1_REG(PWM_CMP1) = PULSE_WIDTH;
    PWM1_REG(PWM_CFG_SCALE) |= PERIOD_SCAlING;

    // set the Green led to be controlled by PWM controller
    GPIO_REG(GPIO_IOF_SEL) |= (1 << PIN_3_OFFSET);
    GPIO_REG(GPIO_IOF_EN ) |= (1 << PIN_3_OFFSET);
    GPIO_REG(GPIO_OUTPUT_XOR) &= ~(1 << PIN_3_OFFSET);
}

static void sleep(uint16_t microseconds) {
    volatile uint64_t* now = (volatile uint64_t*)(CLINT_CTRL_ADDR + CLINT_MTIME);
    volatile uint64_t then = *now + microseconds;
    while (*now < then) {}
}

void main(void) {

    setupClock();
    setupUartToPrint();
    setupPwm();

    uint16_t min = 125, max = 1250, counter = min;
    uint8_t delta = 1;

    while (1) {
        PWM1_REG(PWM_CMP0) = counter;
        if (delta) {
            counter += 1;
        } else {
            counter -= 1;
        }

        if (delta && counter >= max) {
            delta = 0;
        } else if (!delta && counter <= min) {
            delta = 1;
        }
        sleep(10);
    }
}

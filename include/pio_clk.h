#ifndef PIO_CLK
#define PIO_CLK

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "clk.pio.h"

typedef struct PioClk{
    PIO pio;
    uint sm;
    uint offset;
    uint gpio_pin;
    float freq;
}PioClk;

PioClk create_pio_clk(PIO pio, uint pin, float freq);
void start_pio_clock(PioClk clk);
void stop_pio_clock(PioClk clk);

#endif

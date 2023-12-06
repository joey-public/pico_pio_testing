#include "pio_clk.h"

PioClk create_pio_clk(PIO pio, uint pin, float freq)
{
    PioClk clk;
    clk.pio = pio;
    clk.sm = pio_claim_unused_sm(pio, true);
    clk.offset = pio_add_program(pio, &clk_program);
    clk.gpio_pin = pin;
    clk.freq = freq;
    clk_program_init(clk.pio, clk.sm, clk.offset, clk.gpio_pin, clk.freq);
    return clk;
}

void start_pio_clock(PioClk clk)
{
    clk_program_init(clk.pio, clk.sm, clk.offset, clk.gpio_pin, clk.freq);
    pio_sm_set_enabled(clk.pio, clk.sm, true);
}

void stop_pio_clock(PioClk clk)
{
    pio_sm_set_enabled(clk.pio, clk.sm, false);
}

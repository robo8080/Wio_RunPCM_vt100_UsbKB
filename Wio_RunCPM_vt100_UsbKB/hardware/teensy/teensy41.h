#ifndef TEENSY_H
#define TEENSY_H

#define SDMHZ 50
#define LED 13
#define LEDinv 0
#define board_analog_io
#define board_digital_io
SdFat SD;
#define SDINIT SdioConfig(FIFO_SDIO)
#define BOARD "Teensy 4.1"
#define board_teensy41

#endif

#pragma once


// CONFIGURATION REGISTERS

#define ZMCO          0x00

#define ZPOS_H        0x01
#define ZPOS_L        0x02

#define MPOS_H        0x03
#define MPOS_L        0x04

#define MANG_H        0x05
#define MANG_L        0x06

#define CONF_H        0x07

  #define SF_BIT      0   //  Slow Filter
                          //  00 = 16x*; 01 = 8x; 10 = 4x; 11 = 2x
  #define SF_MASK     0b11 << SF_BIT


  #define FFTH_BIT    2   //  Fast Filter Threshold
                          /*  000 = slow filter only,
                              001 = 6 LSBs,
                              010 = 7 LSBs,
                              011 = 9 LSBs,
                              100 = 18 LSBs,
                              101 = 21 LSBs,
                              110 = 24 LSBs,
                              111 = 10 LSBs */
  #define FFTH_MASK   0b111 << FFTH_BIT

  #define WD_BIT      5   //  Watch dog
                          //  0 = OFF,
                          //  1 = ON




#define CONF_L        0x08

  #define PWR_BIT     0   /*  Power Mode
                              00 = NOM,
                              01 = LPM1,
                              10 = LPM2,
                              11 = LPM3 */

  #define PWR_MASK    0b11 << PWR_BIT


  #define HYST_BIT    2  /*   Hysteresis
                              00 = OFF,
                              01 = 1 LSB,
                              10 = 2 LSBs,
                              11 = 3 LSBs
                                        */
  #define HYST_MASK   0b11 << HYST_BIT


  #define OUT_BIT     4  /*   Output Stage
                              00 = full analog (GND == 0% to VDD == 100%),
                              01 = reduced analog (GND == 0% to VDD == 90%),
                              10 = digital PWM (DAC Off)
                                        */
  #define OUT_MASK    (0b11 << OUT_BIT)


  #define PWM_BIT     6  /*   PWM Frequency
                              00 = 115 Hz;
                              01 = 230 Hz;
                              10 = 460 Hz;
                              11 = 920 Hz
                                        */
  #define PWM_MASK    0b11 << PWM_BIT



// OUTPUT REGISTERS

#define RAW_ANGLE_H   0x0C
#define RAW_ANGLE_L   0x0D

#define ANGLE_H       0x0E
#define ANGLE_L       0x0F


// STATUS REGISTERS

#define STATUS        0x0B

#define MH_BIT        3
#define ML_BIT        4
#define MD_BIT        5

#define AGC           0x1A

#define MAGNITUDE_H   0x1B
#define MAGNITUDE_L   0x1C

// BURN COMMANDS

#define BURN          0xFF

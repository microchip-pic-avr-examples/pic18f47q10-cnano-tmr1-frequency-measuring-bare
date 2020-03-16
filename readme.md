![](images/MicrochipLogo.png)

# PIC18F47Q10 Using TMR1 Gate to measure frequency

## Objective:
This example shows how to use the TMR1 configured in gate single pulse and toggle combined mode. It with sample a full period of a signal. A GPIO pin will be configured as input and it will be connected to a periodical signal.


## Resources:
- Technical Brief Link [(linkTBD)](http://www.microchip.com/)
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)
- [PIC18F47Q10 datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf) for more information or specifications.

## Hardware Configuration:

The PIC18F47Q10 Curiosity Nano Development Board [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029) is used as a test platform.

![](images/PIC18F47Q10-Curiosity-Nano.png)

## Demo:
Run the code in debug mode. Pin RB5 is configured as digital input. A periodical signal needs to be applied to this pin. Set a breakpoint inside "TMR1_GATE_ISR()". The measured frequency will be stored in
the variable called "value". The code will stop at the breakpoint when the signal period has ended.

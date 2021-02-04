[![MCHP](images/microchip.png)](https://www.microchip.com)

# PIC18F47Q10 Using TMR1 Gate to measure frequency
The PIC18F47Q10 features Timers with Gate Control.
This example shows how to use the TMR1 configured in gate single pulse and toggle combined mode. It with sample a full period of a signal. A GPIO pin will be configured as input and it will be connected to a periodical signal.

## Related Documentation
- [TB3285 - Getting Started with Timers/Counters on PIC18](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1003329)
- [PIC18F-Q10 Family Product Page](https://www.microchip.com/design-centers/8-bit/pic-mcus/device-selection/pic18f-q10-product-family)
- [PIC18F47Q10 Data Sheet](http://ww1.microchip.com/downloads/en/DeviceDoc/40002043D.pdf)
- [TB3261 - PIC1000: Getting Started with Writing C-Code for PIC16 and PIC18](https://www.microchip.com/wwwappnotes/appnotes.aspx?appnote=en1002117)

## Software Used
- MPLAB® X IDE 5.30 or newer [(microchip.com/mplab/mplab-x-ide)](http://www.microchip.com/mplab/mplab-x-ide)
- MPLAB® XC8 2.10 or a newer compiler [(microchip.com/mplab/compilers)](http://www.microchip.com/mplab/compilers)
- Microchip PIC18F-Q Series Device Support (1.4.109) or newer [(packs.download.microchip.com/)](https://packs.download.microchip.com/)

## Hardware Used
- PIC18F47Q10 Curiosity Nano [(DM182029)](https://www.microchip.com/Developmenttools/ProductDetails/DM182029)

## Setup
The PIC18F47Q10 Curiosity Nano Development Board is used as the test platform.

The following configurations must be made for this project:

|Pin           | Configuration      |
| :----------: | :----------------: |
|RB5           | Digital Input      |

## Demo:
Run the code in debug mode. Pin RB5 is configured as digital input. A periodical signal needs to be applied to this pin. Set a breakpoint inside "TMR1_GATE_ISR()". The measured frequency will be stored in the variable called "value". The code will stop at the breakpoint when the signal period has ended.

<img src="images/PIC18F47Q10-Curiosity-Nano.png" alt="Hardware Setup"/>

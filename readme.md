# Fujitsu Serial Programming Mode Replacement
Fujitsu Cortex-M3/M4 SoCs have boot ROM support for entering "serial programming mode", via UART or USB. This mode is activated by setting pins MD[1:0] = b'01' (they need to be externally pulled down during normal operation). With these pins configured, the ROM will use UART or USB to download code to SRAM and then execute it.  
This project was specifically targetting a version of the MB9B500 series, however it should work with small tweaks for entire FM3/FM4 product line (or the decendents perhaps branded as Spansion or Cypress now...).  
## But why?
Fujitsu has a very crappy, ancient win32 program which uploads their own mystery code blob to SRAM and interfaces with that to allow a few simple commands like erasing flash and writing new data to flash. This project completely replaces all code running on the Fujitsu part (server code in SRAM), and on the PC (client written in python). This allows rapid testing of code on the device and doing completely custom things.
## Helpful docs
* [FM3 32-BIT MICROCONTROLLER MB9Axxx / MB9Bxxx Series PERIPHERAL MANUAL](https://www.fujitsu.com/tw/Images/MB9Bxxx-MN706-00002-1v0-E.pdf)
* [FM3 Family MB9B500/400/300/100/MB9A100 Series, Flash Programming Guide](http://www.cypress.com/file/227581/download)
* [FM3 32-BIT MICROCONTROLLER MB9BF500 Series FLASH PROGRAMMING MANUAL](http://www.fujitsu.com/tw/Images/CM91-10102-2E-20100415a.pdf)

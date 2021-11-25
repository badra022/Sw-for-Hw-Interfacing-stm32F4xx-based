
# Memory and storage classes

## Memory sections

![sections](https://4.bp.blogspot.com/-6MDb37pMBVU/XIaI-7M2f8I/AAAAAAAADEk/g5s9pZvp7rYnTu_IZ6h9sZvs5EGw5M3EgCLcBGAs/s1600/mem.jpg)

* **.text** section exist in Flash memory, this section is used to store the binary (machine code) to be fetched later for execution
* you need to know that when you flash/burn your code into the microcontroller, what happen actually is that the binary is transferred to the microcontroller and get stored in flash memory. thus, Flash memory is modified when flashing the binary.
* **.bss** is used to store uninitialized data
```c
#include"stdio.h"
int y;          /* stored in .bss */

int main(void){
    int x;      /* stored in .bss */
    return 0;
}
```
* you need to know that .bss section is volatile(RAM), thus the data stored in it get erased by reset or shutdown.
* .bss section is written to zeros before executing your **main** code, by the **startup** code. so that any ininitialized variable stored in one of .bss location have 0 value by default and not a garbage value. 
```c
#include"stdio.h"
int y;          /* stored in .bss */

int main(void){
    int x;      /* stored in .bss */
    printf("x = %d and y = %d", x, y);
    return 0;
}
```
```
x = 0 and y = 0

...Program finished with exit code 0
Press ENTER to exit console.
```
* **.data** is used for initialized data with non zero values
```c
#include"stdio.h"
int y = 0;          /* stored in .bss as it's initialized to 0*/

int main(void){
    int x = 5;      /* stored in .data */
    return 0;
}
```
* you need to know that these data in .data section isn't filled into ram in runtime of the program, instead it's filled out in **startup** running time, but program (main) can modify these data as it want, it's just initialized by startup as this initialization is one time assignment in the runtime so for code optimization purposes, this init is done by startup
* if you compile the previous code into assembly, you wouldn't find any line responsible for assigning the initial value into the variable declared, it's deleted, as we don't need it anymore because the startup code did the init
* how the startup got the initial values for the .data section data? does startup code parse the binary code someway and extract the initial values from the binary? No, this is done by the help of something called **shadow data section**.
* In computing, shadow memory is a technique used to track and store information on computer memory used by a program during its execution.
* so what is this **shadow data section** exactly? this is a memory section allocated in FLASH not in RAM, thus, it's non volatile, no matter how many you reset or shutdown the power the values in this section will not be erased, this section is used to store the initial values that will be copied to .data memory section in the RAM by the startup execution.
* okay, who created this shadow data section at the first place? the linker allocate these values within binary code(hex), and put their start address to map file output to make the startup code able to retrieve these values from binary code
* **.text** memory section in FLASH is usually used for storing constant data also, as it's non volatile, read only section. sometimes they are stored in different FLASH memory section called **.rodata** (read only data), it depends on the linker and **linked script** which we will discuss shortly
```c
#include"stdio.h"
const int y = 0;          /* stored in .text/.rodata as it's initialized to 0*/

int main(void){
    const int x = 5;      /* stored in .text/.rodata */
    return 0;
}
```
* const data in the .text doesn't get copied to ram, as we need them to stay read only.
* see this great article in <a href="https://mcuoneclipse.com/2013/04/14/text-data-and-bss-code-and-data-size-explained/">memory sections</a>

* heap and stack share the same section and address space, stack is storing data bottom up, and heap storing data up bottom 
* you need to know that **.data**, **.bss** in RAM are filled using startup code before even executing main code, while **stack** and **heap** are dynamically allocating data in runtime.
* **heap** is used for dynamic memory allocation, but it's not used in microcontrollers.
* **stack** is used for temporary data allocation, this section cannot allocate data randomly access (by specific addresses) like heap does, instead the only way to put or remove data out of stack is using **push** and **pop** operations , this is a part of stack methodology which lead it to large number of uses in software and hardware
* note that **.data** and **.bss** sections we don't say that they can allocate data randomly (by specific addresses) because they are initialized before even execution, but we say that they can access **(read or write and not allocate)** their data randomly(by specific addresses)

so far, startup code does
* init .bss memory section to zeros
* copy the shadow data section to .data section in ram

these sections, each of them have a specific size in the memory, start address and end address. these parameters are configurable for each microcontroller by a file called **linked script (ld)**, as each mcu vendor manufacture a different physical memory with different sizes that imply to ARM memory architecture as we saw in lecture02.

this linker script is an input to linker stage that help it assign physical addresses of the data into the physical memory sections

this is a piece of linker script for tm4c123gh6pm microcontroller.

```
/******************************************************************************
 *
 * Default Linker script for the Texas Instruments TM4C123GH6PM
 *
 * This is derived from revision 11167 of the TivaWare Library.
 *
 *****************************************************************************/

MEMORY
{
    FLASH (RX) : ORIGIN = 0x00000000, LENGTH = 0x00040000
    SRAM (WX)  : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

REGION_ALIAS("REGION_TEXT", FLASH);
REGION_ALIAS("REGION_BSS", SRAM);
REGION_ALIAS("REGION_DATA", SRAM);
REGION_ALIAS("REGION_STACK", SRAM);
REGION_ALIAS("REGION_HEAP", SRAM);
REGION_ALIAS("REGION_ARM_EXIDX", FLASH);
REGION_ALIAS("REGION_ARM_EXTAB", FLASH);
```

it defines the following
* FLASH is starts from address 0x00000000 in address space, and it's size is 0x00040000
* SRAM starts from addess 0x20000000 in addess space and it's size is 0x00008000
* ```.text, .arm_extidx, .arm_extab``` are in flash and ```.bss, .data, .stack, .heap``` are in sram

there're more details of these sections in the rest of linker script 





compilers deal with .c files each as standalone file, thus the addresses it conserve in the memory is just a logical addresses or as called **offsets** with respect to start address of RAM and ROM, that's becuase this one file is just 1 part of the full program code, that's why the phisical addresses must be assigned with taking the rest files in consideration, that's the job of **linker**
![](https://lh3.googleusercontent.com/proxy/JKXhQKdIvB0DHlL0uo5R6jNRcx87GqN8HrtjxAG1TKGF9I_05DubqTcpWLPMG6Cva3oNODNUYDEZVJ-LoCkz9UQsTXJmIbn4uJVCbb-Z5IRBsHF0dgrEZWuN4Em8Gp9AkeXrob0-9jm0hLX2XBxws2fqd0ReTwi5X8-oV9TGuuvAfJaeqKYZqz8l56GewaOaX_ntGtR3NpCk)

for example, when compiler compile this file, it doesn't find the implementation of ```printf``` function, this is implemented in different files in library. compiler assign addresses for all defined vairables and functions, those addresses are being used in the linker with the rest of files to integrate them to one single physical addresses assignment

```c

```
```

```
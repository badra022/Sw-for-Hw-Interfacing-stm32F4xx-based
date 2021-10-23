## lecture 1 notes

a typical Computer hardware consist of three main components, ```cpu```, ```Memory```, ```IO``` and ```peripherals```. as well as Microcontrollers which we will focus on

* why need peripherals at the first place?
    * each peripheral can be programmed and run in Parallel manner with cpu and other peripherals, because at the end, a peripheral is nothing other than **hardware circuit** outside the cpu and separated from other peripherals Functionalities.
    * fewer Code to store in the Flash Memory (i.e. **Memory conservation**).
    * Faster than Code. bacause a peripheral is a **programmable dedicated hardware** for specific functionalities and this is always faster than doing this Functionalities using general purpose Cpu.
     * even if we use real time operating system to handle perihperals functionalities with code in separate threads, it's still **sequential execution** of the code not in parallel manner. **C language cannot run actual parallel threads**

for example, suppose I want to send 8 bits data output from Mcu Pin serially to another Mcu
* with code
```c 
void send_bits(unsigned char data){
    while(data != 0x00){
        /* put the first bit of data variable in the Pin*/

        /* shift data variable to the right by 1*/

        /* wait some timing before entering the next loop */
    }
}

/* rest of your code */
```
* but if we program **UART** peripheral to do this by itself without any code, all we have to do is to tell it what is the data to be sent and it will send it for you according to your programmed configurations
```c
UART_config(/* pointer to configs*/);
UART.DR = data;     /* this will be sent by UART automatically */

/* rest of your code */
```

* why need Memory?
    * store the code in **FLASH** Memory or soCalled **ROM**
    * store program data for execution in **RAM** Memory, this is temporary data that can be replaced by any value

* how the CPU controls the **RAM**/**ROM** and **IO** or **peripherals** in general?
    * CPU deals with Memory, and all of these have controllable registers that is mapped to certain addresses in the RAM, so processor can deal with them using the RAM interfacing with it
    * **advanced**: there's some registers does not have any mapped addresses in the RAM so it cannot be controlled using RAM interface with CPU, but there're assembly instructions used to deal with em' directly.

how does the cpu inteface the Memory?

![1]("figures/1.png")
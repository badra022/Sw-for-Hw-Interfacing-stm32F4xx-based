BSRR -> atomic istruction -> 1 cycle -> write 1 to action -> write 0 on the others do nothing
ODR -> 3 cycles -> need critical section -> disable and enable interrupt
RCC -> need to enable peripheral clock -> otherwise hardware exception
arm have 2 different buses to interface the memory, with 2 different protocols, AHB, APB
AHB -> provide access to peripherals for high performance and higher access access
APB -> provide access to peripherals for lower performance and lower access speed
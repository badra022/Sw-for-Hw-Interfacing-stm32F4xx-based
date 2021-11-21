# embedded system introduction and GPIO peripheral

## intro to embedded world

there's a hardware parameter for hardware circuits called **propagation delay**, the lower this delay the higher the maximum frequency you can run this hardware on, the lower this delay the higher the hardware cost

computers hardware and mobiles hardware are **general purpose hardware**, handle any operation you want to perform, but it does not have dedicated hardware for most of the operations, which means the processor needs more processing time and power to handle these operations with the available hardware circuits, so the performance is lower than any other dedicated hardwares. to increase the performance and speed of these operations you need to increase clock system (frequency), but this must be compatible with the propagation delay parameter of the hardware, so to lower this parameter in order to increase the frequency supported, hardware price increases, so it's a trade off.

microcontrollers hardware are **dedicated purpose hardware**, contain some hardware peripherals for specific types of operation which will perform faster than the general purpose hardware. now we does not need to increase the frequency to increase the performance.

so at the end, embedded systems is simply a system contain embedded cpu and dedicated hardwares (peripherals)  to interface the outer world (I/O).

for example
* to sense LM35 sensor readings, you need ADC peripheral as a dedicated hardware
* to deal with actuators, you need DAC peripheral as a dedicated hardware.

for this reasons, microcontrollers are prefered for dedicated functionalities more than general purpose functionalities.

## GPIO perihperal

**coming soon...**
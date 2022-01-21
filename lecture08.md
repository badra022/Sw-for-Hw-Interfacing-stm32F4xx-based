
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
* if you compile the previous code into assembly, you wouldn't find any line responsible for assigning the initial value into the variable declared, it's deleted, as we don't need it anymore because the startup code did the inititialization for us
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

---


## Stack

![stack frames](https://upload.wikimedia.org/wikipedia/commons/8/8a/ProgramCallStack2_en.png)

the thing is, when the processor begin to execute a function, it saves some previous data about previous execution status of the caller function which is called **context switch data**, basically, are registers like PC, SPR and other stuff to make it able to return to the previous executing point before calling the new function. now the new function is being executed, all the locally declared variables inside it are stored in the stack, stack is incremented and not a random access memory, so the processor just push the values one after another to the stack. now all the data that that function being executed have stored in the stack is called **data frame**, so each executing function have a data frame in the stack, as long as it had not finished execution. 

* shortly saying: each executing function have a **stack frame**
* cpu pushs context switch data and function defined variables into the stack, and pops the whole stack frame when returning


* variable declaration **does get pushed to stack memory** and it's location is reserved for the definition time. thus we cannot redeclare the same variable again in the same function, as it's already reserved a location for it in the stack frame of the function. this will result in a **redeclaration error**

Midterm Question:
```c
/* Point out the error in the program */
f(int a, int b)
{
int a;
a = 20;
return a;
}

/*
A. Missing parenthesis in return statement
B. The function should be defined as int f(int a, int b)
C. Redeclaration of a @
D. None of above
*/
```

* functions that have return type and does not have ```return``` statement return **undefined value** (probably the last value in some internal register like accumulator), but does not return values from stack, as the entire stack frame of the function is popped with exitting the function

Midterm Question:
```c
/* What will be the output of the program in 16 bit platform (Turbo C under DOS)? (Hint: _AX is the accumulator register) */
#include<stdio.h>
int main()
{
int fun();
int i;
i = fun();
printf("%d\n", i);
return 0;
}
int fun()
{
_AX = 1990;
}
/*
A. Garbage value
B. 0 (Zero)
C. 1990 @
D. No output
*/
```

* if the stack is accessed by push-pop methods, so how the processor access each local variable that is stored in function's stack frame? the answer is <a href= 'https://stackoverflow.com/questions/26898040/what-is-the-idea-behind-using-a-stack-for-local-variables'>here</a>

* is it right to make a pointer to a local variable's address to be accessed outside it's scope? Nope, as this address **is not permenant addresses**, it will be **reused** with another variable as the function (acquiring the local variable) exit and another function is called. what if I try to? well, it will return a **garbage value** from it's location in stack


* stack pointer is **decremented with each push** and the opposite is true
```c
int func(void){
    /* say the stack pointer is pointing at 0xFFFF */
    int x;      /* does not stored yet */
    int y = 0;  /* pushed into address 0xFFFF and SP = 0xFFFE now */
    int x = 0;  /* pushed into address 0xFFFE and SP = 0xFFFD now */

    return 0;       /* pops function's stack frame and return the SP = 0xFFFF */
}
```
* **recursion** is risky in embeddedsoftware and prevented with many dev rules, as it may cause **stack overflow** due to too many recursed stack frames

* stack consumption is not easily determined, you can just estimate the max stack consumption by calculations.

* bss and data segments' variables have **permenant addresses** as 

section (segment) | features
---------| ------------------
stack | non-permenant addresses<br>local variables storage<br> consumption not determined<br> still a random access memory <br> not initialized <br> runtime allocation <br> volatile values (ram)
bss | initialized data storage (global vars)<br>permenant addresses <br> initialized by startup to zeros <br> volatile values (ram) <br>
data | uninitialized data storage (global vars)<br>permenant addresses<br>allocated by startup to the same values in ROM's shadow data section<br>volatile values (ram)<br>
text or code | binary instructions storage <br>non-volatile(ROM)<br>permenant values and addresses
rodata | read only data storage (```const``` and ```strings```)<br>non-volatile (ROM)<br>permenant addresses and values<br>

compilers deal with .c files each as standalone file, thus the addresses it conserve in the memory is just a logical addresses or as called **offsets** with respect to start address of RAM and ROM, it's considered logical addresses (not physical hardware addresses) becuase this one file.c is just 1 part of the full program code, that's why the phisical addresses must be assigned with taking the rest files in consideration, that's the job of **linker**

![](https://lh3.googleusercontent.com/proxy/JKXhQKdIvB0DHlL0uo5R6jNRcx87GqN8HrtjxAG1TKGF9I_05DubqTcpWLPMG6Cva3oNODNUYDEZVJ-LoCkz9UQsTXJmIbn4uJVCbb-Z5IRBsHF0dgrEZWuN4Em8Gp9AkeXrob0-9jm0hLX2XBxws2fqd0ReTwi5X8-oV9TGuuvAfJaeqKYZqz8l56GewaOaX_ntGtR3NpCk)

consider this example to understand the compilation and linking roles

> main.c
```c
#include<stdio.h>

int func1(int);

int main(void){
    int x = func1(5);

    return 0;
}
```
```
gcc -c main.c
```
this code will compile **just fine** as the compiler have all what's required for the file to be successfully compiled. like
* function prototype for the used function ```func1```
* correct syntax
* access path for ```stdio.h``` library to be able to be preprocessed

```
gcc main.c
```
but it's not linked successfully becuase the definition of ```func1``` is not there, not in any other linked file in the linking command, neither in the ```stdio.h``` library, it's just not there

> func1.c
```c
int func1(int x){
    return x;
}
```
```
gcc main.c func1.c
```
this will compile and link successfully

* Note: each C file have an output **object** file (```file.o``` and ```func1.o```) from the compiler tool (not the linker)

* the linker doesn't link the C file, it's linking the object files (that is the output of compiler tool)

linker also get another input file called **linker script** or **linked directive** or **linker command**, which is a script (not a code) that states memory sections and some info of them


for example, when compiler compile this file, it doesn't find the implementation of ```printf``` function, this is implemented in different files in library. compiler assign addresses for all defined vairables and functions, those addresses are being used in the linker with the rest of files to integrate them to one single physical addresses assignment

## Linker

* one of the very importnt **linker** roles is that it **merges** logical memory segments from all the files into one, so the output executable will have 1 bss segment (bss1 + bss2 + bss3 and so on), 1 data segment (data1 + data2 + ..etc), 1 code segment (code1 + code2 + ..etc), 1 rodata (rodata1 + rodata2 + ..etc), one stack and heap, but stack and heap are not merged becuase they are not allocated yet, thus the remaining memory in ram will be used for them after allocating .data and .bss. the size of them can be specified in the linker script also 

> Question: which tool throws the error ```not enough memory```?
>* preprocessor
>* compiler
>* **linker   @**
>* linker script

* linker roles:
    * symbols resolvation
        * each object file have a symbol table that must be resolved by the linker with another object files, if any file's symbol table is not fully resolved, then the linker throws a linker error states ```no reference to (whatever not exist)``` or any other format of missing something from another files
    * memory check
        * whether the final memory consumption and memory segments is compatible with linker script or not
    * memory allocation
        * assign for each variable or data a physical address
        * allocate shadow data section in rom (for startup to put in the .data segment in ram)

* linker output is ```.exe```, ```.elf (hex with debug capabilities)```, ```.hex``` and ```.map```(report of allocations) files

## data scopes

#### function scope
```c
#include<stdio.h>

int func1(int x, int y){
    int result = x + y;
    return result;
}

int main(void){
    x = 5;          /* compilation err */
    result = 50;    /* compilation err */
    return 0;
}
```
* redeclaration and redefinition of the same identifier (variable name) in the same scope are not allowed (compilation err)
#### Block scope
```c
#include<stdio.h>

int main(void){
    {
        int result = x + y;
        return result;
    }
    x = 5;          /* compilation err */
    result = 50;    /* compilation err */
    return 0;
}
```

#### Global scope (software scope)
usually define the variable in the top of any file and use ```extern``` to access the variable in other files

> main.c
```c
#include<stdio.h>

int x = 10;         /* global scope */

int main(void){
    printf("%d", func1());

    return 0;
}
```

Note that this doesn't mean any file linked with ```main.c``` can use ```x``` variable, but only those who ```extern``` it will be able to access it, otherwise, it will not see it 

> func1.c
```c
extern int x;

int func1(void){
    return x;
}
```

**now can you tell the output if we compile (and link) those two files?
```
gcc main.c func1.c

10
```
#### file scope
usually define the variable as ```static``` variable in top of it's file to prevent other files from using it by ```extern```
> main.c
```c
#include<stdio.h>

static int N = 10;      /* file scope */
static int M = 20;      /* file scope */

int main(){
    printf("%d %d", N, M);
    return 0;
}
```

> func1.c
```c
extern int N;       /* linking err (turns out after linking to main.c that N is a static int) */
extern static int N;        /* compilation err (extern + static)!! */

int func1(void){
    return N;
}
```

**same concept of scopes applies to functions, not only variables**
so you may have static functions
, global functions and local functions

* **static functions** are accessable in it's own file only
> main.c
```c
#include<stdio.h>

int _add2(int, int);
int add3(int, int, int);

int main(void){
    printf("%d", add3(5, 3, 8));     /* fine */
    printf("%d", _add2(5, 3));       /* linker error */
    return 0;
}
```
> func1.c
```c
static int _add2(int x, int y){
    return x + y;
}

int add3(int x, int y, int z){
    return z + _add(x, y);
}
```
```
gcc main.c func1.c

linker error: no reference to _add2()
```
Notice that the existance of ```_add2``` prototype made ```main.c``` pass the compilation, but as ```_add2``` is still static in ```func1.c```, it will produce linking error

it's a good practice to use it like this:
> main.c
```c
#include<stdio.h>
int add3(int, int, int);

int main(void){
    printf("%d", add3(5, 3, 8));     /* fine */
    return 0;
}
```
> func1.c
```c
static int _add2(int x, int y){
    return x + y;
}

int add3(int x, int y, int z){
    return z + _add(x, y);
}
```
```
gcc main.c func1.c

16
```

* **global functions** are accessable along all files
as you declare it's prototype in it
> main.c
```c
#include<stdio.h>
int add3(int, int, int);

int main(void){
    printf("%d", add3(5, 3, 8));     /* fine */
    return 0;
}
```
> func1.c
```c
static int _add2(int x, int y){
    return x + y;
}

int add3(int x, int y, int z){
    return z + _add(x, y);
}
```
```
gcc main.c func1.c

16
```

you are right, it's the same example of the **static functions**, that's becuase the function ```add3``` itself is a good example for the global functions 


* **local functions** are accessable in some function's block if you declared it's prototype inside it, not in the top of the file
> main.c
```c
#include<stdio.h>
int main()
{
    int fun();          /* local prototype, thus, this function is accessable inside main() function only */
    int i;
    i = fun();
    printf("%d\n", i);
    return 0;
}
int fun()
{
_AX = 1990;
}
```

it's can be used from another c files also, but it's invoking(calling) is not global though
> main.c
```c
#include<stdio.h>
int main()
{
    int fun();          /* local prototype, thus, this function is accessable inside main() function only */
    int i;
    i = fun();
    printf("%d\n", i);
    return 0;
}
```
> func1.c
```c
int fun()
{
_AX = 1990;
}
```
```
gcc mainc func.c

1990
```

* important Note: function names must be **unique** across all the linked files in the project. why? becuase if there's two seperated definitions, the compiler won't know which definition to assign to the prototypes


* **rule 1**: don't declare vars or functions globally when you don't need to use them outside the file

* **rule 2**: any var or func must be declared before using

* **rule 3**: function and block scopes can access anything in file and global scope, file scope can access anything from global scope. in general, inner scopes can access outer scopes

* **rule 4**: you can declare 2 same identifier variables in two different scopes that doesn't see each others

* **rule 5**: if two identical identifier variables exist and can be seen in some point, the compiler uses the most restricted scope variable declared. for example:

```c
#include<stdio.h>
int x = 10;

int get_global_x(){
    return x;
}

int main(void){
    int x = 5;
    printf("local x value is = %d", x);
    printf("global x value is = %d", get_global_x());
    return 0;
}
```
```
local x value is = 5
global x value is = 10
```

## automatic variables and lifetime
is the default **local** variables with ```auto``` class specifier or without any. they are stored in the stack
```c
#include<stdio.h>

int func1(void){
    auto int x;     /* automatic variable or local variable */
    int y;          /* automatic variable or local variable */
    int z = 0;      /* automatic variable or local variable */
}
```
the lifetime of these variables in the stack memory is **temporary**, as they are popped upon the exit of the function. unlike global variables (initialized or uninitialized)
which have **permenant** variable lifetime

what if we want a **local variable with permenant lifetime ?**

use ```static``` storage class with the local variable, this will make the declaration of the local variable be stored in the **.bss** segment (permenant) not in the stack (temporary)

```c
    #include<stdio.h>

    int func1(){
        static int x = 0;
        x++;
        printf("x = %d\n", x);
    }

    int main(void){
        func1();func1();func1();

        return 0;
    }
```
```
x = 1
x = 2
x = 3


...Program finished with exit code 0
Press ENTER to exit console.
```
of course the local variable is a local variable, accessable inside the function only, but the only difference is that it now have a permenant address inside bss
```c
#include<stdio.h>

int func1(){
    static int x = 0;
    x++;
    
}

int main(void){
    func1();func1();func1();
    printf("x = %d\n", x);
    return 0;
}
```
```
main.c:11:24: error: ‘x’ undeclared (first use in this function)
   11 |     printf("x = %d\n", x);
```

but if it have now a permenant address, we can now access it through it's address from outside the function
```c
#include<stdio.h>

int* ptr_x = nullptr;

int func1(){
    static int x = 0;
    ptr_x = &x;     /* make the pointer point to x's address */
    x++;
}

int main(){
    func1();func1();
    printf("*ptr_x = x = %d", *ptr_x);       /* print the value pointed py ptr_x */
    return 0;
}
```
```
*ptr_x = x = 2

...Program finished with exit code 0
Press ENTER to exit console.
```


#### so to summarize the scopes and lifetimes

```c
#include<stdio.h>
int x;      /* global scope with permenant lifetime */
extern int y;       /* linked global scope variable with permenant lifetime from another file */
static int z;       /* file scope with permenant lifetime */
const int w = 20;     /* constant global var with permenant life */
static const char s = 1;      /* constant local var with permenant life */


int func1(void){
    auto int x;     /* automatic var with temporary life */
    int y = 0;      /* automatic var with temporary life */
    static int z = 0;   /* local var with permenant life */
    register int q = 2; /* lcoal var with permenant life */
}

int main(void){

    return 0;
}
```

#### tentative definition (search topic)




## notes
* **preprocessor errors** happen when you use some # directive that not exist, sometimes it's considered compilation errors

* sorting of compiling files isn't important in most cases

* linker script is just a script used by linker tool, it's not compiled at all

* remember the feature of non permenant addresses of the stack memory? here's a question:
```c
#include<stdio.h>
int func2(void);

int func1(void){
    int x = 0;
    x++;
    printf(" x = %d", x);
    func2();
}

int func2(void){
    int y;
    y++;
    printf(" y = %d", y);
}

int main(void){
    func1();
    func2();

    return 0;
}
```
```
 x = 1 y = 22025 y = 2

...Program finished with exit code 0
Press ENTER to exit console.
```
that's becuase when we called ```func2``` from inside ```func1```, it created new stack frame and assigned y to new stack memory address(which contains garbage), but when we exitted ```func1```, it's entire stack frame is now popped and when we called ```func2``` again, it reused the same location of the previous ```func1``` stack frame, thus now y posses the same address as x previously had, thus the same value of the memory (which is also considered a garbage and you shouldn't depend on it in your code)


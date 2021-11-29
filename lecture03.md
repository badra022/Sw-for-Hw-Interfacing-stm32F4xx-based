# C Programming

* middle level language, have feature of **portability** (not dependent on specific hardware), efficient **memory and execution performance**

* Memory -> **Data**(execution of data in Ram) and **Flash** (stores the code instructions)

* **Machine instructions** consist of binary data (i.e. 0's and 1.s) stored in Flash memory, each instruction consist of **OP-code**(specify the operation) + **source addr.** + **destination addr**.

* each hardware have specific **instruction set Architecture (ISA)** that defines it's specific **machine language** , of course we cannot write the machine language directly so there's **assembly language** which is more higher level than machine language, to abstract the machine instruction interface.

* Data movement, arithmatic and Jump operations are the common instructions over all ISA's

* assembly is a language you can write your software with. with files extension (.asm). we need assembler tool to Convert this .asm file code to machine language and instructions(0's and 1's) to Flash it into the microcontroller

* assembly is a hardware specific language. each hardware have a different memory interface and different ISA(instructions) than the others. because of that, each hardware need specific assembly language.

* assembly is:
    * long development process
    * faster execution
    * very optimized
    * used in **timing critical** situations (i.e. OS scheduling, enable/disable interrupts, etc..)
    * Not portable

* C needs a **Compiler tool** to convert it to machine language. also called **binary files** (machine language file that will be stored in the Flash memory)

* C used to be high level language several years age. now it's considered **middle level** in contrast with python, java, etc..

* python is Interpreted language. each line is passed to the Interpreter to convert and execute. at the end, the Interpreter is a software that can run your python script lines. This require extra Memory to run store the Interpreter for running any python script.

* C is compiled language. all the code is passed to the Compiler tool to convert it to binary file, then you store that binary file in the Flash and execute it directly using the processor, hence, no extran Memory for extra tools is required to run C programs in the processors.

* example: **rasbperry pi** need Linux OS to be installed on it to enable the user to install python Interpreter, to make the Mcu be able to run your python code.

* most Mcus used in industry cannot store such operating systems. but there's **real time operating systems (RTOS)** that can be run in the Mcu for Tasks scheduling purposes.

* c and c++ handle memory efficiently 

* C is
    * portability for different hardware
    * fast development cycle
    * memory efficient
    * compiled language
    * readable
    * maintainable (you can easily debug and fix)
    * structured oriented programming language

Object oriented | structured oriented
---------------|-------------------------
you can structure your code as objects which have attributes and methods. supporting polymorphism, inheritance and encapsulation but it's not efficient and slower to deal with embedded devices. | you cannot make special structures as object. no supporting for Methods, polymorphism, inheritance and encapsulation. it's little harder to organize but it's more efficient especially for embedded devices.

* C is used when speed and space is needed.

* **#include** and all the directives starting with # is just text replacement, commonly called **preprocessor directives**, because it preprocess the code text before compilation of the code.

* #include replace the text you include to the current file containing the #include directive, what is inside the included files? declarations, which is a prototypes of library functions which hold information of the functions **(i.e. number of parameters, return type, function name)** only and not the implementations, why include this declarations of the functions in your file? when you use library functions it will get compilation error if you don't include the declaration, that's all what you need to know for now.

* C is consisted of functions only. to execute specific function you need to call it

* **compiler logically allocate memory for variables**

* datatypes in C are **native** and **user defined** 

* native datatypes
    * void (0 bytes, does not physically consume memory)
    * integers (for decimal numbers)
        * char  (1 byte)
        * int   (2 or 4 bytes)
        * short (2 bytes)
        * long  (4 bytes)
    * Non integers (for fractions)
        * float (4 bytes)
        * double (8 bytes)

* variable names are called **identifiers** 

* here is some **size qualifiers** that is used with native datatypes to modify it's default size in memory. syntax typed as ```qualifier datatype identifier = value;```
```c
short int x = 0; /* 2 bytes */
long int x = 0; /* 4 bytes */
long long x = 0;/* 8 bytes */
long double x = 0; /* 10 bytes */

/* float, char, short cannot take a size qualifier before them */

```

* there's also other qualifiers (e.g. **signed**, **unsigned**) that affect the range of data.

```c
char x          = 0;    /* 1 byte, signed, -128...127 */
unsigned char x = 0;    /* 1 byte, unsigned, 0...255 */
int x           = 0;    /* 2 or 4 bytes, signed */
signed long int = 0;  /* 4 bytes, unsigned, -2,147,483,648...2,147,483,647 */
unsigned long int = 0;  /* 4 bytes, unsigned, 0...4,294,967,295*/
short x         =0;     /* 2 bytes, signed */
signed short x    =0;   /* 2 bytes, signed */      
signed float x     =0;  /* Not applicable, float and double are always signed by definition */
void x              =0; /* NOT APPLICABLE, void cannot store any value by definition */
char x;                 /* This is called a declaration, telling the compiler that there's an identifier named x that will need to consume 1 byte in RAM memory, and storing a signed value, so the compiler handle assigning this variable it's physical location in the ram */
void function(int x);   /* this is also a declaration, telling the compiler that there's a function with name function, returning nothing, with one integer parameter will be used in the code so don't return compilation error */

/* FOLLOWING DECLARATION ARE NOT ALLOWED BY THE IDENTIFIER RULES */
char +x = 0;
char else = 0;
char x 1 = 0;           
char a+b = 0;

```

* C is case sensitive. so that ```ahmed``` doesn't equal ```Ahmed``` doesn't equal ```ahMeD``` 





# Macros

* it's just a plain text reolacement
* have no type checking
* have no return statement
* faster in context of execution because there's no invokation (actually), it's just replaced with the code
```c
#define MULTIPLY(X, Y)  X * Y

int main(void){
    int x = 3, y = 5;
    int z = MULTIPLY(x, y);
}
```
this code will pass through the preprocessor (before the compiler) and will output the next file ```.i``` which will be actually compiled by the compiler
```c
int main(void){
    int x = 3, y = 5;
    int z = x * y;
}
```
so the problem here is that if we do this
```c
#define MULTIPLY(X, Y)  X * Y

int main(void){
    int x = 3, y = 5;
    int z = MULTIPLY(x, y + 1);
}
```
this will let ```z = x * y + 1``` which is 16, although we meant to multiply ```x * (y + 1)``` which is 18, that's the main problem of plain text replacement

* Not compiled (preprocessed)
* hard to debug. why?

1)
```c
#include<stdio.h>
#define MULTIPLY(X, Y)    do{\
                        m = X * Y;\
                        printf("%d", m);\
                        }\
                        while(0);
int main(){
    int m;
    MULTIPLY(5, 8);
}
```
this will be replaced with
```c
int main(){
    int m;
    do{m = X * Y; printf("%d", m);}while(0);        /* this line contain three different statements */
}
```
and as the debugger goes line by line, it's hard to detect where would be the error in such one line, so that macros are meant to be 1 line or 2 maximum

2)

this will replace each macro used in the  code, thus if the macro code contain an error, this error now spreaded along the whole code and cannot be referred to one location, so take care.

* one advantage (which is not used except in **autocode generation**) is the **text concatenation
```c
#define WRAP(MODULE_NAME, COMPONENT)    MODULE_NAME##_##COMPONENT

int main(void){
    int WRAP(GPIO, IDR) = 0x41;
}
```
this will result in
```c
int main(void){
    int GPIO_IDR = 0x41;
}
```

Macros | inline functions | functions
-----------|-----------|----------------
test replacement | object replacement | function context calling
no type checking | type check | type check
no return | return | return
Fastest | Faster | slower
not compiled | compiled | compiled
hard to debug | easier | easier
can concatenate text | cannot | cannot
more code size | more code size | less code size
no context switching | depend of compiler optmization | context switching

# Pointers

## what is a pointer

so, why use pointers? **to access memory chunks using addresses**, done, that's it. let's expand this definition into three use cases

* pass/share variables by address.
    * so instead of passing the value of the variable to a local variable to some function, we will pass the address to make that function be able to access the original address value through it
```c
#include <stdio.h>

void increaseValue(int * ptr){
    *ptr = *ptr + 1; 
}
int main()
{
    int x = 0;
    printf("x = %d \n", x);
    increaseValue(&x);
    printf("x = %d", x);
    return 0;
}
```
```
x = 0 
x = 1
```
* pass/share large size of data (e.g. arrays, structs...etc) by address
```c
#include <stdio.h>

void increaseValue(int * parr){
    for(int i = 0; i < 1000; i++){
        parr[i]++;
    }
}
int main()
{
    int x[1000] = {1, 2, 3, 4};     /* 1 2 3 4 0 0 0 0 ... */
    printf("x[0] = %d  x[1] = %d  x[2] = %d  x[3] = %d \n", x[0], x[1], x[2], x[3]);
    increaseValue(x);
    printf("x[0] = %d  x[1] = %d  x[2] = %d  x[3] = %d \n", x[0], x[1], x[2], x[3]);
    return 0;
}
```
```
x[0] = 1  x[1] = 2  x[2] = 3  x[3] = 4 
x[0] = 2  x[1] = 3  x[2] = 4  x[3] = 5 
```
* access peripherals registers (which is mapped in the memory to some addresses) by address

## Questions
> WARNING: you must see the lecture record before proceeding

try to answer the next questions yourself without seeing the answer then check the answer

-------------

what is the output of the following
---
```c

```

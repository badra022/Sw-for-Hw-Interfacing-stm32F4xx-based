# C Programming

## Operators

```c
#include"stdio.h"

int main(void){

    return 0;
}

```
```

```
operators have many types including the following

**assignment operators** like ```=```. the left side of the operator must be a variable can be assigned a value, and the left side must be a value or expression that calculate a value
```c
#include"stdio.h"

int main(void){
    int x, y;
    x = 0; /* assign value */
    /* x + 1 = 0; */    /* this is not allowed, will throw l-value error */
    y = (x + 5); /* assign exression */
    printf("x = %d and y = %d", x, y);
    return 0;
}

```
```
x = 0 and y = 5

...Program finished with exit code 0
Press ENTER to exit console.
``` 
**arithmetic operators** like ```+, -, *, /, %```, mind the sign with these arithmatic operators
```c
#include"stdio.h"

int main(void){
    unsigned char x = 50, y = 100;
    signed char z = 150;
    printf("x = %d , y = %d , z = %d \n", x, y, z);
    printf("\n x + y is unsigned addition and equals %d", x + y);
    printf("\n x + z is signed addition and equals %d", x + z);
    printf("\n x + y + z is signed addition and equals %d", x + y + z);
    printf("\n z + z is signed addition and equals %d", z + z);
    return 0;
}
```
```
x = 50 , y = 100 , z = -106 

 x + y is unsigned addition and equals 150
 x + z is signed addition and equals -56
 x + y + z is signed addition and equals 44
 z + z is signed addition and equals -212

...Program finished with exit code 0
Press ENTER to exit console.
```
> some comments on above code. char, short, int datatypes can be printed with ```%d``` specifier, this specifier can print any integer datatype as a numerical number. ```%c``` works only with char datatype and print it as an ascii character. characters are just integers with 8 bits data width so we can use them in arithmetic operations like any other integer.

 > note: any value not stored in a variable with a datatype is signed integer by default, except you cast it to another datatype, like in the following example.

 ```c
#include"stdio.h"

int main(void){
    unsigned int x = 3000000000;
    signed int y = 1000000000;
    printf(" value of 3000000000 is %d as it's type is signed integer by default", 3000000000);
    printf("\n value casted to unsigned int = %d", (unsigned int)3000000000);   /* didn't change the speciifier %d */
    printf("\n value casted to unsigned int and printed with the appropriate specifier = %u", (unsigned int)3000000000);   /* used %u for unsigned int */
    printf("\n value casted to signed long = %d", (long)3000000000);    /* didn't change the speciifier %d */
    printf("\n value casted to signed long and printed with the appropriate specifier = %ld", (long)3000000000);    /* used %ld for signed long */
    printf("\n x + y leads to signed addition and = %d", x + y);
    printf("\n x + (unsigned int)y leads to unsigned addition and = %u", x + (unsigned int)y);
    
    return 0;
}

 ```
 ```
main.c:6:38: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long int’ [-Wformat=]
    6 |     printf(" value of 3000000000 is %d as it's type is signed integer by default", 3000000000);
      |                                     ~^                                             ~~~~~~~~~~
      |                                      |                                             |
      |                                      int                                           long int
      |                                     %ld
main.c:9:47: warning: format ‘%d’ expects argument of type ‘int’, but argument 2 has type ‘long int’ [-Wformat=]
    9 |     printf("\n value casted to signed long = %d", (long)3000000000);    /* didn't change the speciifier %d */
      |                                              ~^   ~~~~~~~~~~~~~~~~
      |                                               |   |
      |                                               int long int
      |                                              %ld
 value of 3000000000 is -1294967296 as it's type is signed integer by default
 value casted to unsigned int = -1294967296
 value casted to unsigned int and printed with the appropriate specifier = 3000000000
 value casted to signed long = -1294967296
 value casted to signed long and printed with the appropriate specifier = 3000000000
 x + y leads to signed addition and = -294967296
 x + (unsigned int)y leads to unsigned addition and = 4000000000

...Program finished with exit code 0
Press ENTER to exit console.
 ```
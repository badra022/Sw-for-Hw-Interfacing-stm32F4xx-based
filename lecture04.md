# C Programming

## Operators


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
this warnings are on purpose so that you read them and know what kind of warnings you will be facing
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
here is some specifiers used with ```printf``` for different types and formats. note that they are not used in embedded software programs so you don't need to memorize them

<img src="https://sillycodes.com/wp-content/uploads/2014/04/DatatypesinClanguage.jpg">
<img src="https://www.crackyourinterview.com/images/Img264217-0.png">

```*, /``` are almost same as ```+```, but ```-``` is different. as the sign of subtraction is decided according to the sign of the first operand
```c
#include"stdio.h"

int main(void){
    printf("\n (unsigned char)200 - (unsigned char)30 leads to unsigned subtraction and = %d", (unsigned char)200 - (unsigned char)30);
    printf("\n (signed char)200 - (unsigned char)30 leads to unsigned subtraction and = %d", (signed char)200 - (unsigned char)30);
    printf("\n (unsigned char)200 - (signed char)30 leads to unsigned subtraction and = %d", (unsigned char)200 - (signed char)30);
    printf("\n (signed char)200 - (signed char)30 leads to signed subtraction and = %d", (signed char)200 - (signed char)30);
    
    return 0;
}
```
```

 (unsigned char)200 - (unsigned char)30 leads to unsigned subtraction and = 170
 (signed char)200 - (unsigned char)30 leads to unsigned subtraction and = -86
 (unsigned char)200 - (signed char)30 leads to unsigned subtraction and = 170
 (signed char)200 - (signed char)30 leads to signed subtraction and = -86

...Program finished with exit code 0
Press ENTER to exit console.
```
Q: what is the output of the following operation
```c
#include"stdio.h"

int main(void){
    signed char x = 200;
    signed char y = 100;
    printf("%d", x - y);
    return 0;
}
```
```
-156

...Program finished with exit code 0
Press ENTER to exit console.
```
ans: as the signed char value of 200 is -56 and signed char value of 100 is 100 then ```-56 - 100 = -156```

as you saw in the above examples, all this tricks is for the sake of understanding datatypes and operations. your code must imply simplicity and type compatibility, e.g. if you you want to perform signed subtraction, a good practice is to subtract two signed values in two signed variables 

```c
int main(void){
    signed char x = -5, y = 20;
    printf("%d", x - y);
}
```

there's some thing called **integer promotion**, which is the conversion of some integer datatype(char, short, int, long) to a higher integer datatype using **implicit casting** or **explicit casting**

for example, you can perform addition on two unsigned char operands then store the result in short datatype to not be overflowed

this is an example for explicit casting as we type ```(short)(x + y)```
```c
#include"stdio.h"

int main(void){
    unsigned char x = 255;
    unsigned char y = 255;
    printf("%d", (short)(x + y)); /* (x + y) explicitly casted */
    return 0;
}
```

or you can leave it to implicit casting 

```c
#include"stdio.h"

int main(void){
    unsigned char x = 255;
    unsigned char y = 255;
    short z = x + y; /* (x + y) is implicitly casted to short then stored in z */
    printf("%d", z);
    return 0;
}
```
```
510

...Program finished with exit code 0
Press ENTER to exit console.
```
also if you add integer datatype value + higher integer datatype value, the lower one will be promoted to higher integer datatype and the result will be the higher integer datatype
```c
#include"stdio.h"

int main(void){
    unsigned char x = 255;
    unsigned short y = 255;
    printf("%d", x + y);
    return 0;
}
```
```
510

...Program finished with exit code 0
Press ENTER to exit console.
```
so in the above example, we don't need to explicity cast ```x + y``` to make the result in short datatype

division are **floating point** and **non floating point** divsion

we will show this with an example
```c
#include"stdio.h"

int main(void){
    printf(" 5 / 2 = %f", 5/2); /* integer division or non-floating-point division */
    printf("\n (float)5 / 2 = %f", (float)5 / 2); /* floating-point division */
    printf("\n 5 / (float)2 = %f", 5 / (float)2); /* floating-point division */
    printf("\n (double)5 / 2 = %.2lf", (double)5 / 2); /* floating-point division */
    printf("\n (double)5 / (float)2 = %.2lf", (double)5 / (float)2); /* floating-point division */
    printf("\n 5 / 2.3 = %.2f", 5/2.3); /* floating-point division */
    printf("\n 5.5 / 2 = %.2f", 5.5/2); /* floating-point division */
    printf("\n 5.0 / 2.2 = %f", 5.0/2.2); /* floating-point division */
    return 0;
}
```
```
main.c:4:23: warning: format ‘%f’ expects argument of type ‘double’, but argument 2 has type ‘int’ [-Wformat=]
    4 |     printf(" 5 / 2 = %f", 5/2); /* integer division or non-floating-point division */
      |                      ~^   ~~~
      |                       |   |
      |                       |   int
      |                       double
      |                      %d
 5 / 2 = 0.000000
 (float)5 / 2 = 2.500000
 5 / (float)2 = 2.500000
 (double)5 / 2 = 2.50
 (double)5 / (float)2 = 2.50
 5 / 2.3 = 2.17
 5.5 / 2 = 2.75
 5.0 / 2.2 = 2.272727

...Program finished with exit code 0
Press ENTER to exit console.
```
if we try to assign ```3.0``` to some integer datatyped variable, it will be **implicitly casted** to integer
```c
#include"stdio.h"

int main(void){
    int x = 3.00;
    int y = 2.5;
    printf(" %d/%d = %d", x, y, x / y);
    printf("\n (float)(%d/%d) = %f", x, y, (float)(x / y));
    printf("\n (float)%d/%d = %f", x, y, ((float)x / y));
    printf("\n %d/(float)%d = %f", x, y, (x / (float)y));
    /* note that once the value 2.5 stored in y as integer value (2), we cannot restore the 2.5 value again */
    return 0;
}
```
```
 3/2 = 1
 (float)(3/2) = 1.000000
 (float)3/2 = 1.500000
 3/(float)2 = 1.500000

...Program finished with exit code 0
Press ENTER to exit console.
```
the opposite is true, if we assign ```3``` as integer value to float datatyped value, it will be casted to ```3.0``` floating point value

now to the reminder ```%```, this operators is used with integer datatypes only

**unary operators**, like ```++, --```, basically ```x++;``` is the same as ```x = x + 1```, and the same for minus

these unary operators have 2 possible placement, it can be **post increment** as in ```x++;``` and it can be **pre increment** as in ```++x;```, post increment ++ is executed after all other operators are executed, pre increment execute the ++ before other operators executed
```c
#include"stdio.h"

int main(void){
    int x = 3;
    int y = 2;
    y = x++;
    printf(" x = %d and y = %d", x, y);
    y = ++x;
    printf("\n x = %d and y = %d", x, y);
    x = 3, y = 2;
    printf("\n assume x = %d and y = %d", x, y);
    printf("\n (x++) + (y++) = %d", (x++) + (y++));
    x = 3, y = 2;
    printf("\n x++ + (y++) = %d", x++ + (y++));
    x = 3, y = 2;
    printf("\n (x++) + ++y = %d", (x++) + ++y);
    x = 3, y = 2;
    printf("\n ++x + ++y = %d", ++x + ++y);
    x = 3, y = 2;
    printf("\n (x++ + y++) / (float)y = %.1f", (x++ + y++) / (float)y);
    x = 3, y = 2;
    printf("\n (++x + y++) / (float)y = %.1f", (++x + y++) / (float)y);
    x = 3, y = 2;
    printf("\n (++x + ++y) / (float)y = %.1f", (++x + ++y) / (float)y);
    
    return 0;
}
```
```
 x = 4 and y = 3
 x = 5 and y = 5
 assume x = 3 and y = 2
 (x++) + (y++) = 5
 x++ + (y++) = 5
 (x++) + ++y = 6
 ++x + ++y = 7
 (x++ + y++) / (float)y = 1.7
 (++x + y++) / (float)y = 2.0
 (++x + ++y) / (float)y = 2.3

...Program finished with exit code 0
Press ENTER to exit console.
```

one of the unary operators is ```&```, this address operator gets the address of any variable, if ```x``` is a variable, then ```&x``` is the address of that variable
```c
#include"stdio.h"

int main(void){
    int x = 3;
    printf("x = %d \n&x = %p", x, &x);
    
    return 0;
}
```
```
x = 3 
&x = 0x7ffe41d3cfc4

...Program finished with exit code 0
Press ENTER to exit console.
```
address operator is used for passing parameters to functions by address, instead of passing vairable's value to a function like ```add(x);``` where x say equal 5, this method of passing to function doesn't allow the function to access ```x``` variable, so the original variable cannot be edited or assigned inside the called function, so we use **pass by address** to allow the function to assign to the original variable from inside it. one use case for now is ```scanf``` function, as you must pass the variables by address to be assigned with the input using the scanf function. pass by address and pass by value will be explained in more details in pointers topics.

what happen if we accedently pass variable value instead of address to scanf
> undefined behavior, but basically the program will try to assign some garbage address the input value, most of the time this will produce **runtime error** but the code will be compiled successfully.
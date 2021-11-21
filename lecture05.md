# C programming

## ternary operator
written as ``` condition ? true expression : false expression```, the result should be assigned to some variable using ```=``` assignment operator

```c
#include"stdio.h"

int main(void){
    unsigned char x = 0;
    unsigned char* expression = x == 1? "true" : "false";
    printf("%s", expression);
    return 0;
}
```
```
false

...Program finished with exit code 0
Press ENTER to exit console.
```
> note: strings are just an array of characters (signed or unsigned) ended by character ```'\0'``` named as **null terminator**
```c
#include"stdio.h"

int main(void){
    char* string1 = "ahmed";
    char string2[] = "mohamed";
    char string3[] = {'k', 'h', 'a', 'l', 'e', 'd', '\0'};
    printf("string1 = %s", string1);
    printf("\nstring2 = %s", string2);
    printf("\nstring3 = %s", string3);
    return 0;
}
```
```
string1 = ahmed
string2 = mohamed
string3 = khaled

...Program finished with exit code 0
Press ENTER to exit console.
```

> note: c doesn't have boolean datatype

**relational operators** are ```<, >, >=, <=```

**logical operators** are ```&&, ||```, these are typed as ```boolean expression || boolean expression```, this operation outputs a boolean expression (1 or 0) out of two boolean expressions

```!``` is also a logical operator called **logical Not**, typed as ```! boolean expression```

```c
#include"stdio.h"

int main(void){
    char x = 'A';
    char y = 'C';
    printf("number %d have the ascii charcter value = %c", x, x);
    printf("\nnumber %d have the ascii charcter value = %c", y, y);
    unsigned char boolean_output = (x >= 'A') && !(y < 'D');
    printf("\nboolean output is %d", boolean_output);
    return 0;
}
```
```
number 65 have the ascii charcter value = A
number 67 have the ascii charcter value = C
boolean output is 0

...Program finished with exit code 0
Press ENTER to exit console.
```

all integers except 0 are considered true (1) in logical operations, e.g. ```!50 = 0```, ``` 4 && 3 = 1```, ```0 && 5 = 0``` and so on

## bitwise operators

as the name means, this operators is bit wise, operate on the bits of the data. consist of ```|, &, ^```

```c
#include"stdio.h"

void print_binary(unsigned char data){
    printf("\n ");
    for(char i = 7; i >= 0; i--){
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void){
    unsigned char x = 0b10101010;
    unsigned char y = 0b01110011;
    print_binary(x);
    printf("\n&");
    print_binary(y);
    printf("\n-----------");
    print_binary(x & y);
    printf("\n*************");
    print_binary(x);
    printf("\n|");
    print_binary(y);
    printf("\n-----------");
    print_binary(x | y);
    printf("\n*************");    
    print_binary(x);
    printf("\n^");
    print_binary(y);
    printf("\n-----------");
    print_binary(x ^ y);
    printf("\n*************");
    return 0;
}
```
```

 10101010
&
 01110011
-----------
 00100010
*************
 10101010
|
 01110011
-----------
 11111011
*************
 10101010
^
 01110011
-----------
 11011001
*************

...Program finished with exit code 0
Press ENTER to exit console.
```
also ```~``` is a bitwise Not operator

```c
#include"stdio.h"

void print_binary(unsigned char data){
    // printf("\n ");
    for(char i = 7; i >= 0; i--){
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void){
    unsigned char x = 58;
    printf("~");
    print_binary(x);
    printf(" = ");
    print_binary(~x);
    return 0;
}
```
```
~00111010 = 11000101

...Program finished with exit code 0
Press ENTER to exit console.
```

## shift operators

there's shift to right or left, typed as ```value >> number of bits```, this shifts the value bit by bit with the number of bits, and replace the last bit by 0, for example, ```0b01110100 >> 2 = 0b00011101``` and ```0b01110100 << 2 = 0b11010000```

last bit from the left, which is called also **most significant bit (MSB)**, represent the nigative sign if the binary data stored in a variable with signed integer datatype, so when you try to shift some signed variable data to right, it will replace the MSB by 1 not by 0 to conserve the negative sign of the data. while shifting the negative signed data to the left replace the LSB's by 0 as usual because they don't affect the sign
```c
#include"stdio.h"

void print_binary(unsigned char data){
    // printf("\n ");
    for(char i = 7; i >= 0; i--){
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void){
    char x = -58;
    print_binary(x);
    printf(" >> 2 = ");
    print_binary(x >> 2);
    printf("\n");
    print_binary(x);
    printf(" << 2 = ");
    print_binary(x << 2);
    return 0;
}
```
```
11000110 >> 2 = 11110001
11000110 << 2 = 00011000

...Program finished with exit code 0
Press ENTER to exit console.
```

shift to right by 1 bit ( data >> 1) is considered as dividing the data by 2, becuase when you shift each bit by 1, each bit's weight is divided by 2, so overall the data is divided by 2. e.g. ```0b00010010 (decimal value = 2 + 16 = 18) >> 1 = 0b00001001 (decimal value = 1 + 8 = 9)```, so that **each shift to right by 1 is considered dividing the decimal value by 2, similarly, each shift to lift by 1 is considered multipling the decimal value by 2**

so that if we want to divide some value by 8 for example, we divide the value by 2 three times, thus shifting the binary data by 3 bits.

Q: how to multiply a variable by 9 without ```*``` arithmetic operator
```c
#include"stdio.h"

int main(void){
    int x = 9;
    int x_mul_9 = (x << 3) + x;
    printf("x multiplied by 9 = %d", x_mul_9);
    return 0;
}
```
```
x multiplied by 9 = 81

...Program finished with exit code 0
Press ENTER to exit console.
```

there's two types of shifts, **logical shift** which is the ordinary shifting, **arithmetic shift** which is the shifting of negative signed data as we explained above.

arithmetic shift is not making any logic, you need to avoid it by using the shift operators on unsigned integer datatypes or explicitly casting the data to unsigned datatype.

## Bit Masking

how to set the second bit in binary data/register to 1 without affecting other bits?
* read the binary bits
* mask binary bits (make **all bits be 0 except target bit**), typically ```(1 << target bit index)``` will do
* ```data = data | mask;``` or ```data |= mask;```

```c
#include"stdio.h"

void print_binary(unsigned char data){
    // printf("\n ");
    for(char i = 7; i >= 0; i--){
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void){
    unsigned char data = 0b00101101;
    printf("\nprevious data = ");
    print_binary(data);
    printf("\n");
    print_binary(data);
    unsigned char mask = (1 << 1);
    data |= mask;
    printf("\n|\n");
    print_binary(mask);
    printf("\n=\n");
    print_binary(data);
    printf("\nnew data = ");
    print_binary(data);
    return 0;
}
```
```

previous data = 00101101
00101101
|
00000010
=
00101111
new data = 00101111

...Program finished with exit code 0
Press ENTER to exit console.
```

how to clear the 5th bit in data without affecting others
* read the binary bits
* mask binary bits (make **all bits be 1 except target bit**), typically ``` ~(1 << target bit index)``` will do
* ```data = data & mask;``` or ```data &= mask;```

```c
#include"stdio.h"

void print_binary(unsigned char data){
    // printf("\n ");
    for(char i = 7; i >= 0; i--){
        printf("%d", (data >> i) & 0x01);
    }
}

int main(void){
    unsigned char data = 0b10011001;
    printf("\nprevious data = ");
    print_binary(data);
    printf("\n");
    print_binary(data);
    unsigned char mask = ~(1 << 4);      /* fifth bit index, ~ is used to invert all 0's to 1's and target bit from 1 to 0 */
    data &= mask;
    printf("\n&\n");
    print_binary(mask);
    printf("\n=\n");
    print_binary(data);
    printf("\nnew data = ");
    print_binary(data);
    return 0;
}
```
```

previous data = 10011001
10011001
&
11101111
=
10001001
new data = 10001001

...Program finished with exit code 0
Press ENTER to exit console.
```

for toggle masking
x | y | x ^ y
------|-------|--------
0 | 0 | 0
1 | 0 | 1
0 | 1 | 1
1 | 1 | 0

we can think of this truth table as following

x | y | x ^ y
--------|--------|-----------
x | 0 | x
x | 1 | !x

so if we want to  toggle some logic bit whatever it's value, you need to xor it with 1 according to the above table.

how to toggle bit 0 and bit 7 at once?
* read the data
* mask binary bits (10000001), typically can be done using shifting as ``` (1 << 0) | (1 << 7)```, ```(1 << 0) = 0b00000001``` and ```(1<< 7) = 0b10000000```, thus ```0b10000000 | 0b10000000 = 0b10000001``` 
* ```data ^= mask;```

> Note: we will skip visualization from here and show only the solutions

> Note: we used mask value directly with the third step in the solution to quick up the process
```c
#include"stdio.h"

int main(void){
    unsigned char data = 0b10111010;
    data ^= (1 << 7) | (1 << 0);
    /* data ^= 0x81; can be used also */
    return 0;
}
```

how to toggle bit 5 then set bit 1 and bit 7 then clear bit 0?
* read the data
* mask for toggle (00100000), writen as ```0x20``` or ```(1 << 5)```
* ```data ^= 0x20;``` or ```data ^= (1 << 5);```
* mask for setting (10000010), written as ```0x82``` or ```(1 << 1) | (1 << 7)```
* ```data |= 0x82;``` or ```data |= (1 << 1) | (1 << 7);```
* mask for clearing (11111110), written as ```0xFE``` or ```~(1 << 0)```
* ```data &= 0xFE;``` or ```data &= ~(1 << 0);```

```c
#include"stdio.h"

int main(void){
    unsigned char data = 0xBA;
    data ^= (1 << 5);       /* toggle bit 5 */
    data |= (1 << 1) | (1 << 7);        /* set bit 1 and 7 */
    data &= ~(1 << 0);      /* clear bit 0 */
    return 0;
}
```

> you may have noticed that we used ```unsigned``` integer datatypes only for data that we perform bitwise operations on it, that's a good practice. if you used it with signed numbers it may change the sign and make undefined behavior

different operators have precedence table defining which operator should be executed first and the order of the operators will execute, this will not be included in the exam but it's commonly used in interviews.

so for example if you need to type the following exepression ```x = y * z + 1 >> 2```, this will depend on precedence of each operator to define execution order, so ```>>``` is executed first then * then +. but to improve code quality and portability, you shouldn't depend on operators precedence on your code, if you aim to use such expression you should type it as ```x = ((y * z) + 1 )>> 2```

## switch case

```c
#include"stdio.h"

int main(void){
    unsigned char x = 1;

    switch(x)
    {
        case 1:
        /* statement 1 */
        break;
        case 2:
        {
        /* statement 2 */
        break;
        }
        case 3:
        {
        /* statement 3 */
        break;
        }
        case 4:
        {
        /* statement 4 */
        break;
        }
        default:
        {

        }
    }
}
```

* in the above exampe, ```break``` is essential to stop the execution of the cases after finding the target case, if x = 1 for example and you forgot to write ```break``` for it, case1 will be executed and case2 will be executed as well, then the program will break out from the switch, thus the branching behevior is messed up

* statements inside cases can be multilines

* switch is used only for integers checking (char, short, int, long), will throw compilation error if used with floats

* switch cases almost more optimized in it's assembly code more than if-else, but it cannot handle >, <, <= >= and floats conditioning




for **if-else** and **loops** you may check the slides...






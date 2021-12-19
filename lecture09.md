> research Topic: preprocessor directives (#define, #include, #if, #elif,....)

# recursion

recursion is the case when you call the function inside itself. now thanks to the stack frames, it gives each function execution it's own private part of stack memory, without corrupting the previous stack frames of the unfinished executing functions

consider the following factorial function
```c
int fact(int n){
    if(n == 1){         /* stop condition */
        return 1;
    }

    return n * fact(n - 1);
}

int main(void){
    int number = fact(4);
    return 0;
}
```

now how is the stack consumption till it reach the last recursive call
```
main() frame
int number
-----------------------
int n = 4
return 4 * fact(3)
-----------------------
int n = 3
return 3 * fact(2)
-----------------------
int n = 2
return 2 * fact(1)
-----------------------
int n = 1
return 1            #end of the recursion

# then starting from the last recursive call, it will traceback to the first called function and pop each frame after
another after calculating it's return value

return 1
pop fact(1) frame
------------------
return 2 * (1)
pop fact(2) frame
------------------
return 3 * (2 * (1))
pop fact(3) frame
------------------
return 4 * (3 * (2 * (1)))      # which is the final return from fact(4) call
pop fact(4) frame
------------------
main() frame
```

* in the recursion, it consumes more time more that the iterative method, that's becuase it keeps calling the same function recursively, thus saving each call's context switch and local variables in the stack, this process takes some time for each call. though, iterative method is just iteration, no context switching or stack consumption stuff.

comparison | recursion | iterative
--------------|-----------------|---------------
stack consumption | more  | less
speed | lower | higher
readness | readable | harder to read

* you choose which method to apply among the iterative and recursion based on your **memory and speed** constraints

# Arrays
* adjacent memory locations storage and direct access
```c
int main(){
    int x0 = 0;
    int x1 = 0;     
    int x2 = 0;
    /* we can't loop over these variables if we want becuase they are different vars and not adjacent in memory */

    /* we will use array to make this be able */
    int x[] = {0, 0, 0};
    /* now we can loop */
    for(int i = 0; i < 3; i++){
        /* use x[i] */
    }
    return 0;
}
```
* arrays are **user defined type**. typically, to define any user defined type we provide it three main info
    * how to declare instance from the type 
    ```c
    int x[10];      /* array of adjacent integer values */
    char x[10];      /* array of adjacent char values */
    float x[10];      /* array of adjacent float values */

    int x[];        /* compiler error */
    extern int x[]; /* no compiler error, and depending on it's definition in the other file, it may or may not pass the linking */
    ```
    * how to init it and how to access it
    ```c
    int x[3] = {0, 1, 2};
    int x[];        /* compilation error */
    int x[] = {0, 1, 2};        /* compiler will deduce the number of it's elements from it's initial values */
    int x[2] = {0};     /* array of 2 integers, each initiated to 0 */
    int x[3] = {2};     /* first element is 2 and the rest is 0 */
    int x[3];           /* garbage init */
    int x[3] = {1, 2, 3, 4}     /* compiler error */
    char x[3] = {128, 128, 128}     /* init to -128 for every elements */

    char x[3];
    x[0] = 0;
    x[1] = 0;
    x[2] = 0;       /* this is also a valid initiation */
    ```

* typically, an array of integers consumes 4 times it's number of elements of adjacent memory addresses. intuitively, each array consumes ``` n * size``` where n is the number of bytes of each element.

* what is the memory look like when you define an array?
```c
int X[3] = {0x23E25DFF, 0x75EFD6A8, 0xFF00ABE4, 0x58F9F9E1};        /* array of integers (just types them in hexa to be easly visualized)
```
```
suppose
- array's start address is 0x40020000
- the machine is little endian (machine stores the LSB first up to the MSB in increasing addresses)

FIRST INT ELEMENT X[0]
0x40020000      0xFF
0x40020001      0x5D
0x40020002      0xE2
0x40020003      0x23
---------------------------
SECOND INT ELEMENT X[1]
0x40020004      0xA8
0x40020005      0xD6
0x40020006      0xEF
0x40020007      0x75
---------------------------
THIRD INT ELEMENT X[2]
0x40020008      0xE4
0x40020009      0xAB
0x4002000A      0x00
0x4002000B      0xFF
---------------------------
FORTH INT ELEMENT X[3]
0x4002000C      0xE1 
0x4002000D      0xF9
0x4002000E      0xF9
0x4002000F      0x58
---------------------------

```
```
suppose
- array's start address is 0x40020000
- the machine is big endian (machine stores the MSB first down to the LSB)


FIRST INT ELEMENT X[0]
0x40020000      0x23
0x40020001      0xE2
0x40020002      0x5D
0x40020003      0xFF
---------------------------
SECOND INT ELEMENT X[1]
0x40020004      0x75
0x40020005      0xEF
0x40020006      0xD6
0x40020007      0xA8
---------------------------
THIRD INT ELEMENT X[2]
0x40020008      0xFF
0x40020009      0x00
0x4002000A      0xAB
0x4002000B      0xE4
---------------------------
FORTH INT ELEMENT X[3]
0x4002000C      0x58
0x4002000D      0xF9
0x4002000E      0xF9
0x4002000F      0xE1
---------------------------

```

* array indecies isn't boundary sensitive, if you try to access an index out of array size, it may be accessed successfully, and not neccessary throw a runtime error, thus you may corrupt this location's value that may had been used by another variable. you need to take care

* **2D arrays** are also an adjacent values in memory, but accessed with **2 indecies**, thus there's no difference in the memory storage of 1D and 2D but they are conceptually treated differently in differnet contexts

consider the memory consumption of the following array definition
```c
int X[2][2] = {{0x23E25DFF, 0x75EFD6A8}
              ,{0xFF00ABE4, 0x58F9F9E1}};
/* OR */
int X[][2] =  {{0x23E25DFF, 0x75EFD6A8}
              ,{0xFF00ABE4, 0x58F9F9E1}};

/* OR */
int X[][2] =  {{0x23E25DFF, 0x75EFD6A8}
              ,{0xFF00ABE4, 0x58F9F9E1}};
/* OR */
int X[][2] =  {0x23E25DFF, 0x75EFD6A8, 0xFF00ABE4, 0x58F9F9E1};

/* OR */
int X[2][2] =  {0x23E25DFF, 0x75EFD6A8, 0xFF00ABE4, 0x58F9F9E1};

/* BUT NOT */
int X[][] =  {0x23E25DFF, 0x75EFD6A8, 0xFF00ABE4, 0x58F9F9E1};      /* compiler error */

/* AND NOT */
int X[][] =  {{0x23E25DFF, 0x75EFD6A8}
               ,{0xFF00ABE4, 0x58F9F9E1}};      /* compiler error */

/* AND NOT */
int X[2][] =  {{0x23E25DFF, 0x75EFD6A8}
               ,{0xFF00ABE4, 0x58F9F9E1}};      /* compiler error */
```
```
suppose
- array's start address is 0x40020000
- the machine is little endian (machine stores the LSB first up to the MSB in increasing addresses)

FIRST INT ELEMENT X[0][0]
0x40020000      0xFF
0x40020001      0x5D
0x40020002      0xE2
0x40020003      0x23
---------------------------
SECOND INT ELEMENT X[0][1]
0x40020004      0xA8
0x40020005      0xD6
0x40020006      0xEF
0x40020007      0x75
---------------------------
THIRD INT ELEMENT X[1][0]
0x40020008      0xE4
0x40020009      0xAB
0x4002000A      0x00
0x4002000B      0xFF
---------------------------
FORTH INT ELEMENT X[1][1]
0x4002000C      0xE1 
0x4002000D      0xF9
0x4002000E      0xF9
0x4002000F      0x58
---------------------------

```

* differnet types of initializing 2D arrays are:
```c
int x[2][2] = {{5, 1}, {3, 4}};     /* 5  1  3  4   */
int x[][2] = {{5, 1}, {3, 4}};      /* 5  1  3  4   */
int x[2][] = {{5, 1}, {3, 4}};      /* compilation error (second dimension must be specified) */
int x[][] = {{5, 1}, {3, 4}};       /* compilation error  */
int x[4] = {{5, 1}, {3, 4}};        /* 5  3  0  0 (cannot be used as 2D X[i][j], must be used as 1D array X[index])   */
int x[2][2] = {{5}, {3, 4}};        /* 5  0  3  4   */
int x[2][2] = {{5}, {3}};           /* 5  0  3  0   */
int x[2][2] = {5, 1, 3, 4};         /* 5  1  3  4   */
int x[2][2] = {{5, 1}, 3, 4};       /* 5  1  3  4   */
int x[2][2] = {{5, 1}, 3};          /* 5  1  3  0   */
```

* note: if you use 2D array ```X[n][m]``` as 1D ```X[n * m]```, it won't produce compiler error, but the opposite is not true

```c
#include<stdio.h>

int main(void){
    int x[2][2] = {{5, 1}, {3, 4}};     /* 5  1  3  4   */


    for(int i = 0; i < 4; i++){
        printf("%d  ", x[i]);
    }
}
```
```
967227840  967227848  967227856  967227864

...Program finished with exit code 0
Press ENTER to exit console.
```
and surprisingly, this printed values turns to be the first address of each element (which is consdered an array of 2 integers in this example) in the x array. you will understand it better when we get to pointers

```c
#include<stdio.h>

int main(void){
    int x[4] = {{5, 1}, {3, 4}};     /* 5  3  0  0   */

    for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            printf("%d  ", x[i][j]);
        }
    }
}
```
```
main.c:26:32: error: subscripted value is neither array nor pointer nor vector
   26 |             printf("%d  ", x[i][j]);
      |                                ^
```


* note: size of the array in definition must be constant number or const variable, and cannot be 0. check <a href='https://stackoverflow.com/questions/2427336/why-cant-i-create-an-array-with-size-determined-by-a-global-variable#:~:text=int%20size%20means%20that%20size,not%20allow%20variable%20size%20arrays.'>this</a>
```c
#include<stdio.h>

int main(void){
    const int N = 100;
    int M = 100;
    int x[N];           /* this is fine */
    int y[M];           /* compilation error */

    return 0;
}
```

How to pass an array to a function?

typically, the array identifier (array name) is a pointer to the address of it's first element

for example
```c
#include<stdio.h>
const int N = 100;

int main(void){

    int x[N];           /* this is fine */
    printf("base address of the array = %p", x);

    return 0;
}
```
```
base address of the array = 0x7fff44c1f160

...Program finished with exit code 0
Press ENTER to exit console.
```

so ,if you just pass this address to the function which you want it to access that array, it will access the array using your passed address (which is equivalent to the name of the original array even if the function assigned it a different name)

for example
```c
#include<stdio.h>
const int N = 100;

void initArr(int arr[]){
    for(int i = 0; i < N; i++){
        arr[i] = 0;
    }
}

int main(void){

    int x[N];           /* this is fine */
    initArr(x);
    for(int i = 0; i < N; i++){
        printf("x[%d] = %d \n", i, x[i]);
    }

    return 0;
}
```
in this example, ```initArr``` will receive x's base address in new name called ```arr``` which can access the original array now with it, this method of passing to functions is called **pass by address**

and the output will be that x array is now all initialized to zeros
```
x[0] = 0 
x[1] = 0 
x[2] = 0 
x[3] = 0 
.
.
.
x[98] = 0 
x[99] = 0 

...Program finished with exit code 0
Press ENTER to exit console.
```


# Notes on inline functions
> make sure to see it's slides

compiler decide whether the case of inline function replacement is appropriate or not basen on it's **optimization configurations** and **function's code size**

for example, suppose there's an inline function
```c
inline int cube(int num){
    return num * num * num;
}
```
this function will be either treated as a regular function, or treated in the context of inline functions. if you define optimization of level 0, this function will be treated as inline function becuase no optimization required for program code size, if you define a higher level of optimaziation, then you should not be increasing the size of function's code to be able to be treated as inline function(to save execution time in trade off with increasing code memory) not a regular function.

* it's a good practice to make inline function's code very small (typically one or two lines)




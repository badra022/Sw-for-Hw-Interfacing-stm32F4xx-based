# ex1
  ```c
  # include <stido.h>
  int main()
    {
      float x=10.333;//ff<br />
      unsigned int y=x;<br />
      printf("%x ",y);10 in hexa which is a <br />
      printf("%x ",x);garbage as it try to print float with any other specifier than %f <br />
      return 0;<br /><br />
    } 
   ```
# ex2 
  ```c
- int i1 = 1;     // definition, external linkage
- int i1;         // tentative definition, acts as declaration because i1 is defined
- extern int i1;  // declaration, refers to the earlier definition
```
```c
- extern int i2 = 3; // definition, external linkage
- int i2;            // tentative definition, acts as declaration because i2 is defined
- extern int i2;     // declaration, refers to the external linkage definition
```
in 2 above examples both i2 or i1  value wont be changed 

- note (tentative defination allow more than 1 decleration of same variable with same decleration)
```c
- extren int i;
- static int i:
will compile noramlly 
```

```c
- extern int i1;
- static int i1 ;  
wont compile
```

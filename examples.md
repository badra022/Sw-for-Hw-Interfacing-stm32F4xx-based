# ex1
```c
  # include <stido.h>
  int main()
    {
      float x=10.333;
      unsigned int y=x;
      printf("%x ",y);//10 in hexa which is a
      printf("%x ",x);//garbage as it try to print float with any other specifier than %f 
      return 0;
    } 
```

> note: types of declarations and variable linkage
```c
extern int n; // external declaration with external linkage
int b = 1;    // external definition with external linkage
static const char *c = "abc"; // external definition with internal linkage
int f(void) {  // external definition with external linkage
    int a = 1; // non-external
    return b; 
}
static void x(void) { // external definition with internal linkage
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

# ex3

If there are no definitions in the same translation unit, then the tentative definition acts as an actual definition with the initializer = 0.

```c
int i3;        // tentative definition, external linkage
int i3;        // tentative definition, external linkage
extern int i3; // declaration, external linkage
// in this translation unit, i3 is defined as if by "int i3 = 0;"
```

# ex4

Unlike the extern declarations, which don't change the linkage of an identifier if a previous declaration established it, tentative definitions may disagree in linkage with another declaration of the same identifier. If two declarations for the same identifier are in scope and have different linkage, the behavior is undefined:

```c
static int i4 = 2; // definition, internal linkage
int i4;            // Undefined behavior: linkage disagreement with previous line
extern int i4;     // declaration, refers to the internal linkage definition
 
static int i5; // tentative definition, internal linkage
int i5;        // Undefined behavior: linkage disagreement with previous line
extern int i5; // refers to previous, whose linkage is internal
```


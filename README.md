# DirtyPointer Hack

A C++ program demonstrating a simple hack-around to illegaly access private members and private methods of a C++ object outside the class. This hack was just to unerstand pointers and internal memory allocation of object oriented languages like C++. 

### Concepts learnt: 
The important concepts learnt while hacking-around :
   * Object memory allocation.
   * Pointer arithmetic 
   * Padding in compilers
   * Function pointers

### Object memory allocation : 
C++ objects are stored in heap memory (Heap is a resizable, dynamic memory), objects are garbage collected from heap, when not in use, heap can grow and shrink as per the requirements. 
##### Internal allocation :
When objects are allocated, multiple copies of members (data) is created for each object, but methods are allocated only once, in a common memory area and are shared by all the objects. The figure shows object memory allocation.<br/><br/><br/>
![alt text](https://i.ibb.co/nQ6hpSx/cpp-pointer-this.jpg, "Object allocation")<br/><br/><br/>
Understanding allocation is very important because it allows us to assign pointers to memory locations. Members (data variables) are allocated sequentially within a object memory. **Therefore, if we we create a pointer to an object, it automatically points to first member of the object, irrespective of whether it is public or private.**

Creating a pointer to object : 
Consider a Simple C++ Object  : 
```c++
class DemoObject {
    private:

      int age;
      bool male;
      char gender;
      double salary;
      int function(int age, int increment) {
          this->age = age + increment;
          return age + increment;
      }
    public:
      DemoObject(int age, bool sex, double salary, char gender) {
          this->age = age;
          this->male = sex;
          this->salary = salary;
          this->gender = gender;
      }
      int getAge() {return this->age;}
      bool getisMale() {return this->male;}
      double getName() {return this->salary;}
};
```
Inside Main function, create pointer to object :

```C++
 DemoObject object = DemoObject(21, true, 10000.0, 'M');
 DemoObject *objPointer = &object;
```
Now , objPointer points to first meomory block of object. Since age is the first member, it points to age. We can now access age, and typecaste it to (int *), similarly we can access all other variables.
```C++
  int * agePointer = (int *)objPointer;

    //print , modify and then print again to see changes : 
    printf("AGE  : %d\n",  *agePointer);

    *agePointer = *agePointer + 10;

    printf("Changed value of AGE : %d\n", object.getAge());

    //accessing boolean Male variable, increment the pointer, agePointer, we skip 4 bytes
    //Now *agePointer points to male
    agePointer++;

    bool *malePtr = (bool *)agePointer;

    printf("MALE : %s\n", *malePtr ? "true" : "false");

    *malePtr = false;

    printf("Changed value of MALE : %s\n", object.getisMale() ? "true" : "false");

    //Size of bool is 1 byte, so increment by 1: 

    malePtr ++;

    char *gender = (char *)malePtr;

    printf("GENDER  : %c\n", *gender);

    //change *gender variable 
    *gender = 'F';

    printf("Changed gender value : %c\n", *gender);
```

### Padding:
Padding is a technique followed by compilers of most languages to variables easily addressable. Let us understand, **Padding**.
Address length of memory depends on machine-architecture. For example, in a 32-bit machine, 4GB memory system, CPU generated 32-bit address making it possible to generate 2^32 addresses. Most of the premitive data-types such as int, float, double occupy multiple bytes (Ex : int is 4 bytes), therefore, in most of the machines, they are allocated a memory address that is divisible by 4. (For example : 400000 is a address that is divisible by 4, but 400010 is not). All these variables can be allocated starting from location 400000 but not 4000010. This is known as padding. But other premitives such as **bool**, **char** occupy only 1 byte, therefore they can be allocated anywhere, eventhough their address is not a multiple of 4. 
(Thus, padding is performed only for those variables that occupy multiple bytes).
From the above example, member *male* is allocated immediately after *age* as it as a boolean variable, immediately followed by *gender*, this is followed by padding of 3 bytes , because double is a multi-byte varialbe and it has to start with an address that is divisible by 4. In below code segment, we check the location is divisible by 4. Till that we keep on incrementing pointer.
```C++
    while((int)gender % 4 != 0) gender++;
    printf("New Address after padding : %p\n", gender);
    double * salaryPointer = (double *)gender;
    printf("SALARY : %lf\n", *salaryPointer);
```

### Function Pointers : 
Methods are allocated in a common area of memory that can be shared by all objects. The total size of a method is tedious to find out. The total space is sum of all instructions. Because of the allocation, as shown in the figure, the address of a method is no way related to object address.

In C++ functions of an object can be called using pointers. If pointers are used, they can be invoked, irrespective of whether they are public or private.

```C++
void hackFunction(DemoObject object) {

    int  (DemoObject::*function)(int, int) =  &object.function;
    printf("Function Address in code-segment : %p\n", function);
    int result = (object.*function)(10, 20);
    printf("Result : %d\n", result);
    printf("Changed value of age : %d\n", object.getAge());
}
```

End


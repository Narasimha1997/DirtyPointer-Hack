#include<stdio.h>
#include<iostream>

using namespace std;

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


void hackFunction(DemoObject object) {

    int  (DemoObject::*function)(int, int) =  &object.function;

    printf("Function Address in code-segment : %p\n", function);

    int result = (object.*function)(10, 20);

    printf("Result : %d\n", result);

    printf("Changed value of age : %d\n", object.getAge());

}


int main(int argc, char const *argv[])
{
    DemoObject object = DemoObject(21, true, 10000.0, 'M');

    //create a pointer to object 

    DemoObject *objPointer = &object;

    //now objPointer points to begenning of the object, i.e the first private variable :

    //since we know it is of type int , we cast the pointer to int *

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

    //Addresses for datatypes int, double , or strings are always allocated to next address 
    //that is divisible by 4, 32 and 64 bit addresses thay are generated by CPU, and it will be easier
    //to access such values as they occupy multiple bytes. --- Padding 

    //to generate next address that is divisible by 4, incremen gender pointer until it's address is divisible by 4

    while((int)gender % 4 != 0) gender++;

    printf("New Address after padding : %p\n", gender);

    double * salaryPointer = (double *)gender;

    printf("SALARY : %lf\n", *salaryPointer);

    hackFunction(object);

}

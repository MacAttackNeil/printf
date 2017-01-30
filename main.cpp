#include "printf.hpp"

int main(int argc, char **argv)
{
   //ADAM: The negative scalars value won't show up correctly because hydra machines use 32 bit integers. So negative scalar will have anomalous results worry not. Still works
   int test = 789;
   int bytes = printf("This is an integer : %d\n", 123);
   printf("Characters written : %d\n", bytes);
   printf("This is an integer : %d, This is an integer too : %d\n", test, 987);
   printf("This is an integer : %d\n", 123456789);
   printf("This is a float : %f\n", 3.14);
   printf("This is a float : %f\n", 65.78);
   printf("This is a float : %f\n", 783.234235643);
   printf("This is a float : %f\n", 0.52);
   //printf("This is a hexadecimal num : %x", 100);
   //printf("This is a string : %s", "Sup");
   
   return 0;
}

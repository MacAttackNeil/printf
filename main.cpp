#include "printf.hpp"

int main(int argc, char **argv)
{
   //ADAM: The negative scalars value won't show up correctly because hydra machines use 32 bit integers. So negative scalar will have anomalous results worry not. Still works
   int test = 789;
   printf("This is an integer : %d\n", 123);
   printf("This is an integer : %d\n", test);
   printf("This is an integer : %d\n", 123456789);
   //printf("This is a float : %f", 6.7);
   //printf("This is a hexadecimal num : %x", 100);
   //printf("This is a string : %s", "Sup");
   
   return 0;
}

#include "printf.hpp"

//3 SPACES ADAM NOT TABS
int printf(const char *fmt, ...)
{
   int bytes_written = 0;
   char c;
   //to access variadic arguments must use "va_list"
   va_list args;
   //args tell va_start where to initialize and fmt tells where to start the ... arguments 
   va_start(args, fmt);
	
   //loop through all the characters of fmt
   while( c = *fmt++ )
   {
      if(c == '%')
      {
         //if we see a '%' skip to the next character and see what it is
         c = *fmt++;
         switch(c)
        {
            //decimals, use int64_t
            case 'd':
			   int64_t a_decimal_parameter = va_arg(args, int64_t);
			   /*so to use write, must convert int64_t to a char * this can be confusing so im just writing comments as I understand it before implementing it
			   If you have a number 12345 and divide by 10000 i get 1.2345. Then %10 that number and you get 1. 
			   Then you divide  12345 by 1000 and get 12.345, then %10 and you get 2. Add that to the char *, should have 12. Keep going until its 12345 %10 which is 5 so you youll have the char * of 12345 */
			   write(1, "this be d", 10);
               break;
           //floats, use double
            case 'f':
			   double a_double_parameter = va_arg(args, double);
			   write(1, "this be f", 10);
               break;
            //hex, use uint64_t
            case 'x':
			   uint64_t a_hex_parameter = va_arg(args, uint64_t);
			   write(1, "this be x", 10);
			   break;
			//EXTRA CREDIT. string, use char *
			case 's':
			   char * a_string_parameter = va_arg(args, char *);
			   //get length of the char * then print that out using write(1, char *, length)
  		       break;
            default:
			 //  write(1,c,1);
			   break;
        }
	  }
   }

   //va_end() required to free resources and printf must return the # of bytes_written
   va_end(args);	
   return bytes_written;
}

int snprintf(char *dest, size_t size, const char *fmt, ...)
{
   int bytes_written = 0;


   return bytes_written;
}

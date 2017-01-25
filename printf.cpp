#include <printf.hpp>

//3 SPACES ADAM NOT TABS
int printf(const char *fmt, ...)
{
   int bytes_written = 0;
   char c;
   //to access variadic arguments must use "va_list"
   va_list args;
   //args tell va_start where to initialize and fmt tells where to start the ... arguments 
   va_start(args, fmt);
	
   while( c = *fmt++ )
   {
	  if(c == '%')
	  {
		 c = *fmt++;
         switch(c)
         {
            //decimals
            case 'd':
               break;
            //floats
            case 'f':
               break;
            //hex
            case 'x':
  		       break;
            default:
			   break;
         }
	  }
   }

   va_end(args);	

   return bytes_written;
}

int snprintf(ichar *dest, size_t size, const char *fmt, ...)
{
   int bytes_written = 0;


   return bytes_written;
}

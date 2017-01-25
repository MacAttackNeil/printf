int printf(const char *fmt, ...)
{
   //to access variadic arguments must use "va_list"
   va_list args;
    
   va_start(args, fmt);

   //placeholder
   int bytes_written = 0;
   return bytes_written;
}

#include "printf.hpp"

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
			{
			   int64_t decimal_parameter = va_arg(args, int64_t);
			
			   /*so to use write, must convert int64_t to a char * this can be confusing so im just writing comments as I understand it before implementing it
			   If you have a number 12345 and divide by 10000 i get 1.2345. Then %10 that number and you get 1. 

			   Then you divide  12345 by 1000 and get 12.345, then %10 and you get 2. Add that to the char *, should have 12. Keep going until its 12345 %10 which is 5 so you youll have the char * of 12345 */
			   //write(1, "this be d", 10);

			  /* Then you divide  12345 by 1000 and get 12.345, then %10 and you get 2. Add that to the char *, should have 12. 
			   Then you divide  12345 by 1000 and get 12.345, then %10 and you get 2. Add that to the char *, should have 12. 
			   Keep going until its 12345 %10 which is 5 so you youll have the char * of 12345 */
			   int64_t i, sign;
			   sign = 0;
			   //if sign = 1 then number is negative
			   char toPrint[100];
			   
			   if(decimal_parameter < 0)
			   {
			      sign = 1;
			      decimal_parameter = -decimal_parameter;
			   }
				  i = 0;
			   do 
			   {
				  toPrint[i++] = decimal_parameter % 10 + '0';
				} while ((decimal_parameter /= 10) > 0);
				if (sign == 1)
				{
					toPrint[i++] = '-';
				 }
				 toPrint[i] = '\0';

			 /* REVERSE */
			
			    int64_t counter, temp1, temp2;

			    for(counter = 0, temp2 = i-1; counter < temp2; counter++, temp2--)
				{
					 temp1 = toPrint[counter];
				     toPrint[counter] = toPrint[temp2];
				     toPrint[temp2] = temp1;
               }
			   write(1, toPrint, i);
			   bytes_written += i;

               break;
			}
           //floats, use double
            case 'f':
			{
			   /*Take first part of decimal and turn to int. Then substract that fromthe doub
				*Then multiply by 10 to and repeat
				Example: 5.67 -> 5 -> 5.67 - 5 -> .67*10 -> 6.7 -> repeat*/
			   double double_parameter = va_arg(args, double);

			   //write(1, "this be f", 10);
			   int sign = 0;
			   char toPrint[100];
			   char tempPrint[100];
			   int64_t i = 0;
			   if( double_parameter < 0)
			   {
			      sign = 1;
				  double_parameter = -double_parameter;
			   }
			   //hold value before the . decimal place and convert to char *
			   int64_t beforeDecimal = (int64_t)double_parameter;
			   int64_t front = beforeDecimal;
			   double afterDecimal = double_parameter - beforeDecimal;
			   afterDecimal = afterDecimal*10;
			   while(afterDecimal >  .5 )
			   {
			      beforeDecimal = (int64_t)afterDecimal;
				  int64_t temp = beforeDecimal; 
				  do
				  {
					tempPrint[i++] = beforeDecimal % 10 + '0';
				  } while((beforeDecimal /= 10) > 0);

				  afterDecimal = (afterDecimal - temp);
				  afterDecimal = afterDecimal*10;
			   }
			   int64_t tempI = i;
			   i = 0;
			   //conver to char *
			   if(front < 0)
			   {
			      sign = 1;
			      front = -front;
			   }
				toPrint[i++] = '.';
			   do 
			   {
				  toPrint[i++] = front % 10 + '0';
				} while ((front /= 10) > 0);
				if (sign == 1)
				{
					toPrint[i++] = '-';
				 }
				 toPrint[i] = '\0';
				
			 /* REVERSE */
			
			    int64_t counter, temp1, temp2;

			    for(counter = 0, temp2 = i-1; counter < temp2; counter++, temp2--)
				{
					 temp1 = toPrint[counter];
				     toPrint[counter] = toPrint[temp2];
				     toPrint[temp2] = temp1;
                }

				for(int x = 0; x < tempI; x++)
				{
				   if(x == 6)
				   {
				      break;
				   }
				   
				   toPrint[i++] = tempPrint[x];
				}
				while(tempI < 6)
				{
				   toPrint[i++] = '0';
				   tempI++;
				}
			   

			   write(1, toPrint, i);
			   bytes_written += i;

               break;
			}
            //hex, use uint64_t
            case 'x':
			{
			   char str[64];
			   int i, count;
			   uint64_t hex_parameter = va_arg(args, uint64_t);
			   char map[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
			   
			   for(i = 0; hex_parameter != 0; i++){
				  
				  str[i] = map[hex_parameter % 16];
					
				  hex_parameter = (uint64_t)(hex_parameter / 16);

			   }
			   char str_new[i];
	
			   for(count = 0; count < i; count++){
			      str_new[count] = str[i - count - 1];
			   }
			   str_new[count] = '\0';
			   
			   write(1, str_new, count);
			   bytes_written += count;
			   break;
			}
			//EXTRA CREDIT. string, use char *
			case 's':
			{
			   char * string_parameter = va_arg(args, char *);
			   //get length of the char * then print that out using write(1, char *, length)
			   uint64_t length = 0;
			   for(length = 0; string_parameter[length]; length++);
			   
			   write(1, string_parameter, length);
  		       break;
			}
            default:
			   break;
        }
	  }
	  else
	  {
		//here we write out anything not specified as a type of variable
		char printIt[1] = {c};
		write(1, printIt, 1);
		bytes_written += 1;
	  }
   }

   //va_end() required to free resources and printf must return the # of bytes_written
   va_end(args);	
   return bytes_written;
}

int snprintf(char *dest, size_t size, const char *fmt, ...)
{
   int bytes_written = 0;
   char c;
   char *send = new char[size];

   va_list args;
   va_start(args, fmt);

   while(c = *fmt++){
      if(c == '%'){
	     c = *fmt++;
		 switch(c){
		    case 'd':
			{
			   int64_t decimal_parameter = va_arg(args, int64_t);
			   int64_t i, sign;
			   sign = 0;
			   char toPrint[size];

			   if(decimal_parameter < 0){
			      sign = 1;
				  decimal_parameter = -decimal_parameter;
			   }
			   i = 0;
			   do{
			      toPrint[i++] = decimal_parameter % 10 + '0';
			   }while((decimal_parameter /= 10) > 0);
			   if(sign == 1){
				   toPrint[i++] = '-';
			   }

			   int64_t counter, tmp1, tmp2;

			   for(counter = 0, tmp2 = i-1; counter < tmp2; counter++, tmp2--){
			      tmp1 = toPrint[counter];
				  toPrint[counter] = toPrint[tmp2];
				  toPrint[tmp2] = tmp1;
			   }
				  for(int j = 0; j < i; j++)
				  {
				    send[bytes_written++] = toPrint[j];
				  }
			   break;
			}
			case 'f':
			{
		       double double_parameter = va_arg(args, double);
			   char toPrint[size];
			   char tempPrint[size];
			   int64_t i = 0;
			   int sign = 0;

			   int64_t beforeDecimal = (int64_t)double_parameter;
			   int64_t front = beforeDecimal;
			   double afterDecimal = double_parameter - beforeDecimal;
			   afterDecimal = afterDecimal*10;
			   while(afterDecimal > .5){
			      beforeDecimal = (int64_t)afterDecimal;
				  int64_t temp = beforeDecimal;
				  do{
				     tempPrint[i++] = beforeDecimal % 10 + '0';
				  }while((beforeDecimal /= 10) > 0);

				  afterDecimal = (afterDecimal - temp);
				  afterDecimal = afterDecimal*10;
			   }
			   int64_t tempI = i;
			   i = 0;
			   if(front < 0){
				  sign = 1;
				  front = -front;
			   }
			   toPrint[i++] = '.';
			   do{
				  toPrint[i++] = front % 10 + '0';
			   }while((front /= 10) > 0);
			   if(sign == 1){
				  toPrint[i++];
			   }

			   int64_t counter, tmp1, tmp2;

			   for(counter = 0, tmp2 = i-1; counter < tmp2; counter++, tmp2--){
				  tmp1 = toPrint[counter];
				  toPrint[counter] = toPrint[tmp2];
				  toPrint[tmp2] = tmp1;
			   }

			   for(int x = 0; x < tempI; x++){
				  if(x == 6){
					 break;
				  }
				  toPrint[i++] = tempPrint[x];
			   }
			   while(tempI < 6){
				  toPrint[i++] = '0';
				  tempI++;
			   }

				  for(int j = 0; j < i; j++)
				     send[bytes_written++] = toPrint[j];
			  			   break;
			}
			case 'x':
			{
			   char str[64];
			   int i, count;
			   uint64_t hex_parameter = va_arg(args, uint64_t);
			   char map[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

			   for(i = 0; hex_parameter != 0; i++){
				  str[i] = map[hex_parameter % 16];
				  hex_parameter = (uint64_t)(hex_parameter / 16);
			   }

			   char str_new[i];
			   
			   for(count = 0; count < i; count++){
				  str_new[count] = str[i - count - 1];
			   }

			      for(int j = 0; j < count; j++)
				     send[bytes_written++] = str_new[j];
			   break;
			}
			case 's':
			{
			   char * string_parameter = va_arg(args, char *);
			   //get length of the char * then print that out using write(1, char *, length)
			   uint64_t length = 0;
			   for(length = 0; string_parameter[length]; length++);
			   
			   for(int j = 0; j < length; j++)
				   send[bytes_written++] = string_parameter[j];
  		       break;
			}
			default:
				break;
		 }
	  }else{
		 send[bytes_written++] = c;
	  }
   }
   
   send[bytes_written] = '\0';

   int ll = 0;
   while(ll < size && send[ll] != '\0'){
	    
	  dest[ll] = send[ll];
	  ll++;
	  dest[ll] = '\0';
   }

   return ll;
}




#include <stdio.h>
#include <stdlib.h>
int main(){

   char *ptr;
   char buffer;
   char count=0;
   char size=10;

   printf("Please enter your name \n");

   ptr=(char *)malloc(size*sizeof(char));

   if (ptr==NULL){
      printf("Memory allocation failed \n");
      return 1;
   }
   while(1){
      buffer=getchar();

      if (buffer=='\n' || buffer ==EOF){
         break; 
      }
      if (count +1 >=size){
         size*=2;
        ptr=(char *) realloc(ptr,size*sizeof(char));
      }
      ptr[count]=buffer;
      count++;
   }

   printf("%s \n",ptr);
   return 0;

}

#include <stdio.h>
#include <conio.h>

main()
{
   int x, y;

   x = 10;
   y = 10;

   gotoxy(x, y);

   printf("C program to change cursor position.");

   getch();
   return 0;
}

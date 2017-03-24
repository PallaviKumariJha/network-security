/* following code is inspired from the envaddr.c code provided in lab hours and modified according to the need */

#include <stdio.h>
#include <stdlib.h>

void main()
{
  char* shell = getenv("EGG");

  if (shell)
      printf("%p\n", shell);

}

#include<stdio.h>

int main()
{
int a = 5; // 00000000 00000000 00000000 00000101

printf("\nNumber is Shifted By 1 Bit  : %d", a >> 1);   // 00000010
printf("\nNumber is Shifted By 2 Bits : %d", a >> 2);   // 00000001
printf("\nNumber is Shifted By 3 Bits : %d\n", a >> 3); // 00000000

return(0);
}

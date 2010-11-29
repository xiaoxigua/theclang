#include <stdio.h>

int main(void)
{
    char my_string1[]     = "1234567890";
    char my_string2[10] = "1234567890";

    printf("Size of my_string1 containing '%d' is %d\n", my_string1,sizeof(my_string1));
    printf("Size of my_string2 containing '%d' is %d\n", my_string2,sizeof(my_string2));
    printf("my_string1[9] is %c\n",my_string1[9]);
    printf("my_string2[9] is %c\n",my_string2[9]);
    return 0; 
}

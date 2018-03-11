#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

int main(void)
{
    printf("Enter the message: ");
    scanf("%[^\n]s", message);

    key_generation();

    encryption();
    decryption();

    return 0;
}

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "functions.h"

static unsigned long long int p, q, n, e, d;
static unsigned long long int encrypted_text[BUFSIZE];
static char decrypted_text[BUFSIZE];

static int greatest_common_divisior(unsigned long long int, unsigned long long int);
static int prime(long long int);
static int multiple_and_mod(int, unsigned long long int, unsigned long long int);

void encryption()
{
    printf("\nEncrypted_text:\t");
    for(int i=0; message[i]!='\0'; ++i){
      /* message^e (mod n) = cipher text */
      encrypted_text[i] = multiple_and_mod(message[i], e, n);
      printf("%d ", encrypted_text[i]);
    }
}

void decryption()
{
    for(int i=0; message[i]!='\0'; ++i)
      /* cipher text^d (mod n) = message */
      decrypted_text[i] = multiple_and_mod(encrypted_text[i], d, n);
    printf("\nDecrypted_message: %s\n", decrypted_text);
}


/* key_generation: produce 2 prime numbers, encryption key and decryption key */
void key_generation()
{
    srand(time(NULL));
    /* produce 2 prime numbers */
    do{
        p = (rand() % 100)+5;
    }while(prime(p)==1);

    do{
        q = (rand() % 100)+5;
    }while(prime(q)==1);

    printf("p: %ld\nq: %ld\nn: %ld\n", p, q, (p)*(q));
    unsigned long long int phi_n = (p-1) * (q-1);

    /* produce encryption key */
    do{
        e = rand() % phi_n;
    }while(e<3 || greatest_common_divisior(e, phi_n));

    int temp, i=1;

    /* produce decryption key */
    do{
        d = ((phi_n * i) + 1) / e;
        ++i;
	temp = ((e)*(d)) % phi_n;
    }while (temp != 1 || e == d);

    n = p*q;

    printf("\nPublic Encryption Key: %ld\nSecret Decryption Key: %ld\n", e, d);
}

static int multiple_and_mod(int text, unsigned long long int k, unsigned long long int n)
{
  unsigned long long int character=1;
  for( ; k>0; --k)
    character = (character * text) % n; /* I use this method to prevent overflow */
  return character;
}

/* check if a and b are relatively prime */
static int greatest_common_divisior(unsigned long long int a, unsigned long long int b)
{
    unsigned long long int r;

    if(a<b){
        unsigned long long int temp = a;
        a = b;
        b = temp;
    }

    while(b!=0){
        r = a % b;
        a = b;
        b = r;
    }

    return (a==1)?0:1;
}

/* prime: check if n is prime */
static int prime(long long int n)
{
    int i;
    int flag = 0;
    for(int i=2; i<n; ++i){
        if(n%i == 0){
          flag=1;
        }
    }
    if(flag == 1)
      return 1;
    return 0;
}

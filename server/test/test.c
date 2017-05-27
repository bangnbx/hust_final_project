#include <stdio.h>
void encrypt(int size, unsigned char *buffer);

void encrypt(int size, unsigned char *buffer){
    for(int i=0; i < size; i++){
        unsigned char c = buffer[i];
        printf("%c",c);
    }
}

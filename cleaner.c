#include<stdio.h>
#include<string.h>
#include<stdlib.h>

static void free_int(int** p){
    free(*p);
}

static void free_str(char** str){
    free(*str);
}

char* return_from_func(void){
    [[gnu::cleanup(free_str)]] char* buff = malloc(128);

    //fill buff
    char* returnVal = buff;
    buff = NULL;
    return returnVal;
}


int main(){
    [[gnu::cleanup(free_int)]] int* data = malloc(4);
    *data = 42;

    return 0;
}
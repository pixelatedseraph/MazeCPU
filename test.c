#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef struct{
    int a;
    int b;
    int c;
}Inner;

typedef struct{
    int x;
    Inner inner;
}Outer;

void modify(Outer* outer){
    outer->x = 3;

    outer->inner.a = 5;
    outer->inner.b = 10;
    outer->inner.c = 15;

}


int main(){
    Inner inner = {.a = 1,.b = 2,.c = 3};
    Outer outer = {.x = 100,.inner = inner};

    printf("Before (.x = %d),(.inner = %d %d %d) \n",outer.x,inner.a,inner.b,inner.c);

    modify(&outer);

    printf("After (.x = %d),(.inner = %d %d %d)\n",outer.x,inner.a,inner.b,inner.c);


    return 0;
}
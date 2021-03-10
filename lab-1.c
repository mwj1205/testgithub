#include <stdio.h>
int main()
{
    char charType;
    int integerType;
    float floatType;
    double doubleType;

    printf("[----- [한민우] [2018038047] -----]\n");
    
    // 각 자료형의 크기를 출력한다
    printf("Size of char: %ld byte\n",sizeof(charType));
    printf("Size of int: %ld bytes\n",sizeof(integerType));
    printf("Size of float: %ld bytes\n",sizeof(floatType));
    printf("Size of double: %ld bytes\n",sizeof(doubleType));

    printf("-----------------------------------------\n");
    // 각 자료형의 크기를 출력한다
    printf("Size of char: %ld byte\n",sizeof(char));
    printf("Size of int: %ld bytes\n",sizeof(int));
    printf("Size of float: %ld bytes\n",sizeof(float));
    printf("Size of double: %ld bytes\n",sizeof(double));

    printf("-----------------------------------------\n");
    // 자료형의 크기가 아닌 포인터의 크기를 출력한다
    // 32비트에선 4바이트 64비트에선 8바이트로 주소를 저장하기 때문에
    // 32비트에선 4바이트 64비트에선 8바이트로 출력된다
    printf("Size of char*: %ld byte\n",sizeof(char*));
    printf("Size of int*: %ld bytes\n",sizeof(int*));
    printf("Size of float*: %ld bytes\n",sizeof(float*));
    printf("Size of double*: %ld bytes\n",sizeof(double*));
    return 0;
}

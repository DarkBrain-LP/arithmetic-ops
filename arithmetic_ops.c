#include <stdlib.h>
#include <stdio.h>

#define ZERO 0
#define ONE 1

int increment(int);
int nb_bits(int);
char* binary_representation(int);
void test_binary_repr(void);
int add(int, int);
void test_add(void);

int main(void){
    test_add();
    return 0;
}

void test_add(void){
    int a = 10;
    int b = 5;
    scanf("%i", &a);
    getchar();
    scanf("%i", &b);
    getchar();
    int sum = a+b;
    printf("%i + %i = %i", a, b, sum);
}

int add(int first, int second){
    int result = 0;
    int current_bits_sum = 0;
    int remainder = 0;
    int iteration_count = 0;

    while (first && second)
    {
        if((first & 1) && (second & 1) && remainder){
            current_bits_sum = 1;
            remainder = 1;
        }
        else if(!((first & 1) || (second & 1) || remainder)){
            current_bits_sum = 0;
            remainder = 0;
        }
        else{
            if((first & 1) ^ (second & 1) ^ (remainder)){
                current_bits_sum = 1;
                remainder= 0;
            }
            else{
                current_bits_sum = 0;
                remainder= 1;
            }
        }

        result <<= 1;
        result |= current_bits_sum;

        first >>= 1;
        second >>= 1;

        iteration_count ++;
    }

    result <<= iteration_count;
    result |= first? first: second;

    return result;
}

void test_binary_repr(void){
    char* test = binary_representation(0xF1);
    printf("%s", test);
    free(test);
}

char* binary_representation(int number){
    int n = nb_bits(number);
    char* binary = malloc((n+1) * sizeof(char));
    binary[n] = '\0';

    while(number & (~0)){
        n--;
        binary[n] = (number & 1) + '0';
        number = number >> 1;
    }

    return binary;
}

int nb_bits(int number){
    int n = 0;

    while(number & (~0)){
        number = number >> 1;
        n = increment(n);
    }

    return n;
}



int increment(int number){
    
    return ++number;
//     if(number & 0){
//         return number | 1;
//     }

//     number &= ~(1);

//     while((number >> 1) & 1){
//         int incr = increment(number >> 1) ;
//         number = (incr << 1) || (number & 1); // incorrect
//     }

//     return number;
}
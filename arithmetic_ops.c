#include <stdlib.h>
#include <stdio.h>

#define ZERO 0
#define ONE 1

int increment(int);
void test_increment(void);
int nb_bits(int);
char* binary_representation(int);
void test_binary_repr(void);
int add(int, int);
void test_add(void);

int main(void){
    // test_increment();
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
    int sum = add(a,b);
    printf("%i + %i = %i", a, b, sum);
}

int add_same_bit_numbers(int bits, int first, int second){
    int result = 1;
    int current_bits_sum = 0;
    int remainder = 0;
    int iteration_count = 0;
    while (first || second)
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
            if(((first & 1) ^ (second & 1) ^ (remainder)) == ONE){
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

        iteration_count ++;
        printf("first= %i second= %i remainder= %i, iter=%i", first&1, second&1, remainder, iteration_count);
        printf("\tresult= %i\n", result);
        first >>= 1;
        second >>= 1;
    }

    return result;
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

        iteration_count ++;
        printf("first= %i second= %i remainder= %i, iter=%i", first&1, second&1, remainder, iteration_count);
        printf("\tresult= %i\n", result);
        first >>= 1;
        second >>= 1;
    }

    int remaining_value = first? first: second;
    printf("remaining = %i, shift=%i\n", remaining_value, iteration_count);
    if(remaining_value){
        if(remainder)
            remaining_value = increment(remaining_value);
        
        printf("new_remaining = %i\n", remaining_value);
    }
    remaining_value <<= iteration_count;
    printf("remaining after shift = %i\n", remaining_value);
    // if(remainder){
    //     if(current_bits_sum == 0)
    //         remaining_value = (remainder << (iteration_count));
    // }
    // printf("remaining after shift = %i\n", remaining_value);
    remaining_value |= result;

    return remaining_value;
}

void test_increment(void){
    int n = 0;
    scanf("%i", &n);
    printf("%i", increment(n));
}

int increment(int number){
    if(!(number&1)){
        return number | 1;
    }
    int shift = 0;
    while (number & 1)
    {
        number >>= 1;
        shift ++;
    }
    number <<= shift;
    number |= (1<<shift);
    
    return number;
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
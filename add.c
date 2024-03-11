#include <stdio.h>
#include <stdlib.h>

int add_three_bits(int first, int second, int third);
int add_same_bit_numbers(int first, int second, int len);
int add(int first, int second);
int bit_count(int number);
int right_nbits(int number, int n);
void test_add_three_bits();
void test_add_same_bit_numbers();
void test_add();
void test_bit_count();
void test_right_nbits(int number, int n, int expected);
void global_test_add_three_bits();
void global_test_add_same_bit_numbers();
void global_test_add();

int bit_count(int number){
    int n = 0;

    while(number & (~0)){
        number = number >> 1;
        n = add_three_bits(n,1,0);
    }

    return n;
}
void test_bit_count()
{
    int n = 35;
    int real_value = 6;
    int res = bit_count(35);
    printf("test_bit_count : ");
    if(res == real_value)
    {
        printf("succeeded\n");
    }
    else{
        printf("failed\n");
    }
}

int main(void){
    // global_test_add_three_bits();
    test_bit_count();
    global_test_add_same_bit_numbers();
    return 0;
}

void global_test_right_nbits()
{
    test_right_nbits(0b111001,3,0b001);
}

void test_right_nbits(int number, int n, int expected){
    int result = right_nbits(number, n);
    if(result == expected){
        printf("succeeded\n");
    }
    else{
        printf("failed\n");
    }
}

int right_nbits(int number, int n)
{
    int bits = 0; // represents 111... (n time)
    for(int i = 0; i < n; i++)
    {
        bits <<= 1;
        bits |= 1;
    }

    return number&bits;
}

int add(int first, int second)
{
    int first_len = bit_count(first);
    int second_len = bit_count(second);

    int first_input = 0;
    int second_input = 0;
    first_input = (first_len > second)?right_nbits(first, first_len):right_nbits(second, second_len);
    // right bit could start with 0, hence the shortened number won't be of the same length as the second one...
    second_input = (first_len > second)? second: first;

    int same_bit_addition_result = add_same_bit_numbers(first_input, second_input, bit_count(first_input));

    return 0;
}

int same_bit_number_coded_addition(int first, int second, int len)
{
    int result = 0;

    // set the result to FFF... (len time)
    for(int i = 0; i < len; i++)
    {
        result <<= 1;
        result |= 1;
    }

    int bits_sum = 0;
    int first_bit = 0;
    int second_bit = 0;
    int remainder = 0;
    for(int i = 0; i < len; i++)
    {
        first_bit = (first >> i) & 1;
        second_bit = (second >> i) & 1;
        bits_sum = add_three_bits(first_bit, second_bit, remainder);
        int sum_first_bit = (bits_sum&1);
        remainder = (bits_sum>>1)&1;

        // set the i-th bit to 0, then add the correct value of the bit(the addition's result)
        result &= ~(1<<i);
        result |= (sum_first_bit<<i);
    }
    
    // Here the remainder is coded at the end of the result
    result <<= 1;
    result |= (remainder&1);
    return result;
}


void global_test_add_same_bit_numbers()
{
    test_add_same_bit_numbers(5,5,3);
    test_add_same_bit_numbers(5,7,3);
    test_add_same_bit_numbers(10,10,4);
    test_add_same_bit_numbers(15,15,4);
    test_add_same_bit_numbers(10,8,4);
    test_add_same_bit_numbers(2,3,2);
    test_add_same_bit_numbers(16,17,5);
    test_add_same_bit_numbers(35,35,6);
}
void test_add_same_bit_numbers(int first, int second, int len)
{
    int result = add_same_bit_numbers(first, second, len);
    if((first+second) == result)
    {
        printf("sucess => ");
    }
    else{
        printf("failed => ");
    }
    printf("%i + %i = %i\n", first, second, result);
}

int add_same_bit_numbers(int first, int second, int len)
{
    int result = 0;

    // set the result to FFF...len time
    for(int i = 0; i < len; i++)
    {
        result <<= 1;
        result |= 1;
    }

    int bits_sum = 0;
    int first_bit = 0;
    int second_bit = 0;
    int remainder = 0;
    for(int i = 0; i < len; i++)
    {
        first_bit = (first >> i) & 1;
        second_bit = (second >> i) & 1;
        bits_sum = add_three_bits(first_bit, second_bit, remainder);
        int sum_first_bit = (bits_sum&1);
        remainder = (bits_sum>>1)&1;

        // set the i-th bit to 0, then add the correct value of the bit(the addition's result)
        result &= ~(1<<i);
        result |= (sum_first_bit<<i);
    }
    
    result |= (remainder<<len);
    return result;
}

void global_test_add_three_bits()
{
    test_add_three_bits(0,0,0);
    test_add_three_bits(0,0,1);
    test_add_three_bits(0,1,0);
    test_add_three_bits(0,1,1);
    test_add_three_bits(1,0,0);
    test_add_three_bits(1,0,1);
    test_add_three_bits(1,1,1);
}

void test_add_three_bits(int first, int second, int third)
{
    int addition_value = add_three_bits(first,second,third);
    if((first+second+third) == addition_value)
    {
        printf("sucess => ");
    }
    else{
        printf("failed => ");
    }
    int result = addition_value&1;
    int remainder = (addition_value>>1)&1;
    printf(" %i + %i + %i = %i and remainder = %i\n", first, second, third, result, remainder);
}

int add_three_bits(int first, int second, int third)
{
    int result = 0;
    int remainder = 0;

    // based on 3 bits addition truth table
    if((first & 1) && (second & 1) && third)
    {
        result = 1;
        remainder = 1;
    }
    else if(!((first & 1) || (second & 1) || third))
    {
        result = 0;
        remainder = 0;
    }
    else
    {
        if(((first & 1) ^ (second & 1) ^ (third)) == 1)
        {
            result = 1;
            remainder= 0;
        }
        else
        {
            result = 0;
            remainder = 1;
        }
    }

    return (remainder<<1)|(result & 1);
}
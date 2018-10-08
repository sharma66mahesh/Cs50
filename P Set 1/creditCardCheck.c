#include<stdio.h>

void manipDigits(int *sum, int digit)
{
    int t1, t2;
    t1 = (2 * digit) % 10;
    t2 = (2 * digit) / 10;
    *sum += t1 + t2;
}

int main()
{
    long long int number;
    scanf("%lld", &number);

    int *digits, sum1=0, sum2=0;
    long long int temp = number;

    int digitCount = 1;
    while(temp /= 10)
    {
        digitCount++;
    }
    if(digitCount < 13)
        printf("INVALID\n");
    printf("digit count %d\n", digitCount);

    digits = (int*)malloc(sizeof(int) * digitCount);

    int i = 0;
    while(number > 0)
    {
        digits[i] = number % 10;
        number /= 10;
        i++;
    }

    sum2 = digits[digitCount - 1];
    i = digitCount - 2;
    while(i >= 0)
    {
        if(digits[i] < 5)
            sum1 += 2 * digits[i];
        else
        {
            manipDigits(&sum1, digits[i]);
        }
        i--;
        if(i >= 0){
            sum2 += digits[i];
        }
        i--;
    }
    if((sum1 + sum2) % 10 == 0)
    {
        if(digitCount == 15 && (digits[digitCount-1] == 3 && (digits[digitCount - 2] == 4 || digits[digitCount - 2] == 7)))
            printf("AmEx\n");
    }
}

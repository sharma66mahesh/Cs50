#include<stdio.h>
#include<math.h>

int coinNumber(float cost)
{
    int coinSize[] = {25, 10, 5, 1};
    int count = 0, cents;
    cents = round(cost * 100);
    int i;
    for(i = 0; i < 4; i++){
        count += cents / coinSize[i];
        cents %= coinSize[i];
        printf("%d and %d\n", cents, count);
    }

    printf("cost is %d\n", cents);
    return count;
}

int main()
{
    float cost;
    scanf("%f", &cost);
    printf("Total number of coins required is %d\n", coinNumber(cost));
    return 0;
}

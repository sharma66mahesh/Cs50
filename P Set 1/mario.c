#include<stdio.h>

int main()
{
    int height;
    do{
    printf("Height: ");
    scanf("%d", &height);
    }while(height < 0 || height > 23);
    int i, j, k;
    for(i = 1; i <= height; i++)
    {
        for(k = height-i-1; k >= 0; k--)
        {
            printf(" ");
        }

        for(j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf(" ");
        for(j = 1; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}

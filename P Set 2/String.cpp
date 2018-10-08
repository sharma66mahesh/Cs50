#include<iostream>
#include<string>
#include<cstdio>
using namespace std;

int main()
{
    while(1){
        char name[40];
        int i = 0;
        while(scanf("%c", &name[i++]))
        {
            if(name[i-1] == '\n')
                break;
        }
        name[i-1] = '\0';
        i = 0;
        while(name[i] != '\0')
        {
            if(name[i-1] == ' ' || i == 0)
                printf("%c", toupper(name[i]));
            i++;
        }
    }
}

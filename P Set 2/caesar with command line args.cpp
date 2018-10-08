#include<iostream>
#include<cstdlib>
using namespace std;

int main(int argc, char*argv[])
{
    int temp;
    int k = atoi(argv[1]);  //no. of times the msg letters are to be rotated
    const int MODULO = 26;
    string msg = "";
    int i = 2;
    while(i++ <= argc-2)
    {
        msg += string(argv[i]);
        msg += " ";
    }

    for(int i = 0; i < msg.length(); i++)
    {
        temp = static_cast<int>(msg[i]);
        if(temp >= 65 && temp <= 90)   //A-Z
        {
            msg[i] = static_cast<char>((temp+k-65) % 26 + 65);
        }
        if(msg[i] >= 97 && msg[i] <= 122)   //a-z
        {
            msg[i] = static_cast<char>((temp+k-97) % 26 + 97);
        }
    }
    cout << msg;
}

#include<iostream>

using namespace std;

int main(int argc, char*argv[])
{
    int temp;
    int k;  //no. of times the msg letters are to be rotated
    cin >> k;
    const int MODULO = 26;
    string msg;
    cin.ignore();   //we've already used cin, and cin has \n char in its stream. we need to clear it before we can read a line with delimiter \n
    getline(cin,msg);  //these two lines to read a sentence.
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

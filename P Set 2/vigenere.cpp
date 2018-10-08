//command line arg is a key for no. of times the letters must be shifted in the messages
#include<iostream>
#include<cstdio>

using namespace std;

int main(int argc, char* argv[])
{
    if(argc != 2)
        return 1;

    string msg;
    getline(cin, msg);

    string key = string(argv[1]);

    int j = 0, temp, subVal;    //subVal may equal 65 or 97 depending on case of subVal(uppercase or lowercase)
    for(int i = 0; i < msg.length(); i++)
    {
        temp = static_cast<int>(msg[i]);

        if(key[j] >= 65 && key[j] <= 90)
            subVal = 65;
        else if(key[j] >= 97 && key[j] <= 122)
            subVal = 97;
        else
            return 1;

        if(temp >= 65 && temp <= 90)   //A-Z
        {
            msg[i] = static_cast<char>((temp+static_cast<int>(key[j])-65-subVal) % 26 + 65);
            j = (j+1) % key.length();
        }
        if(msg[i] >= 97 && msg[i] <= 122)   //a-z
        {
            msg[i] = static_cast<char>((temp+static_cast<int>(key[j])-97-subVal) % 26 + 97);
            j = (j+1) % key.length();
        }
    }
    cout << msg;
}

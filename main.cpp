#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>
#include <ctime>
#include <cstdlib>
#include <string>

struct Dict
{
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::string specials[23] = {"!", "£", "$", "%", "^", "&", "*", "(", ")", "@", ";", ":", "<", ">", ",", ".", "#", "{", "}", "[", "]"};
};

struct Settings
{
    int _passwordLength = 0;
    bool _includeSymbols = false;
    bool _includeNumbers = false;
    bool _includeLowercase = false;
    bool _includeUppercase = false;
};

int get_random(int min, int max)
{
    srand(static_cast<unsigned int>(time(0)));
    return rand() % (max - min + 1) + min;
}

int main()
{
    std::cout << "Hello world" << std::endl;
    return 0;
}

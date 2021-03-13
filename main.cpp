#include <iostream>
#include <string>
#include <ctime>

struct Dict
{
    char letters[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    int numbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::string specials[23] = {"!", "£", "$", "%", "^", "&", "*", "(", ")", "@", ";", ":", "<", ">", ",", ".", "#", "{", "}", "[", "]"};
};

struct Settings
{
    int _passwordLength{};
    bool _includeSymbols{};
    bool _includeNumbers{};
    bool _includeLowercase{};
    bool _includeUppercase{};
};

int get_random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

std::string generate_password(Settings s)
{
    Dict d{};
    std::string result = "";

    int choices[4] = {0, 0, 0, 0};

    // this is really ugly lol oh well
    choices[0] = (s._includeLowercase ? 1 : 0);
    choices[1] = (s._includeUppercase ? 2 : 0);
    choices[2] = (s._includeNumbers ? 3 : 0);
    choices[3] = (s._includeSymbols ? 4 : 0);

    for (int i = 0; i < s._passwordLength; i++)
    {
        int choice = 0;

        bool found = false;
        for (int i = 0; i < 4; i++)
        {
            if (choices[i] != 0)
            {
                found = true;
            }
        }

        if (found == false)
        {
            return "very funny";
        }

        while (choice == 0)
        {
            choice = choices[get_random(0, 3)];
        }
        switch (choice)
        {
        case 1:
            result += d.letters[get_random(0, 26)];
            break;
        case 2:
            result += toupper(d.letters[get_random(0, 25)]);
            break;
        case 3:
            result += std::to_string(d.numbers[get_random(0, 9)]);
            break;
        case 4:
            result += d.specials[get_random(0, 22)];
            break;
        }
    }
    return result;
}

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int length;
    char lowercase;
    char uppercase;
    char numbers;
    char symbols;

    std::cout << "How long would you like the password to be: " << std::endl;
    std::cin >> length;
    std::cout << "Include lower-case characters? (y/n): " << std::endl;
    std::cin >> lowercase;
    std::cout << "Include upper-case characters? (y/n): " << std::endl;
    std::cin >> uppercase;
    std::cout << "Include numbers? (y/n): " << std::endl;
    std::cin >> numbers;
    std::cout << "Include special characters? (y/n): " << std::endl;
    std::cin >> symbols;

    Settings s{
        length,
        toupper(symbols) == 'Y' ? 1 : 0,
        toupper(numbers) == 'Y' ? 1 : 0,
        toupper(lowercase) == 'Y' ? 1 : 0,
        toupper(uppercase) == 'Y' ? 1 : 0};

    std::string password = generate_password(s);

    std::cout << password << std::endl;
    return 0;
}

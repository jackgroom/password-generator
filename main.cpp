//
//  main.cpp
//  password generator
//
//  Created by jack on 30/03/2022.
//

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <map>
#include <vector>

// enums for the different character types (for switch statement etc)
enum CharacterType {
    lowercase,
    uppercase,
    number,
    symbol
};

// struct for housing user's password settings
struct Settings {
    int passwordLength;
    bool includeLowercase;
    bool includeUppercase;
    bool includeNumbers;
    bool includeSymbols;
};

// ranges for generating random symbols (ascii values)
std::pair<int, int> bounds [4] = {
    std::make_pair(33, 47),
    std::make_pair(60, 64),
    std::make_pair(91, 96),
    std::make_pair(123, 126)
};

std::string generatePassword(Settings* passwordSettings) {
    std::string generated_password = "";
    
    // map options to string in dictionary
    std::map<CharacterType, bool> settings_map = {
        {lowercase, passwordSettings->includeLowercase},
        {uppercase, passwordSettings->includeUppercase},
        {number, passwordSettings->includeNumbers},
        {symbol, passwordSettings->includeSymbols}
    };
    
    // vector/array to store selected options
    std::vector<CharacterType> options;
    
    // push selected options to array/vector for random indexing
    std::map<CharacterType, bool>::iterator it;
    for (it = settings_map.begin(); it != settings_map.end(); it++) {
        if (it->second) { // if the setting is set to 'true'
            options.push_back(it->first); // add the setting enum to array (so it can be indexed)
        }
    }
    
    for (int i = 0; i < passwordSettings->passwordLength; i++) {
        // get random index in array/vector of options
        CharacterType randomIndex = options[rand() % options.size()];
        switch(randomIndex) {
            case lowercase:
                // random lowercase character
                generated_password += 97 + rand() % 26;
                break;
            case uppercase:
                // random uppercase character
                generated_password += 65 + rand() % 26;
                break;
            case number:
                // random number
                generated_password += 48 + rand() % 10;
                break;
            case symbol:
            {
                // generate a random symbol based on ascii bounds
                std::pair<int, int> chosenRange = bounds[rand() % 4];
                generated_password += chosenRange.first + rand() % (chosenRange.second - chosenRange.first);
                break;
            }
            default:
                // returns a random ascii character
                generated_password += 33 + rand() % 93;
                break;
        }
    }
    
    return generated_password;
}

int getPasswordLength() {
    int passwordLength = -1;
    
    while (passwordLength < 0 || passwordLength > 30) {
        int temp;
        std::cout << "Enter desired password length: ";
        std::cin >> temp;
        
        if (std::cin.good()) {
            passwordLength = temp;
        } else if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
    
    return passwordLength;
}

bool getPasswordSetting(std::string question) {
    bool response = false;
    bool hasResult = false;
            
    // validating input for y/n (and converting to boolean true/false)
    while (!hasResult) {
        std::string result;
        std::cout << question << " (y/n): ";
        std::cin >> result;
                
        std::string substring = result.substr(0, 1);
        std::transform(substring.begin(), substring.end(), substring.begin(), ::toupper); // convert string to uppercase
                                                                                          // (has to be done on chars, so iterate over string and
                                                                                          // change each char individually, even though sub string made
                                                                                          // it single character)
        
        if (substring == "Y" || substring == "N") {
            hasResult = true;
            response = substring == "Y" ? true : false;
        }
    }
    return response;
}

int main(int argc, const char * argv[]) {
    srand(static_cast<unsigned int>(time(0)));
    
    Settings settings = {
        getPasswordLength(),
        getPasswordSetting("Include lowercase letters?"),
        getPasswordSetting("Include uppercase letters?"),
        getPasswordSetting("Include numbers?"),
        getPasswordSetting("Include symbols?")
    };

    std::cout << generatePassword(&settings) << std::endl;
    
    std::cout << "Press any key to exit...";
    std::getchar();
        
    return 0;
}

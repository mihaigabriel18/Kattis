//#include "../allHeaders.h"
#include <iostream>

using std::string;

int main()
{
    // string to keep the "aah" i can say 
    std::string myAh;
    // string to keep the "aah" the doctor wants me to say
    std::string doctorAh;

    std::cin >> myAh >> doctorAh;

    // + 1 so it returns 1 when strings are equal
    std::string resultStr = myAh.length() >= doctorAh.length() ? "go" : "no";
    std::cout << resultStr;

    return 0;
}
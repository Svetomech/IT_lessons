#include <iostream>

int main()
{
    std::string number;
    std::cin >> number;
    
    bool isPalindrome = true;
    
    int l = number.length();
    
    for (int i = 0; i < l; ++i)
    {
        isPalindrome = (number[i] == number[l - i - 1]) && isPalindrome;
    }
    
    std::cout << (isPalindrome ? "Number is palindrome" : "Number is NOT palindrome") << std::endl;
}

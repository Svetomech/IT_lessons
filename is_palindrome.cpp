#include <iostream>

int main()
{
    std::string number;
    std::cin >> number;
    
    bool isPalindrome = true;
    
    int l = number.length();
    
    for (int i = 0; i < l; ++i)
    {
        int digit = number[i];
        int digitFromEnd = number[l - i - 1];
        
        isPalindrome = (digit == digitFromEnd) && isPalindrome;

        if (!isPalindrome)
            break;
    }
    
    std::cout << (isPalindrome ? "Number is palindrome" : "Number is NOT palindrome") << std::endl;
}

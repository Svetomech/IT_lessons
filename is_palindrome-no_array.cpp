#include <iostream>

int countDigits(int number)
{
    int count = 0;
    
    do
    {
        count++;
    } while (number /= 10);
    
    return count;
}

int pullDigit(int number, int positionFromEnd)
{
    while (--positionFromEnd)
    {
        number /= 10;
    }
    
    return number % 10;
}

int main()
{
    int number;
    std::cin >> number;
    
    bool isPalindrome = true;

    int digitsCount = countDigits(number);
    
    if (digitsCount % 2 == 0)
    {
        int leftPosition = digitsCount / 2;
        int rightPosition = leftPosition + 1;
        while (leftPosition > 0 && rightPosition <= digitsCount)
        {
            int leftNum = pullDigit(number, digitsCount - leftPosition);
            int rightNum = pullDigit(number, digitsCount - rightPosition);
            
            leftPosition--;
            rightPosition++;
            
            isPalindrome = (leftNum == rightNum) && isPalindrome;
        }
    }
    else
    {
        do
        {
            int num = number % 10;
            int nextNum = (number / 10) % 10;
            
            isPalindrome = (num == nextNum) && isPalindrome;
        } while ((number /= 10) && number / 10);
    }
    
    std::cout << (isPalindrome ? "Number is palindrome" : "Number is NOT palindrome") << std::endl;
}

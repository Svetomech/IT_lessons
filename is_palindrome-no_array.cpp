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
            int leftDigit = pullDigit(number, digitsCount - leftPosition);
            int rightDigit = pullDigit(number, digitsCount - rightPosition);
            
            leftPosition--;
            rightPosition++;
            
            isPalindrome = leftDigit == rightDigit;

            if (!isPalindrome)
                break;
        }
    }
    else
    {
        do
        {
            int digit = number % 10;
            int nextDigit = (number / 10) % 10;
            
            isPalindrome = digit == nextDigit;

            if (!isPalindrome)
                break;
        } while ((number /= 10) && number / 10);
    }
    
    std::cout << (isPalindrome ? "Number is palindrome" : "Number is NOT palindrome") << std::endl;
}

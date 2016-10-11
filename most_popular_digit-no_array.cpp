#include <iostream>

using namespace std;

int countOccurrences(int number, short digit)
{
	int count = 0;
	do
	{
		if (number % 10 == digit)
		{
			count++;
		}
	} while (number /= 10);
	return count;
}

int main()
{
	int x;
	cin >> x;
	
	int maxDigit = -1;
	int maxCount = -1;
	
	for (int i = 0; i < 10; ++i)
	{
		int count = countOccurrences(x, i);
		
		if (count >= maxCount)
		{
			maxDigit = i;
			maxCount = count;
		}
	}
	
	if (maxDigit > 0)
	{
		cout << "The most frequent digit is " << maxDigit << " with total of " << maxCount << " inclusions.";
	}
	else
	{
		cout << "You must enter a valid number.";
	}
}

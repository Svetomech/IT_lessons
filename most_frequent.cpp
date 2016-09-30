#include <iostream>

using namespace std;

int main()
{
	int x;
	cin >> x;
	
	int f[10];
	for (int i = 0; i < 10; f[i++] = 0);
	
	do
	{
		f[x % 10]++;
	} while (x /= 10);
	
	int maxDigit = -1;
	int maxCount = -1;
	
	for (int i = 0; i < 10; ++i)
	{
		if (f[i] >= maxCount)
		{
			maxDigit = i;
			maxCount = f[i];
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

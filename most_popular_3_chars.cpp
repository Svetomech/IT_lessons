#include <iostream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> splitString(std::string str, int n)
{
    std::vector<std::string> strParts;

    for (int i = 0; i < str.length(); i += n)
    {
        std::string strPart = str.substr(i, n); // std::cout << strPart << " ";

        strParts.push_back(strPart);
    }

    return strParts;
}

int main()
{
    std::string line;
    std::vector<std::string> lineParts;

    std::getline(std::cin, line);
    lineParts = splitString(line, 3);

    int partsCount = lineParts.size();
    std::map<std::string, int> occurences;

    for (int i = 0; i < partsCount; ++i)
    {
        for (int j = i + 1; j < partsCount; ++j)
        {
            if (lineParts[i] == lineParts[j])
            {
                occurences[lineParts[i]]++;
            }
        }
    }

    std::string mostPopular3Chars;
    int mostOccurences = 0;
    for (int i = 0; i < occurences.size(); ++i)
    {
        if (occurences[lineParts[i]] > mostOccurences)
        {
            mostOccurences = occurences[lineParts[i]];
            mostPopular3Chars = lineParts[i];
        }
    }

    std::cout << mostPopular3Chars <<std::endl;
}

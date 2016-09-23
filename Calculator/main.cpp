#include <iostream>
#include <fstream>
#include <string>
#include <stack>

enum class InputType
{
    Console,
    File,
    Constructor
};

class CalculationNotDoneException: public std::exception
{
    virtual const char* what() const throw()
    {
        return "The Input() method should be executed before Output()";
    }
} calc_not_done;

class Calculator
{
    public:
        std::string InputFileName;
        std::string OutputFileName;

        Calculator() :
            InputFileName("Input.txt"),
            OutputFileName("Output.txt"),
            result(0),
            calculationDone(false)
        {
            // empty constructor, totally legit
        }

        Calculator(const InputType& inputFrom)
        {
            Calculator();

            Input(inputFrom);
        }

        Calculator(const InputType& inputFrom, const std::string& expression)
        {
            Calculator();

            Input(inputFrom, expression);
        }

        Calculator(const InputType& inputFrom, const std::string& inputFileName, const std::string& outputFileName)
        {
            Calculator();

            InputFileName = inputFileName;
            OutputFileName = outputFileName;

            Input(inputFrom);
        }

        void Input(const InputType& inputFrom, const std::string& expression = "")
        {
            inputType = inputFrom;

            if (InputType::Console == inputType)
            {
                std::getline(std::cin, input);
            }
            else if (InputType::File == inputType)
            {
                std::ifstream inputFile(InputFileName);

                if (inputFile.is_open())
                {
                    std::getline(inputFile, input);

                    inputFile.close();
                }
                else
                {
                    std::cout << "Can't read from file named " << InputFileName << std::endl;

                    return;
                }
            }
            else if (InputType::Constructor == inputType)
            {
                input = expression;
            }

            processInput();
        }

        long Output()
        {
            if (!calculationDone) throw calc_not_done;

            if (InputType::Console == inputType)
            {
                std::cout << result << std::endl;
            }
            else if (InputType::File == inputType)
            {
                std::ofstream outputFile(OutputFileName);

                if (outputFile.is_open())
                {
                    outputFile << result << std::endl;

                    outputFile.close();
                }
                else
                {
                    std::cout << "Can't create a file named " << OutputFileName << std::endl;

                    return result;
                }
            }
            else if (InputType::Constructor == inputType)
            {
                // nothing specific, just return the result
            }

            calculationDone = false;

            return result;
        }

    private:
        long result;
        bool calculationDone;
        InputType inputType;
        std::string input;

        // add ^ operator
        void processInput()
        {
            std::stack<char> st;
            std::string out;

            for (int i = 0; i < input.length(); ++i)
            {
                char c = input[i];

                if (c == ')')
                {
                    while (st.top() != '(')
                    {
                        out += st.top();
                        st.pop();
                    }
                    st.pop();
                }

                if (c >= '0' && c <= '9')
                {
                    out += c;
                }

                if (c == '(')
                {
                    st.push(c);
                }

                if(c == '+' || c == '-' || c == '/' || c == '*')
                {
                    if (st.empty())
                    {
                        st.push(c);
                    }
                    else
                    {
                        if (operationPriority(st.top()) < operationPriority(c))
                        {
                            st.push(c);
                        }
                        else
                        {
                            while (!st.empty() && (operationPriority(st.top()) >= operationPriority(c)))
                            {
                                out += st.top();
                                st.pop();
                            }

                            st.push(c);
                        }
                    }
                }
            }

            while (!st.empty())
            {
                out += st.top();
                st.pop();
            }

            input = out; // std::cout << "RPN: " << out << std::endl;

            result = calculateOutput();
        }

        // add ^ operator
        int operationPriority(char sign)
        {
            switch(sign)
            {
                case '*':
                case '/':
                    return 3;

                case '-':
                case '+':
                    return 2;

                case '(':
                    return 1;
            }
        }

        // add ^ operator
        long calculateOutput()
        {
            std::stack<std::string> st;

            for (int i = 0; i < input.length(); ++i)
            {
                char c = input[i]; // std::cout << "c: " << c << std::endl;

                if (c == '+' || c == '-' || c == '*' || c == '/')
                {
                    long a = std::stol(st.top()); // std::cout << "a: " << a;
                    st.pop();
                    long b = std::stol(st.top()); // std::cout << "b: " << b << std::endl;
                    st.pop();

                    switch(c)
                    {
                        case '+':
                            st.push(std::to_string(b + a));
                            break;

                        case '-':
                            st.push(std::to_string(b - a));
                            break;

                        case '*':
                            st.push(std::to_string(b * a));
                            break;

                        case '/':
                            st.push(std::to_string(b / a));
                            break;
                    }
                }
                else
                {
                    st.push(std::string(1, c)); // std::cout << "pushed c: " << std::string(1, c) << std::endl;
                }
            }

            calculationDone = true;

            return std::stol(st.top());
        }
};

// add an option to use command line arguments
// int argc, char* argv[]
int main()
{
    // Use case #1 - expression comes from console
    auto calc1 = new Calculator(InputType::Console); // Input() method called automatically
    calc1->Output();

    // Use case #2 - expression comes from file
    auto calc2 = new Calculator(InputType::File, "test.in", "test.out"); // custom filenames
    calc2->Output();

    // Use case #3 - expression in a constructor
    auto calc3 = new Calculator(InputType::Constructor, "2*5-7/3+(2-1/2)"); // brackets supported
    calc3->Output();
}

#include <iostream>
#include <fstream>
#include <vector>

class Stack
{
  enum { SIZE = 100 };
  char body[SIZE];
  int head;
public:
  Stack()
  {
    head = 0;
  }
  ~Stack() {}

  void Push(char val) { body[head++] = val; }
  char Pop() { return body[--head]; }
  char Peek() { return body[head-1]; }
  bool isEmpty() { return head == 0; }
};

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
            if (InputType::Console == inputFrom)
            {
                std::getline(std::cin, input);
            }
            else if (InputType::File == inputFrom)
            {
                std::ifstream inputFile(InputFileName);

                if (inputFile.is_open())
                {
                    std::getline(inputFile, input);

                    inputFile.close();
                }
                else
                {
                    std::cout << "Can't open a file named " << InputFileName << std::endl;

                    return;
                }
            }
            else if (InputType::Constructor == inputFrom)
            {
                input = expression;
            }

            processInput();
        }

        double Output()
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
                    std::cout << "Can't read a file named " << OutputFileName << std::endl;

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
        double result;
        bool calculationDone;
        InputType inputType;
        std::string input;

        void processInput()
        {
            Stack st;
            std::string out;

            for (int i = 0; i < input.length(); ++i)
            {
                if (')' == input[i])
                {
                    while ('(' != st.Peek()) out += st.Pop();
                    st.Pop();
                }
            }

            calculationDone = true;
        }

        double calculate()
        {

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
    auto calc3 = new Calculator(InputType::Constructor, "2 * 5 - 7 / 3 + (2 - 1 / 2)"); // brackets supported
    calc3->Output();
}

#include <iostream>
#include <fstream>

class Calculator
{
    public:
        enum InputType
        {
            Console,
            File
        };

        std::string InputFileName;
        std::string OutputFileName;

        Calculator(std::string expression = "")
        {
            // Default values
            InputFileName = "Input.txt";
            OutputFileName = "Output.txt";
            result = 0;
            calculationDone = false;

            if (expression.empty()) return;

            // parse the expression, send two arguments to calculate()
        }

        void Input(InputType inputDevice)
        {
            device = inputDevice;

            if (InputType::Console == device)
            {
                // use std::cin
            }
            else
            {
                // use std::ifstream
            }

            // parse the expression, send two arguments to calculate()
        }

        void Output()
        {
            if (!calculationDone) return;

            if (InputType::Console == device)
            {
                std::cout << result << std::endl;
            }
            else
            {
                std::ofstream outputFile(OutputFileName);

                if (outputFile.is_open())
                {
                    outputFile << result << std::endl;
                }
                else std::cout << "Can't create a file named " << OutputFileName << std::endl;

                outputFile.close();
            }

            calculationDone = false;
        }

    private:
        long double result;
        bool calculationDone;
        InputType device;

        long double calculate(/*an array of digits and one consisting of operators*/)
        {
            // calculate the result

            calculationDone = true;
        }
};

// add an option to use command line arguments
// int argc, char* argv[]
int main()
{
    // Use case #1 - expression comes from console
    auto calc1 = new Calculator();
    calc1->Input(Calculator::InputType::Console);
    calc1->Output();

    // Use case #2 - expression comes from file
    auto calc2 = new Calculator();
    calc2->Input(Calculator::InputType::File);
    calc2->Output();

    // Use case #3 - expression in a constructor
    auto calc3 = new Calculator("2 * 5 - 7 / 3 + (2 - 1 / 2)");
    calc3->Output();
}

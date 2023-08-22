#include <string>
#include <vector>


using namespace std;


class ReversePolishNotation {
private:
    string mathEquation;
    vector<string> onpTokens;

    bool isOperand(string token);
    bool isArgument(string token);
    bool isOperator(string token);
    bool isFunction(string token);
    int getPrecedence(string op);
    double performOperation(string op, double operand1, double operand2);
    bool isOperandToken(string equation, size_t pos);
    bool isArgumentToken(string equation, size_t pos);
    bool isFunctionToken(string equation, size_t pos);
    bool isOperatorToken(string equation, size_t pos);
    void mathToRPN(string mathEquation);

public:
    ReversePolishNotation(string mathEquation);
    double evaluate(vector<double> *arguments);
};

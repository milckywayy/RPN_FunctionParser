#include <string>
#include <vector>


using namespace std;


class ReversePolishNotation {
private:
    string mathEquation;
    vector<string> onpTokens;

    bool isOperand(string token);
    bool isConstant(string token);
    bool isArgument(string token);
    bool isOperator(string token);
    bool isFunction(string token);
    bool isOperandToken(string equation, size_t pos);
    bool isConstantToken(string equation, size_t pos);
    bool isArgumentToken(string equation, size_t pos);
    bool isFunctionToken(string equation, size_t pos);
    bool isOperatorToken(string equation, size_t pos);
    int getPrecedence(string op);
    double getConstant(string constant);
    double performOperation(string op, double operand1, double operand2);
    double executeFunction(string fun, double arg);
    void equationToRPN(string mathEquation);

public:
    void parseEquation(string mathEquation);
    double evaluate(vector<double> *arguments = NULL);
};

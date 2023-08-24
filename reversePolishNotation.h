#ifndef REVERSE_POLISH_NOTATION_H_
#define REVERSE_POLISH_NOTATION_H_


#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


class ReversePolishNotation {
private:
    string infixEquation;
    vector<string> EquationRPN;

    // <id, idLenght>
    unordered_map<string, int> operators;
    unordered_map<string, int> constants;
    unordered_map<string, int> functions;

    bool doExist(unordered_map<string, int> map, string name);

    bool isOperand(string token);
    bool isNegativeOperand(string token);
    bool isArgument(string token);
    bool isConstant(string token);
    bool isOperator(string token);
    bool isFunction(string token);

    bool isOperandToken(string equation, size_t pos);
    bool isNegativeOperandToken(string equation, size_t pos);
    bool isArgumentToken(string equation, size_t pos);
    int isSpecialToken(string equation, size_t pos, unordered_map<string, int> map);

    int getPrecedence(string op);
    double getConstant(string constant);
    double performOperation(string op, double operand1, double operand2);
    double executeFunction(string fun, double arg);

    void infixToRPN(string infixEquation);

public:
    ReversePolishNotation();
    void parseInfix(string EquationInfix);
    void parseRPN(string EquationRPN);
    double evaluate(vector<double> *arguments = NULL);
    string getEquationInRPN();
};

#endif

#include <iostream>
#include <stack>
#include <cmath>
#include <sstream>
#include "reversePolishNotation.h"
#include "exceptions/argumentNotGiven.h"


using namespace std;


#define _USE_MATH_DEFINES 


bool ReversePolishNotation::doExist(unordered_map<string, int> map, string name) {
    return (map.find(name) != map.end());
}

bool ReversePolishNotation::isOperand(string token) {
    return (token.find_first_not_of("0123456789.") == string::npos);
}

bool ReversePolishNotation::isNegativeOperand(string token) {
    return (token.length() > 1 && token[0] == '-' && isOperand(token.substr(1, token.length() - 1)));
}

bool ReversePolishNotation::isArgument(string token) {
    if (token.length() < 2 || token[0] != 'x') {
        return false;
    }

    for (size_t i = 1; i < token.length(); ++i) {
        if (!isdigit(token[i])) {
            return false;
        }
    }

    return true;
}

bool ReversePolishNotation::isConstant(string token) {
    return doExist(constants, token);
}

bool ReversePolishNotation::isOperator(string token) {
    return doExist(operators, token);
}

bool ReversePolishNotation::isFunction(string token) {
    return doExist(functions, token);
}

bool ReversePolishNotation::isOperandToken(string equation, size_t pos) {
    return (equation[pos] >= '0' && equation[pos] <= '9') || equation[pos] == '.';
}

bool ReversePolishNotation::isNegativeOperandToken(string equation, size_t pos) {
    if (equation.length() - pos > 1) {
        return (equation[pos] == '-' && isOperandToken(equation, pos + 1));
    }
    else {
        return false;
    }
}

bool ReversePolishNotation::isArgumentToken(string equation, size_t pos) {
    if (equation.length() - pos > 1) {
        return (equation[pos] == 'x' && isOperandToken(equation, pos + 1));
    }
    else {
        return false;
    }
}

int ReversePolishNotation::isSpecialToken(string equation, size_t pos, unordered_map<string, int> map) {
    for (pair<string, int> token : map) {
        if (equation.length() - pos >= token.second) {
            if (equation.substr(pos, token.second) == token.first) {
                return token.second;
            }
        }
    }

    return 0;
}

int ReversePolishNotation::getPrecedence(string op) {
    if (op == "+" || op == "-") {
        return 1;
    }
    else if (op == "*" || op == "/") {
        return 2;
    }
    else if (op == "^") {
        return 3;
    }
    else if (op == "sin" || op == "cos" || op == "tan" || op == "abs" || op == "sqrt") {
        return 4;
    }

    return 0;
}

double ReversePolishNotation::getConstant(string constant) {
    if (constant == "_pi") {
        return M_PI;
    }
    else if (constant == "_e") {
        return M_E;
    }

    throw runtime_error("Unknown constant");
}

double ReversePolishNotation::performOperation(string op, double operand1, double operand2) {
    if (op == "+") {
        return operand1 + operand2;
    }
    else if (op == "-") {
        return operand1 - operand2;
    }
    else if (op == "*") {
        return operand1 * operand2;
    }
    else if (op == "/") {
        if (operand2 == 0) {
            throw runtime_error("Division by zero");
        }
        return operand1 / operand2;
    }
    else if (op == "^") {
        return pow(operand1, operand2);
    }

    throw runtime_error("Unknown operator");
}

double ReversePolishNotation::executeFunction(string fun, double arg) {
    if (fun == "sin") {
        return sin(arg);
    }
    else if (fun == "cos") {
        return cos(arg);
    }
    else if (fun == "tan") {
        return tan(arg);
    }
    else if (fun == "abs") {
        return fabs(arg);
    }
    else if (fun == "sqrt") {
        if (arg < 0) {
            throw runtime_error("Negative number under the square root");
        }
        return sqrt(arg);
    }

    throw runtime_error("Unknown function");
}

// Convert a regular math equation to Reverse Polish Notation (RPN)
void ReversePolishNotation::infixToRPN(string mathEquation) {
    stack<string> operatorStack; // Stack to store operators and parentheses

    size_t pos = 0; // Current position in the math equation
    size_t tokenLenght = 0;
    while (pos < mathEquation.length()) {
        // Check if the token is an operand (number)
        if (isOperandToken(mathEquation, pos) || isNegativeOperandToken(mathEquation, pos)) {
            size_t endPos = pos + 1;
            while (endPos < mathEquation.length() && isOperandToken(mathEquation, endPos)) {
                ++endPos;
            }
            // Extract the operand and add it to the RPN token list
            EquationRPN.push_back(mathEquation.substr(pos, endPos - pos));
            pos = endPos; // Move the position to the end of the operand
        }
        // Check if the token is an argument (variable x)
        else if (isArgumentToken(mathEquation, pos)) {
            size_t endPos = pos + 1;
            while (endPos < mathEquation.length() && isOperandToken(mathEquation, endPos)) {
                ++endPos;
            }

            if (endPos - pos < 2) {
                throw invalid_argument("Argument " + mathEquation.substr(pos, endPos - pos) + " has invalid format");
            }

            EquationRPN.push_back(mathEquation.substr(pos, endPos - pos));
            pos = endPos;
        }
        // Check if the token is an costant
        else if ((tokenLenght = isSpecialToken(mathEquation, pos, constants)) != 0) {
            EquationRPN.push_back(mathEquation.substr(pos, tokenLenght));
            pos += tokenLenght;
        }
        // Check if the token is a known function
        else if ((tokenLenght = isSpecialToken(mathEquation, pos, functions)) != 0) {
            operatorStack.push(mathEquation.substr(pos, tokenLenght)); // Push the function onto the operator stack
            pos += tokenLenght;
        }
        // Check if the token is an operator
        else if ((tokenLenght = isSpecialToken(mathEquation, pos, operators)) != 0) {
            while (!operatorStack.empty() && operatorStack.top() != "(" && getPrecedence(operatorStack.top()) >= getPrecedence(mathEquation.substr(pos, tokenLenght))) {
                // Pop operators from the stack with higher precedence and add them to the RPN token list
                EquationRPN.push_back(operatorStack.top());
                operatorStack.pop();
            }
            operatorStack.push(mathEquation.substr(pos, tokenLenght));
            ++pos;
        }
        // Handle opening parentheses
        else if (mathEquation[pos] == '(') {
            operatorStack.push("("); // Push the opening parenthesis onto the operator stack
            ++pos;
        }
        // Handle closing parentheses
        else if (mathEquation[pos] == ')') {
            while (!operatorStack.empty() && operatorStack.top() != "(") {
                // Pop operators from the stack until an opening parenthesis is encountered
                EquationRPN.push_back(operatorStack.top());
                operatorStack.pop();
            }
            if (!operatorStack.empty() && operatorStack.top() == "(") {
                operatorStack.pop(); // Pop the opening parenthesis from the stack
            }
            ++pos;
        }
        else if (isspace(mathEquation[pos]) || mathEquation[pos] == '\0') {
            ++pos; // Ignore white characters and \0 
        }
        else {
            // Throw exception when any unrecognized character was found
            throw invalid_argument("Invalid character entered");
        }
    }

    // Pop any remaining operators from the stack and add them to the RPN token list
    while (!operatorStack.empty()) {
        EquationRPN.push_back(operatorStack.top());
        operatorStack.pop();
    }
}

ReversePolishNotation::ReversePolishNotation() {
    // <id, idLenght>
    operators["+"] = 1;
    operators["-"] = 1;
    operators["*"] = 1;
    operators["/"] = 1;
    operators["^"] = 1;

    constants["_pi"] = 3;
    constants["_e"] = 2;

    functions["sin"] = 3;
    functions["cos"] = 3;
    functions["tan"] = 3;
    functions["abs"] = 3;
    functions["sqrt"] = 4;
}

void ReversePolishNotation::parseInfix(string EquationInfix) {
    if (EquationInfix.empty()) {
        throw invalid_argument("Empty equation");
    }

    this->infixEquation = EquationInfix;
    infixToRPN(this->infixEquation);

    try {
        evaluate(NULL);
    }
    catch (ArgumentNotGiven &e) {
    }
}

void ReversePolishNotation::parseRPN(string EquationRPN) {
    stringstream ss(EquationRPN);
    string token;

    while (ss >> token) {
        this->EquationRPN.push_back(token);
    }
}

// Evaluate the RPN expression using provided arguments
double ReversePolishNotation::evaluate(vector<double> *arguments) {
    stack<double> operands;

    for (string token : EquationRPN) {
        if (isOperand(token) || isNegativeOperand(token)) {
            operands.push(stod(token));
        }
        else if (isConstant(token)) {
            operands.push(getConstant(token));
        }
        else if (isArgument(token)) {
            size_t argIndex = atoi(token.c_str() + 1);

            if (arguments == NULL || argIndex >= arguments->size()) {
                throw ArgumentNotGiven("Argument " + token + " not given");
            }

            operands.push(arguments->at(argIndex));
        }
        else if (isOperator(token)) {
            if (operands.size() < 2) {
                // Cant perform any operation with less than 2 args
                throw invalid_argument("Invalid equation given");
            }

            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            double result = performOperation(token, operand1, operand2);
            operands.push(result);
        }
        else if (isFunction(token)) {
            if (operands.size() < 1) {
                // Cant execute any function with less than 1 args
                throw invalid_argument("Invalid equation given");
            }

            double arg = operands.top();
            operands.pop();
            double result = executeFunction(token, arg);
            operands.push(result);
        }
    }

    if (operands.empty()) {
        throw runtime_error("No result to return");
    }
    else if (operands.size() > 1) {
        throw invalid_argument("Invalid equation given");
    }

    return operands.top();
}

string ReversePolishNotation::getEquationInRPN() {
    string equation = "";

    for (string token : EquationRPN) {
        equation += token + " ";
    }

    return equation;
}

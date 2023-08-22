#include <iostream>
#include <stack>
#include <cmath>
#include "reversePolishNotation.h"


using namespace std;


bool ReversePolishNotation::isOperand(string token) {
    return (token.find_first_not_of("0123456789.") == string::npos);
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

bool ReversePolishNotation::isOperator(string token) {
    static const string operators = "+-*/^";
    return (token.length() == 1 && operators.find(token) != string::npos);
}

bool ReversePolishNotation::isFunction(string token) {
    return (token == "sin" || token == "cos" || token == "tan");
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
    else if (op == "sin" || op == "cos" || op == "tan") {
        return 4;
    }
    return 0;
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
    else if (op == "sin") {
        return sin(operand1);
    }
    else if (op == "cos") {
        return cos(operand1);
    }
    else if (op == "tan") {
        return tan(operand1);
    }

    throw runtime_error("Unknown operator or function");
}

// Convert a regular math equation to Reverse Polish Notation (RPN)
void ReversePolishNotation::equationToRPN(string mathEquation) {
    stack<string> operators; // Stack to store operators and parentheses

    size_t pos = 0; // Current position in the math equation
    while (pos < mathEquation.length()) {
        // Check if the token is an operand (number)
        if (isOperandToken(mathEquation, pos)) {
            size_t endPos = pos + 1;
            while (endPos < mathEquation.length() && isOperandToken(mathEquation, endPos)) {
                ++endPos;
            }
            // Extract the operand and add it to the RPN token list
            onpTokens.push_back(mathEquation.substr(pos, endPos - pos));
            pos = endPos; // Move the position to the end of the operand
        }
        // Check if the token is an argument (variable x)
        else if (isArgumentToken(mathEquation, pos)) {
            size_t endPos = pos + 1;
            while (endPos < mathEquation.length() && isOperandToken(mathEquation, endPos)) {
                ++endPos;
            }
            onpTokens.push_back(mathEquation.substr(pos, endPos - pos));
            pos = endPos;
        }
        // Check if the token is a known function (sin, cos, tan)
        else if (isFunctionToken(mathEquation, pos)) {
            operators.push(mathEquation.substr(pos, 3)); // Push the function onto the operator stack
            pos += 3;
        }
        // Check if the token is an operator (+, -, *, /, ^)
        else if (isOperatorToken(mathEquation, pos)) {
            while (!operators.empty() && operators.top() != "(" && getPrecedence(operators.top()) >= getPrecedence(mathEquation.substr(pos, 1))) {
                // Pop operators from the stack with higher precedence and add them to the RPN token list
                onpTokens.push_back(operators.top());
                operators.pop();
            }
            operators.push(mathEquation.substr(pos, 1));
            ++pos;
        }
        // Handle opening parentheses
        else if (mathEquation[pos] == '(') {
            operators.push("("); // Push the opening parenthesis onto the operator stack
            ++pos;
        }
        // Handle closing parentheses
        else if (mathEquation[pos] == ')') {
            while (!operators.empty() && operators.top() != "(") {
                // Pop operators from the stack until an opening parenthesis is encountered
                onpTokens.push_back(operators.top());
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop(); // Pop the opening parenthesis from the stack
            }
            ++pos;
        }
        else {
            ++pos; // Ignore spaces and other unrecognized characters
        }
    }

    // Pop any remaining operators from the stack and add them to the RPN token list
    while (!operators.empty()) {
        onpTokens.push_back(operators.top());
        operators.pop();
    }
}

bool ReversePolishNotation::isOperandToken(string equation, size_t pos) {
    return (equation[pos] >= '0' && equation[pos] <= '9') || equation[pos] == '.';
}

bool ReversePolishNotation::isArgumentToken(string equation, size_t pos) {
    return (equation[pos] == 'x');
}

bool ReversePolishNotation::isFunctionToken(string equation, size_t pos) {
    return (equation.substr(pos, 3) == "sin" || equation.substr(pos, 3) == "cos" || equation.substr(pos, 3) == "tan");
}

bool ReversePolishNotation::isOperatorToken(string equation, size_t pos) {
    return equation[pos] == '+' || equation[pos] == '-' || equation[pos] == '*' || equation[pos] == '/' || equation[pos] == '^';
}

ReversePolishNotation::ReversePolishNotation(string mathEquation) {
    if (mathEquation.empty()) {
        throw invalid_argument("Empty equation");
    }

    this->mathEquation = mathEquation;
    equationToRPN(this->mathEquation);
}

// Evaluate the RPN expression using provided arguments
double ReversePolishNotation::evaluate(vector<double> *arguments) {
    stack<double> operands;

    for (string token : onpTokens) {
        if (isOperand(token)) {
            operands.push(stod(token));
        }
        else if (isArgument(token)) {
            size_t argIndex = atoi(token.c_str() + 1);

            if (argIndex >= arguments->size()) {
                throw out_of_range("Argument index out of range");
            }

            operands.push(arguments->at(argIndex));
        }
        else if (isOperator(token)) {
            double operand2 = operands.top();
            operands.pop();
            double operand1 = operands.top();
            operands.pop();
            double result = performOperation(token, operand1, operand2);
            operands.push(result);
        }
        else if (isFunction(token)) {
            double operand1 = operands.top();
            operands.pop();
            // 0 because functions take only one argument
            double result = performOperation(token, operand1, 0);
            operands.push(result);
        }
    }

    if (operands.empty()) {
        throw runtime_error("No result to return");
    }

    return operands.top();
}

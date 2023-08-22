#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <cmath>
#include <map>


using namespace std;


class ReversePolishNotation {
private:
    string mathEquation;
    vector<string> onpTokens;

    bool isOperand(string token) {
        return (token.find_first_not_of("0123456789.") == string::npos);
    }

    bool isOperator(string token) {
        static const string operators = "+-*/^";
        return (token.length() == 1 && operators.find(token) != string::npos);
    }

    bool isFunction(string token) {
        return (token == "sin" || token == "cos" || token == "tan");
    }

    int getPrecedence(string op) {
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

    double performOperation(string op, double operand1, double operand2) {
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

        return 0.0;
    }

    void mathToRPN(string mathEquation) {
        stack<string> operators;

        size_t pos = 0;
        while (pos < mathEquation.length()) {
            if (isOperandToken(mathEquation, pos)) {
                size_t endPos = pos + 1;
                while (endPos < mathEquation.length() && isOperandToken(mathEquation, endPos)) {
                    ++endPos;
                }

                onpTokens.push_back(mathEquation.substr(pos, endPos - pos));
                pos = endPos;
            }
            else if (isFunctionToken(mathEquation, pos)) {
                operators.push(mathEquation.substr(pos, 3));
                pos += 3;
            }
            else if (isOperatorToken(mathEquation, pos)) {
                while (!operators.empty() && operators.top() != "(" && getPrecedence(operators.top()) >= getPrecedence(mathEquation.substr(pos, 1))) {
                    onpTokens.push_back(operators.top());
                    operators.pop();
                }

                operators.push(mathEquation.substr(pos, 1));
                ++pos;
            }
            else if (mathEquation[pos] == '(') {
                operators.push("(");
                ++pos;
            }
            else if (mathEquation[pos] == ')') {
                while (!operators.empty() && operators.top() != "(") {
                    onpTokens.push_back(operators.top());
                    operators.pop();
                }

                if (!operators.empty() && operators.top() == "(") {
                    operators.pop();
                }
                ++pos;
            }
            else {
                ++pos;
            }
        }

        while (!operators.empty()) {
            onpTokens.push_back(operators.top());
            operators.pop();
        }
    }

    bool isOperandToken(string equation, size_t pos) {
        return (equation[pos] >= '0' && equation[pos] <= '9') || equation[pos] == '.';
    }

    bool isFunctionToken(string equation, size_t pos) {
        return (equation.substr(pos, 3) == "sin" || equation.substr(pos, 3) == "cos" || equation.substr(pos, 3) == "tan");
    }

    bool isOperatorToken(string equation, size_t pos) {
        return equation[pos] == '+' || equation[pos] == '-' || equation[pos] == '*' || equation[pos] == '/' || equation[pos] == '^';
    }

public:
    ReversePolishNotation(string mathEquation) {
        this->mathEquation = mathEquation;
        mathToRPN(this->mathEquation);
    }

    double evaluate() {
        stack<double> operands;

        for (string token : onpTokens) {
            cout << token << endl;
            if (isOperand(token)) {
                operands.push(stod(token));
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

                double result = performOperation(token, operand1, 0);
                operands.push(result);
            }
        }

        return operands.top();
    }
};

int main() {
    string mathEquation = "4^2 - cos(0)";
    ReversePolishNotation calculator(mathEquation);
    double result = calculator.evaluate();
    cout << "Result: " << result << endl;

    return 0;
}

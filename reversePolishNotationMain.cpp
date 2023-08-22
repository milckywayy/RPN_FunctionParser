#include <iostream>
#include <string>
#include <vector>
#include "reversePolishNotation.h"


using namespace std;


// Test case
int main(int argc, char **argv) {
    vector<double> args;
    args.push_back(1);
    args.push_back(3);
    args.push_back(2);

    string mathEquation = "(x0 * x1) + x2 ^ 2";

    ReversePolishNotation calculator(mathEquation);

    double result = calculator.evaluate(&args);
    cout << "Result: " << result << endl;

    return 0;
}
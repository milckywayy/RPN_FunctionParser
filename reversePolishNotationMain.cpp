#include <iostream>
#include <string>
#include <vector>
#include "reversePolishNotation.h"


using namespace std;


void help() {
    cout << " ============ RPN Function parser ============ " << endl << endl;
    cout << "Usage: ./main.exe " << '"' << "math_equation" << '"' << " x0 x1 x2 ..." << endl;
    cout << "\t- math_equation: Mathematical equation in postfix notation" << endl;
    cout << "\t- args: Numbers to be used in the equation" << endl << endl;
    cout << "Program supports:" << endl;
    cout << "\t- constants: _pi = ~3.14, _e = ~2.72" << endl;
    cout << "\t- functions: sin(x), cos(x), tan(x), abs(x), sqrt(x)" << endl;
    cout << "\t- arguments: x0, x1, x2 ..." << endl << endl;
    cout << "Example: ./main.exe " << '"' << "(sin( _pi/2 ) * x0) + x1" << '"' << " 2 3 (Result = 5)" << endl;
}

int main(int argc, char **argv) {
    vector<double> args;
    string mathEquation;
    ReversePolishNotation calculator;
    double result;

    for (int i = 1; i < argc; i++) {
        string arg = argv[i];
        if (arg == "-h" || arg == "--help" || arg == "/h" || arg == "/help") {
            help();
            return 0;
        }
    }

    if (argc < 2) {
        help();
        return 0;
    }
    if (argc > 1) {
        mathEquation = argv[1];
    }
    else {
        cerr << "Error: No equation given" << endl << endl;
        help();
        return 1;
    }

    for (int i = 2; i < argc; i++) {
        args.push_back(stod(argv[i]));
    }

    try {
        calculator.parseEquation(mathEquation);
    }
    catch (exception &e) {
        cerr << "Error: " << e.what() << endl << endl;
        help();
        return 2;
    }

    result = calculator.evaluate(&args);
    cout << "Result: " << result << endl;

    return 0;
}
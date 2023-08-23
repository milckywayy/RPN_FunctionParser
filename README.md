# RPN_FunctionParser
C++ implementation of a reverse polish notation (RPN) calculator. It allows you to convert regular mathematical equations/functions into their RPN equivalent and then evaluate them with provided variables (arguments).

## Features:
- Conversion to RPN: Program converts a regular mathematical expression into its RPN equivalent. This conversion process is fundamental for efficient evaluation using a stack-based approach.
- Support for Functions: The program supports common trigonometric functions (sin, cos, tan) alongside basic arithmetic operations. This expands its usability for a wider range of mathematical calculations.
- Dynamic Argument Evaluation: The program allows you to provide arguments for variables (arguments) in the equation. This dynamic evaluation of arguments makes it versatile for solving equations with varying input values.

## Usage:
- Equation Parsing: Start by creating an instance of the ReversePolishNotation class. Use the parseEquation() method to parse and tokenize the given mathematical equation. This step prepares the equation for evaluation.
- Argument Input (Optional): If your equation contains variables (arguments), you can provide their values using a vector<double>. This is useful for evaluating equations with dynamic inputs.
- Evaluation: The evaluate() method performs the actual evaluation of the RPN tokens. It takes care of applying operators, functions, and handling exceptions.

The program supports following:
- Constants: `_pi = ~3.14`, `_e = ~2.72`
- Functions: `sin(x)`, `cos(x)`, `tan(x)`
- Arguments: `x0`, `x1`, `x2`, ...

## Example:
### Example equations/functions:
-     "(1 + 2)^3 + 1"
-     "(x0 - -1) / _e"
-     "(sin( _pi/2 ) * x0) + x1"

### Example C++ code:
    #include <iostream>
    #include "reversePolishNotation.h"
    
    int main() {
      ReversePolishNotation calculator;
      std::string equation = "2 * (3 + sin(x0))";
      calculator.parseEquation(equation);
    
      std::vector<double> arguments = {1.0}; // Provide argument values
      try {
          double result = calculator.evaluate(&arguments);
          std::cout << "Result: " << result << std::endl;
      } catch (std::exception& e) {
          std::cout << "Error: " << e.what() << std::endl;
      }

      return 0;
    }


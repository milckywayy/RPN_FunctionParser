../build/main.exe: main.cpp reversePolishNotation.h reversePolishNotation.cpp exceptions/argumentNotGiven.h
	g++ -o ../build/main.exe main.cpp reversePolishNotation.h reversePolishNotation.cpp exceptions/argumentNotGiven.h

test:
	../build/main.exe "(x0 + 1) * 5" 1

linux:
	g++ -shared -o ../build/math_parser.so -fPIC reversePolishNotation.h reversePolishNotation.cpp exceptions/argumentNotGiven.h

windows:
	g++ -shared -o ../build/math_parser.dll reversePolishNotation.h reversePolishNotation.cpp exceptions/argumentNotGiven.h

clean:
	rm ../build/*
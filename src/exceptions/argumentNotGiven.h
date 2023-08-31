#ifndef ARGUMENT_NOT_GIVEN_H_   
#define ARGUMENT_NOT_GIVEN_H_  


#include <string>
#include <exception>


class ArgumentNotGiven : public std::exception {
private:
    std::string message;
public:
    ArgumentNotGiven(const std::string& msg) : message(msg) {}
    const char* what() const throw() {
        return message.c_str();
    }
};

#endif 

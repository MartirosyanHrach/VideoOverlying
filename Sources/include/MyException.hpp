#ifndef MY_EXCEPTION
#define MY_EXCEPTION

#include <string>
#include <exception>

class MyException : public std::exception {
public:
    MyException(const std::string& message) : m_message(message) {}
    MyException(const std::string& helperMessage, const std::string& message) : 
        m_message(helperMessage + " " + message) {}

    const char* what() const throw() {
        return (m_message).c_str(); 
    }
private:
    std::string m_message;
};

#endif //MY_EXCEPTION
#pragma once
#include <map>

class ErrorHandler {
public:
    enum ErrorCodes {
        UNKNOWN_ERROR,
        FILE_NOT_FOUND
    };

    ErrorHandler ();
    ~ErrorHandler ();

    std::string getErrorMessage (const ErrorCodes errorCode);

private:
    std::map<ErrorCodes, std::string> mErrorMessages;
};


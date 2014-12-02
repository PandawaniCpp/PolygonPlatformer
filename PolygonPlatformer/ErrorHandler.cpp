#include "ErrorHandler.h"

ErrorHandler::ErrorHandler () {
    mErrorMessages.insert (std::make_pair (ErrorCodes::UNKNOWN_ERROR, "Nieznany b³¹d."));
    mErrorMessages.insert (std::make_pair (ErrorCodes::FILE_NOT_FOUND, "Nie znaleziono pliku."));
}

ErrorHandler::~ErrorHandler () {
}

std::string ErrorHandler::getErrorMessage (const ErrorCodes code) {
    if (mErrorMessages.find (code) != mErrorMessages.end ())
        return mErrorMessages[code];
    else
        return mErrorMessages[ErrorCodes::UNKNOWN_ERROR];
}

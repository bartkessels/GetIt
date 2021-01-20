#pragma once

#include <exception>

namespace getit::domain::exception
{
    struct MethodRequiredException: public std::exception
    {
        const char* what() const throw()
        {
            return "The http method can't be null or empty";
        }
    };
}
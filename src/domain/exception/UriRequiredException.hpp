#pragma once

#include <exception>

namespace getit::domain::exception
{
    struct UriRequiredException: public std::exception
    {
        const char* what() const throw()
        {
            return "The uri can't be null or empty";
        }
    };
}
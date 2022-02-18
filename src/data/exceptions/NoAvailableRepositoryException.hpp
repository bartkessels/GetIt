#pragma once

#include <exception>

namespace getit::data::exceptions
{
    struct NoAvailableRepositoryException: public std::exception
    {
        public:
            const char* what() const throw()
            {
                return "Cannot find a repository for the specified class";
            }
    };
}
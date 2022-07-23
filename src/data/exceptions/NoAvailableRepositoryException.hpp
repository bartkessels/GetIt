#pragma once

#include <exception>

namespace getit::data::exceptions
{
    struct NoAvailableRepositoryException: public std::exception
    {
        public:
            [[nodiscard]] const char* what() const noexcept override
            {
                return message;
            }

            inline static const char* message = "Cannot find a repository for the specified class";
    };
}
#pragma once

#include <string>

#include "presentation/states/RequestState.hpp"

namespace getit::presentation::states
{
    struct Error: public RequestState
    {
        public:
            explicit Error(std::string message): message(std::move(message)) {}
            ~Error() override = default;

            std::string message;
    };
}
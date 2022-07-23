#pragma once

#include "presentation/states/RequestState.hpp"

namespace getit::presentation::states
{
    struct Sending: public RequestState
    {
        public:
            ~Sending() override = default;
    };
}
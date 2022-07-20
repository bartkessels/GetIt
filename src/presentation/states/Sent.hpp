#pragma once

#include <memory>

#include "domain/models/Response.hpp"
#include "presentation/states/RequestState.hpp"

namespace getit::presentation::states
{
    struct Sent: public RequestState
    {
        public:
            explicit Sent(std::shared_ptr<domain::models::Response> response): response(std::move(response)) {}
            ~Sent() override = default;

            std::shared_ptr<getit::domain::models::Response> response;
    };
}
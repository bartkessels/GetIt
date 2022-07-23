#pragma once

#include <memory>
#include <utility>

#include "domain/models/Request.hpp"
#include "presentation/states/RequestState.hpp"

namespace getit::presentation::states
{
    struct FileOpened: public RequestState
    {
        public:
            explicit FileOpened(std::shared_ptr<getit::domain::models::Request>  request):
                request(std::move(request)) {}
            ~FileOpened() override = default;

            std::shared_ptr<getit::domain::models::Request> request;
    };
}
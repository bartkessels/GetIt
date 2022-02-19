#pragma once

#include <memory>
#include <string>

#include "domain/models/RequestBody.hpp"

namespace getit::presentation::fragments
{
    struct BodyFragmentModel
    {
        public:
            std::shared_ptr<domain::models::RequestBody> body;
    };
}
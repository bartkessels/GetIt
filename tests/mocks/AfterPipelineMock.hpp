#pragma once

#include <memory>
#include <trompeloeil.hpp>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/RequestData.hpp"

namespace getit::tests::mocks
{
    class AfterPipelineMock: public getit::domain::AfterRequestPipeline
    {
        public:
            MAKE_MOCK1(executeAfterRequest, void(std::shared_ptr<getit::domain::Response>), override);
    };
}

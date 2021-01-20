#pragma once

#include <memory>
#include <trompeloeil.hpp>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"

namespace getit::tests::mocks
{
    class BeforePipelineMock: public getit::domain::BeforeRequestPipeline
    {
        public:
            MAKE_MOCK1(executeBeforeRequest, void(std::shared_ptr<getit::domain::RequestData>), override);
    };
}

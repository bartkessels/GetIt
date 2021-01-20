#pragma once

#include <list>
#include <memory>
#include <string>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"
#include "domain/Response.hpp"

namespace getit::domain
{
    class Request
    {
        public:
            Request() = default;
            ~Request() = default;
            
            void registerPipeline(std::shared_ptr<BeforeRequestPipeline> beforePipeline);
            void registerPipeline(std::shared_ptr<AfterRequestPipeline> afterPipeline);
            void send();

        protected:
            virtual std::shared_ptr<Response> sendRequest(std::shared_ptr<RequestData> data) = 0;

        private:
            std::list<std::shared_ptr<BeforeRequestPipeline>> beforePipelines;
            std::list<std::shared_ptr<AfterRequestPipeline>> afterPipelines;
    };
}

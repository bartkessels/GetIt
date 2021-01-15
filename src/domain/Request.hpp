#pragma once

#include <list>
#include <memory>
#include <string>

#include "domain/RequestData.hpp"
#include "domain/RequestPipeline.hpp"
#include "domain/Response.hpp"

namespace getit::domain
{
    class Request
    {
        public:
            Request() = default;
            ~Request() = default;
            
            void registerPipeline(std::shared_ptr<RequestPipeline> pipeline);
            void send();

        protected:
            virtual std::shared_ptr<Response> sendRequest(std::shared_ptr<RequestData> data) = 0;

        private:
            std::list<std::shared_ptr<RequestPipeline>> pipelines;
    };
}

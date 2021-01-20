#pragma once

#include <memory>

#include "domain/RequestData.hpp"

namespace getit::domain
{
    struct BeforeRequestPipeline
    {
        public:
            virtual ~BeforeRequestPipeline() = default;

            /**
             * @brief Modify the RequestData before the request is sent
             * 
             * @param data this data will be sent to the request client
             * @return void
             */
            virtual void executeBeforeRequest(std::shared_ptr<RequestData> data) = 0;
    };
}
#pragma once

#include <memory>
#include <string>

#include "domain/BeforeRequestPipeline.hpp"

namespace getit::domain::pipelines
{
    class MethodPipeline: public BeforeRequestPipeline
    {
        public:
            explicit MethodPipeline(std::string httpMethod);
            ~MethodPipeline() = default;
    
            /**
             * @brief Sets the http method on the RequestData
             * 
             * @param data the RequestData on which the http method is set
             * @return void
             */
            void executeBeforeRequest(std::shared_ptr<RequestData> data) override;

        private:
            std::string httpMethod;
    };
}
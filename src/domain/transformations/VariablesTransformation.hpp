#pragma once

#include <memory>
#include <list>

#include "domain/contracts/Transformation.hpp"
#include "domain/implementations/FormDataRequestBody.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Variable.hpp"

namespace getit::domain::transformations
{
    class VariablesTransformation : public contracts::Transformation
    {
        public:
            explicit VariablesTransformation(std::list<std::shared_ptr<models::Variable>>   variables);
            ~VariablesTransformation() override = default;

            std::shared_ptr<domain::models::Request> transform(std::shared_ptr<domain::models::Request> request) override;

        private:
            std::list<std::shared_ptr<models::Variable>> variables;

            static std::shared_ptr<models::Request> transformUri(std::shared_ptr<models::Request> request, const std::shared_ptr<models::Variable>& variable);
            static std::shared_ptr<models::Request> transformHeaders(std::shared_ptr<models::Request> request, const std::shared_ptr<models::Variable>& variable);
            static std::shared_ptr<models::Request> transformBody(const std::shared_ptr<models::Request>& request, const std::shared_ptr<models::Variable>& variable);
            static std::shared_ptr<implementations::FormDataRequestBody> transformFormdataBody(std::shared_ptr<implementations::FormDataRequestBody> body, const std::shared_ptr<models::Variable>& variable);
            static std::shared_ptr<implementations::RawRequestBody> transformRawRequestBody(std::shared_ptr<implementations::RawRequestBody> body, const std::shared_ptr<models::Variable>& variable);

            static std::pair<std::string, std::string> transformPair(const std::pair<std::string, std::string>& pair, const std::shared_ptr<models::Variable>& variable);
    };
}
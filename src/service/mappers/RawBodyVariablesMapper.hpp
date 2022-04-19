#pragma once

#include <memory>
#include <string>
#include <tuple>

#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Variables.hpp"

#include "service/mappers/VariablesMapper.hpp"

using namespace getit::domain::implementations;

namespace getit::service::mappers
{
    class RawBodyVariablesMapper : public VariablesMapper
    {
        public:
            ~RawBodyVariablesMapper() override = default;

        protected:
            void mapBody(const std::tuple<std::string, std::string>& variable) override;

        private:
            const std::shared_ptr<RawRequestBody>& mapElements(const std::shared_ptr<RawRequestBody>& body, const std::tuple<std::string, std::string>& variable);
            const std::shared_ptr<RawRequestBody>& mapFiles(const std::shared_ptr<RawRequestBody>& body, const std::tuple<std::string, std::string>& variable);
    };
}
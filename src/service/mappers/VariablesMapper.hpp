#pragma once

#include <boost/algorithm/string/replace.hpp>
#include <boost/format.hpp>
#include <memory>
#include <string>
#include <tuple>

#include "domain/models/Request.hpp"
#include "domain/models/Variables.hpp"

#include "service/contracts/VariablesMapper.hpp"

using namespace getit::domain;

namespace getit::service::mappers
{
    class VariablesMapper : public contracts::VariablesMapper
    {
        public:
            ~VariablesMapper() override = default;

            std::shared_ptr<models::Request> map(std::shared_ptr<models::Request> request, std::shared_ptr<models::Variables> variables) override;

        protected:
            std::shared_ptr<models::Request> request;
            std::shared_ptr<models::Variables> variables;

            virtual void mapBody(const std::tuple<std::string, std::string>& variable) = 0;

            static std::string replaceVariable(std::string input, const std::tuple<std::string, std::string>& variable);

        private:
            void mapUri(const std::tuple<std::string, std::string>& variable);
            void mapHeaders(const std::tuple<std::string, std::string>& variable);
    };
}
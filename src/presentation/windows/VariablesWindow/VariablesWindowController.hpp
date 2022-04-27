#pragma once

#include <map>
#include <memory>
#include <string>

#include "domain/models/Variable.hpp"
#include "presentation/windows/VariablesWindow/IVariablesWindowView.hpp"

namespace getit::presentation::windows
{
    class VariablesWindowController
    {
        public:
            explicit VariablesWindowController(IVariablesWindowView* view);
            ~VariablesWindowController();

            std::list<std::string> getCollections();
            std::list<std::shared_ptr<Variable>> getVariables(const std::string& collection);
            std::map<std::string, std::list<std::shared_ptr<Variable>>> getVariables();

            void setVariables(const std::string& collection);
            void setVariables(std::map<std::string, std::list<std::shared_ptr<Variable>>> variables);

        private:
            IVariablesWindowView *view;
    };
}
#include "presentation/windows/VariablesWindow/VariablesWindowController.hpp"

using namespace getit::presentation::windows;

VariablesWindowController::VariablesWindowController(IVariablesWindowView* view):
    view(view)
{

}

VariablesWindowController::~VariablesWindowController()
{
    delete view;
}

std::list<std::string> VariablesWindowController::getCollections()
{
    std::list<std::string> keys;

    for (const auto& [key, _] : getVariables()) {
        keys.push_back(key);
    }

    return keys;
}

std::list<std::shared_ptr<Variable>> VariablesWindowController::getVariables(const std::string& collection)
{
    auto iterator = getVariables().find(collection);

    if (iterator != getVariables().end())
        return iterator->second;

    return {};
}


std::map<std::string, std::list<std::shared_ptr<Variable>>> VariablesWindowController::getVariables()
{
    return view->getVariables();
}

void VariablesWindowController::setVariables(const std::string& collection)
{

}


//void setVariables(std::string collection);
//void setVariables(std::map<std::string, std::list<std::shared_ptr<Variable>>> variables);
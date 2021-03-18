#include "gui/widget/BodyWidget/FormdataBodyTab/FormdataBodyTabController.hpp"

using namespace getit::gui::widget::BodyWidget;

FormdataBodyTabController::FormdataBodyTabController(std::shared_ptr<IFormdataBodyTabView> view):
    view(view)
{

}

void FormdataBodyTabController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    std::map<std::string, std::string> elements = view->getElements();
    std::map<std::string, std::string> files = view->getFiles();
    const auto& currentTime = std::time(nullptr);
    auto boundary = std::to_string(currentTime);

    auto requestBody = std::make_shared<getit::domain::body::FormdataRequestBody>(boundary);

    for (const auto& [element, value] : view->getElements()) {
        requestBody->addElement(element, value);
    }

    for (const auto& [file, value] : view->getFiles()) {
        requestBody->addFile(file, value);
    }


    data->setBody(requestBody);
}
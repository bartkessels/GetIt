#include "gui/widget/ResponseBodyWidget/ResponseBodyController.hpp"

using namespace getit::gui::widget;

ResponseBodyController::ResponseBodyController(std::shared_ptr<IResponseBodyView> view):
    view(view)
{

}

void ResponseBodyController::registerTab(std::shared_ptr<getit::domain::AfterRequestPipeline> controller, std::shared_ptr<QWidget> tab, std::string name)
{
    this->tabControllers.push_back(controller);
    view->addResponseBodyTab(tab.get(), name);
}

void ResponseBodyController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    for (const auto& tab : this->tabControllers) {
        tab->executeAfterRequest(response);
    }
}
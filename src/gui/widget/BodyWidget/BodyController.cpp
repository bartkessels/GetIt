#include "gui/widget/BodyWidget/BodyController.hpp"

using namespace getit::gui::widget;

BodyController::BodyController(std::shared_ptr<IBodyView> view):
    view(view)
{

}

void BodyController::registerTab(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> tab, std::string name)
{
    this->tabControllers.push_back(controller);
    view->addBodyTab(tab.get(), name);
}

void BodyController::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    int currentTabIndex = view->getSelectedTabIndex();
    auto body = tabControllers.at(currentTabIndex);

    body->executeBeforeRequest(data);
}
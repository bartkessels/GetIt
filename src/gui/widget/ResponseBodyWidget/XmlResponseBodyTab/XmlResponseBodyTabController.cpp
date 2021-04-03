#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/XmlResponseBodyTabController.hpp"

using namespace getit::gui::widget::ResponseBodyWidget;

XmlResponseBodyTabController::XmlResponseBodyTabController(std::shared_ptr<IXmlResponseBodyTabView> view):
    view(view)
{

}

void XmlResponseBodyTabController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    view->setBody(response->body);
}
#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/RawResponseBodyTabController.hpp"

using namespace getit::gui::widget::ResponseBodyWidget;

RawResponseBodyTabController::RawResponseBodyTabController(std::shared_ptr<IRawResponseBodyTabView> view):
    view(view)
{

}

void RawResponseBodyTabController::executeAfterRequest(std::shared_ptr<getit::domain::Response> response)
{
    view->setBody(response->body);
}

///Users/bkessels/Git-projects/X-platform/GetIt/src/gui/widget/ResponseBodyWidget/RawResponseBodyTabView/RawResponseBodyTabView.ui
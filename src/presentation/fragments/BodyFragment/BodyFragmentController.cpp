#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"

using namespace getit;
using namespace getit::presentation::fragments;

BodyFragmentController::BodyFragmentController(BodyFragmentView* view):
    view(view)
{

}

BodyFragmentController::~BodyFragmentController()
{
    delete this->view;
}

std::shared_ptr<domain::models::RequestBody> BodyFragmentController::getContent()
{
    return view->getBody();
}

void BodyFragmentController::setContent(std::shared_ptr<domain::models::RequestBody> content)
{
    view->setBody(content);
}
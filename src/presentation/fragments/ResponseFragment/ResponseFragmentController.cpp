#include "presentation/fragments/ResponseFragment/ResponseFragmentController.hpp"

using namespace getit;
using namespace getit::presentation::fragments;

ResponseFragmentController::ResponseFragmentController(IResponseFragmentView* view):
    view(view)
{

};

ResponseFragmentController::~ResponseFragmentController()
{
    delete view;
}

std::shared_ptr<domain::models::Response> ResponseFragmentController::getContent()
{
    const auto& content = std::make_shared<domain::models::Response>();

    content->headers = view->getHeaders();
    content->body = view->getBody();

    return content;
}

void ResponseFragmentController::setContent(std::shared_ptr<domain::models::Response> content)
{
    view->clearHeaders();
    view->setHeaders(content->headers);
    view->setBody(content->body);
}
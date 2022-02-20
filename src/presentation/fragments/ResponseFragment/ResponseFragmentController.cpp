#include "presentation/fragments/ResponseFragment/ResponseFragmentController.hpp"

using namespace getit::presentation::fragments;

ResponseFragmentController::ResponseFragmentController(ResponseFragmentView* view):
    view(view)
{

};

ResponseFragmentController::~ResponseFragmentController()
{
    delete view;
}

std::shared_ptr<ResponseFragmentModel> ResponseFragmentController::getContent()
{
    const auto& content = std::make_shared<ResponseFragmentModel>();

    content->headers = view->getHeaders();
    content->body = view->getBody();

    return content;
}

void ResponseFragmentController::setContent(std::shared_ptr<ResponseFragmentModel> content)
{
    view->setHeaders(content->headers);
    view->setBody(content->body);
}
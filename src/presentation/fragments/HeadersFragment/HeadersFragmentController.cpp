#include "presentation/fragments/HeadersFragment/HeadersFragmentController.hpp"

using namespace getit::presentation::fragments;

HeadersFragmentController::HeadersFragmentController(HeadersFragmentView* view):
    view(view)
{

}

HeadersFragmentController::~HeadersFragmentController()
{
    delete this->view;
}

std::map<std::string, std::string> HeadersFragmentController::getContent()
{
    return view->getHeaders();
}

void HeadersFragmentController::setContent(std::map<std::string, std::string> content)
{
    view->setHeaders(content);
}
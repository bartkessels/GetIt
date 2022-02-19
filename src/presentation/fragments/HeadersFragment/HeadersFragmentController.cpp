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

std::shared_ptr<HeadersFragmentModel> HeadersFragmentController::getContent()
{
    const auto& model = std::make_shared<HeadersFragmentModel>();
    return model;
}

void HeadersFragmentController::setContent(std::shared_ptr<HeadersFragmentModel> content)
{

}
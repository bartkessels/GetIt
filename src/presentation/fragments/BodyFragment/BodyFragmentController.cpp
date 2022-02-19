#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"

using namespace getit::presentation::fragments;

BodyFragmentController::BodyFragmentController(BodyFragmentView* view):
    view(view)
{

}

BodyFragmentController::~BodyFragmentController()
{
    delete this->view;
}

std::shared_ptr<BodyFragmentModel> BodyFragmentController::getContent()
{
    const auto& model = std::make_shared<BodyFragmentModel>();

    return model;
}

void BodyFragmentController::setContent(std::shared_ptr<BodyFragmentModel> content)
{

}
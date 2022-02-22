#include "presentation/fragments/BodyFragment/BodyFragmentController.hpp"

using namespace getit;
using namespace getit::presentation::fragments;

BodyFragmentController::BodyFragmentController(IBodyFragmentView* view):
    view(view)
{

}

BodyFragmentController::~BodyFragmentController()
{
    delete this->view;
}

std::shared_ptr<domain::models::RequestBody> BodyFragmentController::getContent()
{
    switch(view->getBodyType())
    {
        case BodyType::FORM_DATA:
            return view->getFormDataBody();
        case BodyType::RAW:
            return view->getRawBody();
    }
    
    return nullptr;
}

void BodyFragmentController::setContent(std::shared_ptr<domain::models::RequestBody> content)
{
    if (const auto& formData = std::dynamic_pointer_cast<domain::implementations::FormDataRequestBody>(content)) {
        view->setFormDataBody(formData);
    } else if (const auto& raw = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(content)) {
        view->setRawBody(raw);
    }
}

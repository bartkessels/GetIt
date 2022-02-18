#include "presentation/tabs/RawRequestTab/RawRequestTabController.hpp"

using namespace getit::presentation::tabs;

RawRequestTabController::RawRequestTabController(std::shared_ptr<RawRequestTabView> view, std::shared_ptr<domain::factories::RequestFactory> requestFactory):
    view(view),
    requestFactory(requestFactory)
{

}

void RawRequestTabController::setRequest(std::shared_ptr<getit::domain::models::Request> request)
{
    const auto& entity = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request);

    // view->setMethod(entity->getMethod());
    // view->setUri(entity->getUri());
    // view->setContentType(entity->getContentType());
    // view->setBody(entity->getBody());
}

void RawRequestTabController::setResponse(std::shared_ptr<getit::domain::models::Response> response)
{
    // view->setResponseHeaders(response->headers);
    // view->setResponseBody(response->body);
}

std::shared_ptr<getit::domain::models::Request> RawRequestTabController::getRequest()
{
    // const auto& contentType = view->getContentType();
    // const auto& body = view->getBody();
    // const auto& request = requestFactory->getRequest(body, contentType);
    // const auto& entity = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request);

    // entity->setMethod(view->getMethod());
    // entity->setUri(view->getUri());

    // return entity;
}
#include "service/implementations/CppRestRequestService.hpp"

using namespace getit::service::implementations;

std::future<std::shared_ptr<getit::domain::models::Response>> CppRestRequestService::send(std::shared_ptr<getit::domain::models::Request> request)
{
    const auto& cppRequest = std::make_shared<web::http::http_request>(request->getMethod());
    const auto& client = std::make_shared<web::http::client::http_client>(request->getUri());

    for (const auto& [header, value] : request->getHeaders()) {
        cppRequest->headers().add(header, value);
    }

    if (request->getBody() != nullptr)
        cppRequest->set_body(
            request->getBody()->getBody(),
            request->getBody()->getContentType()
        );

    return std::async(std::launch::async, [client, cppRequest]() {
        const auto& rawResponse = client->request(*cppRequest).get();
        const auto& response = std::make_shared<getit::domain::models::Response>();
        bool ignoreContentType = true;

        response->body = rawResponse.extract_string(ignoreContentType).get();

        for (auto [header, value] : rawResponse.headers()) {
            response->headers.insert({header, value});
        }

        return response;
    });
}
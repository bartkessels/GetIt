#pragma once

#include <cpprest/http_client.h>
#include <string>
#include <memory>

#include "domain/Request.hpp"

namespace getit::domain::request
{
    class CppRestRequest: public Request
    {
        public:
            CppRestRequest() = default;
            CppRestRequest(web::http::client::http_client* client);
            ~CppRestRequest();

            std::shared_ptr<getit::domain::Response> sendRequest(std::shared_ptr<RequestData> data) override;

            // void send(std::function<void(Response*)> callback) override;

        private:
            web::http::client::http_client* client;

            web::http::http_request buildRequest(std::shared_ptr<RequestData> data);
            void addHeadersToRequest(web::http::http_request* request, std::shared_ptr<RequestData> data);
            void addBodyToRequest(web::http::http_request* request, std::shared_ptr<RequestData> data);
            std::shared_ptr<getit::domain::Response> buildResponse(web::http::http_response restResponse);
    };
}

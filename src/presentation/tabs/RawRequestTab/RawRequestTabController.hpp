#pragma once

#include <memory>

#include "domain/factories/RequestFactory.hpp"
#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"
#include "presentation/tabs/RawRequestTab/RawRequestTabView.hpp"
#include "presentation/tabs/RequestTabController.hpp"

namespace getit::presentation::tabs
{
    class RawRequestTabController: public RequestTabController
    {
        public:
            explicit RawRequestTabController(std::shared_ptr<RawRequestTabView> view, std::shared_ptr<domain::factories::RequestFactory> factory);
            ~RawRequestTabController() = default;

            void setRequest(std::shared_ptr<domain::models::Request> request) override;
            void setResponse(std::shared_ptr<domain::models::Response> response) override;

            std::shared_ptr<domain::models::Request> getRequest() override;

        private:
            std::shared_ptr<RawRequestTabView> view;
            std::shared_ptr<domain::factories::RequestFactory> requestFactory;
    };
}
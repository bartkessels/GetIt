#pragma once

#include <memory>
#include <QWidget>

#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"

namespace getit::presentation::tabs
{
    struct RequestTabImplementation: public virtual QWidget
    {
        public:
            ~RequestTabImplementation() override = default;

            virtual std::shared_ptr<domain::models::Request> addToRequest(std::shared_ptr<domain::models::Request> request) = 0;
            virtual void setResponse(std::shared_ptr<domain::models::Response> response) = 0;
    };
}
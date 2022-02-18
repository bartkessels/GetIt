#pragma once

#include <map>
#include <QComboBox>
#include <QString>
#include <QWidget>
#include <string>

#include "domain/implementations/RawRequestBody.hpp"
#include "domain/models/Request.hpp"
#include "domain/models/Response.hpp"
#include "presentation/tabs/RequestTabImplementation.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RawRequestTabView; }
QT_END_NAMESPACE

namespace getit::presentation::tabs
{
    class RawRequestTabView: public RequestTabImplementation
    {
        public:
            explicit RawRequestTabView(QWidget* parent = nullptr);
            ~RawRequestTabView() override;

            std::shared_ptr<domain::models::Request> addToRequest(std::shared_ptr<domain::models::Request> request) override;
            void setResponse(std::shared_ptr<domain::models::Response> response) override;
        private:
            std::string getContentType();
            std::string getBody();

            Ui::RawRequestTabView* ui;
    };
}
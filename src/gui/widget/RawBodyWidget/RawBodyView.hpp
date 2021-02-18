#pragma once

#include <memory>
#include <QString>
#include <QWidget>

#include "domain/body/RawRequestBody.hpp"
#include "domain/RequestBody.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RawBodyView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class RawBodyView: public QWidget
    {
        public:
            explicit RawBodyView(QWidget* parent = nullptr);
            ~RawBodyView();
            
            std::shared_ptr<getit::domain::RequestBody> getBody();

            void setBody(std::string contentType, std::string body);
            
        private:
            Ui::RawBodyView* ui;
    };
}

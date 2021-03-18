#pragma once

#include <memory>
#include <QString>
#include <QWidget>

#include "gui/widget/BodyWidget/RawBodyTab/IRawBodyTabView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RawBodyTabView; }
QT_END_NAMESPACE

namespace getit::gui::widget::BodyWidget
{
    class RawBodyTabView: public QWidget, public IRawBodyTabView
    {
        public:
            explicit RawBodyTabView(QWidget* parent = nullptr);
            ~RawBodyTabView() override;

            std::string getContentType() override;
            std::string getBody() override;

            void setContentType(std::string contentType) override;
            void setBody(std::string body) override;

        private:
            Ui::RawBodyTabView* ui;
    };
}

#pragma once

#include <memory>
#include <string>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseRawBodyView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class ResponseRawBodyView: public QWidget
    {
        public:
            explicit ResponseRawBodyView(QWidget* parent = nullptr);
            ~ResponseRawBodyView() override;

            void setBody(std::string body);

        private:
            Ui::ResponseRawBodyView* ui;
    };
}
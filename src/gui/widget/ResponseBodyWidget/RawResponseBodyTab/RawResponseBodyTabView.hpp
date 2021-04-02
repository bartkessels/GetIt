#pragma once

#include <QString>
#include <QWidget>
#include <string>

#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/IRawResponseBodyTabView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RawResponseBodyTabView; }
QT_END_NAMESPACE

namespace getit::gui::widget::ResponseBodyWidget
{
    class RawResponseBodyTabView: public QWidget, public IRawResponseBodyTabView
    {
        public:
            explicit RawResponseBodyTabView(QWidget* parent = nullptr);
            ~RawResponseBodyTabView() override;

            void setBody(std::string body) override;

        private:
            Ui::RawResponseBodyTabView* ui;
    };
}
#pragma once

#include <QString>
#include <QWidget>
#include <string>

#include "gui/highlighter/Highlighter.hpp"
#include "gui/widget/ResponseBodyWidget/JsonResponseBodyTab/IJsonResponseBodyTabView.hpp"
#include "highlighter/JsonHighlighterRules.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class JsonResponseBodyTabView; }
QT_END_NAMESPACE

namespace getit::gui::widget::ResponseBodyWidget
{
    class JsonResponseBodyTabView: public QWidget, public IJsonResponseBodyTabView
    {
        public:
            explicit JsonResponseBodyTabView(QWidget* parent = nullptr);
            ~JsonResponseBodyTabView() override;

            void setBody(std::string body) override;

        private:
            Ui::JsonResponseBodyTabView* ui;
    };
}
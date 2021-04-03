#pragma once

#include <QComboBox>
#include <QString>
#include <QWidget>
#include <string>

#include "gui/highlighter/Highlighter.hpp"
#include "gui/widget/BodyWidget/RawBodyTab/IRawBodyTabView.hpp"
#include "highlighter/JsonHighlighterRules.hpp"
#include "highlighter/XmlHighlighterRules.hpp"

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
            getit::gui::highlighter::Highlighter* highlighter;
    };
}

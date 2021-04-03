#pragma once

#include <QString>
#include <QWidget>
#include <string>

#include "gui/highlighter/Highlighter.hpp"
#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/IXmlResponseBodyTabView.hpp"
#include "highlighter/XmlHighlighterRules.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class XmlResponseBodyTabView; }
QT_END_NAMESPACE

namespace getit::gui::widget::ResponseBodyWidget
{
    class XmlResponseBodyTabView: public QWidget, public IXmlResponseBodyTabView
    {
        public:
            explicit XmlResponseBodyTabView(QWidget* parent = nullptr);
            ~XmlResponseBodyTabView() override;

            void setBody(std::string body) override;

        private:
            Ui::XmlResponseBodyTabView* ui;
            getit::gui::highlighter::Highlighter* highlighter;
    };
}
#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/XmlResponseBodyTabView.hpp"
#include "./ui_XmlResponseBodyTabView.h"

using namespace getit::gui::widget::ResponseBodyWidget;

XmlResponseBodyTabView::XmlResponseBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::XmlResponseBodyTabView())
{
    ui->setupUi(this);
}

XmlResponseBodyTabView::~XmlResponseBodyTabView()
{
    delete ui;
}

void XmlResponseBodyTabView::setBody(std::string body)
{
    auto highlighter = new getit::gui::highlighter::Highlighter(
            ui->responseBody->document(),
            getit::highlighter::XmlHighlighterRules::rules
    );

    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
}
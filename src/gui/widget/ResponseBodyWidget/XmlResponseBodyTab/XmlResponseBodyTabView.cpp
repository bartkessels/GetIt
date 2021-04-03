#include "gui/widget/ResponseBodyWidget/XmlResponseBodyTab/XmlResponseBodyTabView.hpp"
#include "./ui_XmlResponseBodyTabView.h"

using namespace getit::gui::widget::ResponseBodyWidget;

XmlResponseBodyTabView::XmlResponseBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::XmlResponseBodyTabView())
{
    ui->setupUi(this);

    highlighter = new getit::gui::highlighter::Highlighter(
            ui->responseBody->document()
    );
}

XmlResponseBodyTabView::~XmlResponseBodyTabView()
{
    delete ui;
    delete highlighter;
}

void XmlResponseBodyTabView::setBody(std::string body)
{
    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
    highlighter->startHighlighting(getit::highlighter::XmlHighlighterRules::rules);
}
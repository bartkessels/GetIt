#include "gui/widget/ResponseBodyWidget/JsonResponseBodyTab/JsonResponseBodyTabView.hpp"
#include "./ui_JsonResponseBodyTabView.h"

using namespace getit::gui::widget::ResponseBodyWidget;

JsonResponseBodyTabView::JsonResponseBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::JsonResponseBodyTabView())
{
    ui->setupUi(this);

    highlighter = new getit::gui::highlighter::Highlighter(
            ui->responseBody->document()
    );
}

JsonResponseBodyTabView::~JsonResponseBodyTabView()
{
    delete ui;
    delete highlighter;
}

void JsonResponseBodyTabView::setBody(std::string body)
{
    highlighter->startHighlighting(getit::highlighter::JsonHighlighterRules::rules);
    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
}
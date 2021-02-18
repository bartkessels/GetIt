#include "gui/widget/ResponseRawBodyWidget/ResponseRawBodyView.hpp"
#include "./ui_ResponseRawBodyView.h"

using namespace getit::gui::widget;

ResponseRawBodyView::ResponseRawBodyView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseRawBodyView())
{
    ui->setupUi(this);
}

ResponseRawBodyView::~ResponseRawBodyView()
{
    delete ui;
}

void ResponseRawBodyView::setBody(std::string body)
{
    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
}
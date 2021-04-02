#include "gui/widget/ResponseBodyWidget/RawResponseBodyTab/RawResponseBodyTabView.hpp"
#include "./ui_RawResponseBodyTabView.h"

using namespace getit::gui::widget::ResponseBodyWidget;

RawResponseBodyTabView::RawResponseBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::RawResponseBodyTabView())
{
    ui->setupUi(this);
}

RawResponseBodyTabView::~RawResponseBodyTabView()
{
    delete ui;
}

void RawResponseBodyTabView::setBody(std::string body)
{
    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
}
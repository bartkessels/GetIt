#include "gui/widget/RawBodyWidget/RawBodyView.hpp"
#include "./ui_RawBodyView.h"

using namespace getit::gui::widget;

RawBodyView::RawBodyView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::RawBodyView())
{
    ui->setupUi(this);
}

RawBodyView::~RawBodyView()
{
    delete ui;
}

std::shared_ptr<getit::domain::RequestBody> RawBodyView::getBody()
{
    auto contentType = ui->contentType->text().toStdString();
    auto body = ui->rawBody->document()->toPlainText().toStdString();

    auto requestBody = std::make_shared<getit::domain::body::RawRequestBody>(contentType);
    requestBody->setBody(body);

    return requestBody;
}

void RawBodyView::setBody(std::string contentType, std::string body)
{
    ui->contentType->setText(QString::fromStdString(contentType));
    ui->rawBody->document()->setPlainText(QString::fromStdString(body));
}

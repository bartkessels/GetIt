#include "presentation/tabs/RawRequestTab/RawRequestTabView.hpp"
#include "./ui_RawRequestTabView.h"

using namespace getit::presentation::tabs;

RawRequestTabView::RawRequestTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::RawRequestTabView())
{
    ui->setupUi(this);
}

RawRequestTabView::~RawRequestTabView()
{
    delete ui;
}

std::shared_ptr<getit::domain::models::Request> RawRequestTabView::addToRequest(std::shared_ptr<getit::domain::models::Request> request)
{
    const auto& entity = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(request);
    entity->setContentType(this->getContentType());
    entity->setBody(this->getBody());

    return entity;
}

void RawRequestTabView::setResponse(std::shared_ptr<getit::domain::models::Response> response)
{

}

std::string RawRequestTabView::getContentType()
{
    return ui->contentType->text().toStdString();
}

std::string RawRequestTabView::getBody()
{
    return ui->rawBody->document()->toPlainText().toStdString();
}
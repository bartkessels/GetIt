#include "presentation/fragments/ResponseFragment/ResponseFragmentView.hpp"
#include "./ui_ResponseFragmentView.h"

using namespace getit::presentation::fragments;

ResponseFragmentView::ResponseFragmentView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseFragmentView())
{
    ui->setupUi(this);
}

ResponseFragmentView::~ResponseFragmentView()
{
    delete ui;
}

std::map<std::string, std::string> ResponseFragmentView::getHeaders()
{
    std::map<std::string, std::string> headers;

    for (int i = 0; i < ui->headers->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->headers->topLevelItem(i);

        headers.insert_or_assign(
                itm->text(keyIndex).toStdString(),
                itm->text(valueIndex).toStdString()
        );
    }

    return headers;
}

std::string ResponseFragmentView::getBody()
{
    return ui->body->document()->toPlainText().toStdString();
}

void ResponseFragmentView::setHeaders(const std::map<std::string, std::string>& headers)
{
    for (const auto& [header, value] : headers) {
        addHeader(header, value);
    }
}

void ResponseFragmentView::clearHeaders()
{
    ui->headers->clear();
}

void ResponseFragmentView::setBody(const std::string& body)
{
    ui->body->document()->setPlainText(QString::fromStdString(body));
}

void ResponseFragmentView::addHeader(const std::string& header, const std::string& value)
{
    const auto& row = new QTreeWidgetItem(ui->headers);

    row->setText(keyIndex, QString::fromStdString(header));
    row->setText(valueIndex, QString::fromStdString(value));
    row->setFlags(treeItemFlag);
}
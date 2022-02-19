#include "presentation/fragments/HeadersFragment/HeadersFragmentView.hpp"
#include "./ui_HeadersFragmentView.h"

using namespace getit::presentation::fragments;

HeadersFragmentView::HeadersFragmentView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::HeadersFragmentView())
{
    ui->setupUi(this);

    connect(ui->addHeader, &QPushButton::pressed, this, &HeadersFragmentView::addDefaultHeader);
    connect(ui->removeHeader, &QPushButton::pressed, this, &HeadersFragmentView::removeSelectedHeader);
}

HeadersFragmentView::~HeadersFragmentView()
{
    delete ui;
}

std::map<std::string, std::string> HeadersFragmentView::getHeaders()
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

void HeadersFragmentView::setHeaders(std::map<std::string, std::string> headers)
{
    for (const auto& [header, value] : headers) {
        addHeader(header, value);
    }
}

void HeadersFragmentView::addDefaultHeader()
{
    this->addHeader("Header", "Value");
}

void HeadersFragmentView::addHeader(std::string header, std::string value)
{
    const auto& row = new QTreeWidgetItem(ui->headers);

    row->setText(keyIndex, QString::fromStdString(header));
    row->setText(valueIndex, QString::fromStdString(value));
    row->setFlags(treeItemFlag);
}

void HeadersFragmentView::removeSelectedHeader()
{
    delete ui->headers->currentItem();
}
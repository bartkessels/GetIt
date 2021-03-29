#include "gui/widget/HeadersWidget/HeadersView.hpp"
#include "./ui_HeadersView.h"

using namespace getit::gui::widget;

HeadersView::HeadersView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::HeadersView())
{
    ui->setupUi(this);

    connect(ui->btnAddHeader, &QPushButton::pressed,
            this, [this]() {
                this->addHeader("Header", "Value");
            });
    connect(ui->btnRemoveHeader, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedHeader();
            });
}

HeadersView::~HeadersView()
{
    delete ui;
}

std::list<std::pair<std::string, std::string>> HeadersView::getHeaders()
{
    std::list<std::pair<std::string, std::string>> headers;

    for (int i = 0; i < ui->treeHeaders->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->treeHeaders->topLevelItem(i);

        headers.emplace_back(
            itm->text(headerIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        );
    }

    return headers;
}

void HeadersView::setHeaders(std::list<std::pair<std::string, std::string>> headers)
{
    for (const auto& [header, value] : headers) {
        this->addHeader(header, value);
    }
}

void HeadersView::addHeader(std::string header, std::string value)
{
    const auto& headerRow = new QTreeWidgetItem(ui->treeHeaders);

    headerRow->setText(headerIndex, QString::fromStdString(header));
    headerRow->setText(valueIndex, QString::fromStdString(value));
    headerRow->setFlags(headerFlags);
}

void HeadersView::removeSelectedHeader()
{
    delete ui->treeHeaders->currentItem();
}
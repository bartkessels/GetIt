#include "gui/widget/HeadersWidget/HeadersWidget.hpp"
#include "./ui_HeadersWidget.h"

using namespace getit::gui::widget;

HeadersWidget::HeadersWidget(QWidget *parent):
    QWidget(parent),
    ui(new Ui::HeadersWidget())
{
    ui->setupUi(this);

    this->connectSignals();
}

HeadersWidget::~HeadersWidget()
{
    delete ui;
}

void HeadersWidget::addToRequest(std::shared_ptr<domain::Request> request)
{
    for(int i = 0; i < ui->treeHeaders->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeHeaders->topLevelItem(i);
        const auto& header = item->text(0).toStdString();
        const auto& value = item->text(1).toStdString();

        // request->addHeader(header, value);
    }
}

void HeadersWidget::connectSignals()
{
    connect(ui->btnAddHeader, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeHeaders);
                row->setText(0, "Key");
                row->setText(1, "Value");
                row->setFlags(treeWidgetItemFlags);
            });

    connect(ui->btnRemoveHeader, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeHeaders->currentItem();
            });
}
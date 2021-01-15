#include "gui/widget/BodyWidget/BodyWidget.hpp"
#include "./ui_BodyWidget.h"

using namespace getit::gui::widget;

BodyWidget::BodyWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::BodyWidget())
{
    ui->setupUi(this);

    this->connectSignals();
}

BodyWidget::~BodyWidget()
{
    delete ui;
}

void BodyWidget::addToRequest(std::shared_ptr<domain::Request> request)
{
    // const auto& bodyValue = ui->textBodyRaw->document()->toPlainText().toStdString();
    // const auto& contentType = ui->textContentType->text().toStdString();
    // const auto& body = std::make_shared<domain::RawRequestBody>(contentType);

    // body->setBody(bodyValue);

    // request->setBody(body);
}

void BodyWidget::connectSignals()
{
    connect(ui->treeBodyFormdata, &QTreeWidget::itemChanged,
            this, &BodyWidget::formdataItemsChanged);

    connect(ui->treeBodyFormdataFiles, &QTreeWidget::itemChanged,
            this, &BodyWidget::formdataItemsChanged);

    connect(ui->btnAddFormdata, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeBodyFormdata);
                row->setText(0, "Key");
                row->setText(1, "Value");
                row->setFlags(treeWidgetItemFlags);
            });

    connect(ui->btnRemoveFormdata, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeBodyFormdata->currentItem();
                ui->treeBodyFormdata->itemChanged(nullptr, 0);
            });

    connect(ui->btnAddFormdataFile, &QPushButton::pressed,
            this, [=]() {
                const auto& row = new QTreeWidgetItem(ui->treeBodyFormdataFiles);
                row->setText(0, "Key");
                row->setFlags(treeWidgetItemFlags);

                emit ui->treeBodyFormdataFiles->itemDoubleClicked(row, 1);
            });

    connect(ui->btnRemoveFormdataFile, &QPushButton::pressed,
            this, [=]() {
                delete ui->treeBodyFormdataFiles->currentItem();
            });

    connect(ui->treeBodyFormdataFiles, &QTreeWidget::itemDoubleClicked,
            this, [=](QTreeWidgetItem* selectedItem, int columnIndex) {
                if (columnIndex != 1) return;

                const auto& fileName = QFileDialog::getOpenFileUrl(this);

                if (!fileName.isEmpty()) {
                    selectedItem->setText(1, fileName.toLocalFile());
                }

                if (selectedItem->text(1).isEmpty()) {
                    delete selectedItem;
                }
            });
}

void BodyWidget::formdataItemsChanged(QTreeWidgetItem*, int)
{
    const auto& boundary = generateBoundary();
    const auto& data = std::make_unique<getit::domain::body::FormdataRequestBody>(boundary);

    for(int i = 0; i < ui->treeBodyFormdata->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeBodyFormdata->topLevelItem(i);
        const auto& formdataKey = item->text(0).toStdString();
        const auto& formdataValue = item->text(1).toStdString();

        data->addElement(formdataKey, formdataValue);
    }

    for(int i = 0; i < ui->treeBodyFormdataFiles->topLevelItemCount(); ++i ) {
        QTreeWidgetItem* item = ui->treeBodyFormdataFiles->topLevelItem(i);
        const auto& formdataKey = item->text(0).toStdString();
        const auto& filePath = item->text(1).toStdString();

        data->addFile(formdataKey, filePath);
    }

    ui->textContentType->setText(data->getContentType().c_str());
    ui->textBodyRaw->document()->setPlainText(data->getBody().c_str());
}

std::string BodyWidget::generateBoundary()
{
    auto now = std::chrono::system_clock::now();
    auto millis = now.time_since_epoch().count();
    auto boundary = boost::format("%1%") % millis;

    return boundary.str();
}
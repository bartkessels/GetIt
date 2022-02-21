#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "./ui_BodyFragmentView.h"

using namespace getit;
using namespace getit::presentation::fragments;

BodyFragmentView::BodyFragmentView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::BodyFragmentView())
{
    ui->setupUi(this);
    toggleBody();

    connect(ui->bodyType, &QComboBox::currentIndexChanged, this, &BodyFragmentView::toggleBody);
    connect(ui->addElement, &QPushButton::pressed, this, &BodyFragmentView::addDefaultElement);
    connect(ui->removeElement, &QPushButton::pressed, this, &BodyFragmentView::removeSelectedElement);
    connect(ui->addFile, &QPushButton::pressed, this, &BodyFragmentView::addDefaultFile);
    connect(ui->removeFile, &QPushButton::pressed, this, &BodyFragmentView::removeSelectedFile);
}

BodyFragmentView::~BodyFragmentView()
{
    delete ui;
}

std::shared_ptr<domain::implementations::FormdataRequestBody> BodyFragmentView::getFormDataBody()
{
    const auto& body = std::make_shared<domain::implementations::FormdataRequestBody>();

    body->setElements(getRowsFromTreeWidget(ui->elements));
    body->setFiles(getRowsFromTreeWidget(ui->files));

    return body;
}

std::shared_ptr<domain::implementations::RawRequestBody> BodyFragmentView::getRawBody()
{
    const auto& body = std::make_shared<domain::implementations::RawRequestBody>();

    body->setContentType(ui->contentType->text().toStdString());
    body->setBody(ui->raw->document()->toPlainText().toStdString());

    return body;
}

void BodyFragmentView::setFormDataBody(const std::shared_ptr<domain::implementations::FormdataRequestBody>& body)
{
    for (const auto& [element, value] : body->getElements()) {
        addRowToTreeWidget(element, value, ui->elements);
    }

    for (const auto& [file, filePath] : body->getFiles()) {
        addRowToTreeWidget(file, filePath, ui->files);
    }
}

void BodyFragmentView::setRawBody(const std::shared_ptr<domain::implementations::RawRequestBody>& body)
{
    ui->contentType->setText(QString::fromStdString(body->getContentType()));
    ui->raw->setPlainText(QString::fromStdString(body->getBody()));
}

BodyType BodyFragmentView::getBodyType()
{
    if (ui->bodyType->currentIndex() == BodyType::RAW)
        return BodyType::RAW;
    return BodyType::FORM_DATA;
}

void BodyFragmentView::setBodyType(const BodyType& bodyType)
{
    ui->bodyType->setCurrentIndex(bodyType);
}

void BodyFragmentView::toggleBody()
{
    // Show form data view by default
    ui->formdataWidget->show();
    ui->rawWidget->hide();

    if (ui->bodyType->currentIndex() == BodyType::RAW) {
        ui->formdataWidget->hide();
        ui->rawWidget->show();
    }
}

void BodyFragmentView::addDefaultElement()
{
    addRowToTreeWidget("Key", "Value", ui->elements);
}

void BodyFragmentView::removeSelectedElement()
{
    delete ui->elements->currentItem();
}

void BodyFragmentView::addDefaultFile()
{
    const auto& filePath = QFileDialog::getOpenFileUrl(this);

    if (!filePath.isEmpty()) {
        addRowToTreeWidget("File", filePath.toLocalFile().toStdString(), ui->files);
    }
}

void BodyFragmentView::removeSelectedFile()
{
    delete ui->files->currentItem();
}

void BodyFragmentView::addRowToTreeWidget(const std::string &key, const std::string &value, QTreeWidget* widget)
{
    const auto& row = new QTreeWidgetItem(widget);

    row->setText(keyIndex, QString::fromStdString(key));
    row->setText(valueIndex, QString::fromStdString(value));
    row->setFlags(treeItemFlag);
}

std::map<std::string, std::string> BodyFragmentView::getRowsFromTreeWidget(QTreeWidget* widget) const
{
    std::map<std::string, std::string> rows;

    for (int i = 0; i < widget->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = widget->topLevelItem(i);

        rows.insert_or_assign(
                itm->text(keyIndex).toStdString(),
                itm->text(valueIndex).toStdString()
        );
    }

    return rows;
}
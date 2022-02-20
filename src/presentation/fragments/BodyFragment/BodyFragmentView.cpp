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

    connect(ui->bodyType, &QComboBox::currentTextChanged, this, &BodyFragmentView::toggleBody);
    connect(ui->addElement, &QPushButton::pressed, this, &BodyFragmentView::addDefaultElement);
    connect(ui->removeElement, &QPushButton::pressed, this, &BodyFragmentView::removeSelectedElement);
    connect(ui->addFile, &QPushButton::pressed, this, &BodyFragmentView::addDefaultFile);
    connect(ui->removeFile, &QPushButton::pressed, this, &BodyFragmentView::removeSelectedFile);
}

BodyFragmentView::~BodyFragmentView()
{
    delete ui;
}

std::shared_ptr<domain::models::RequestBody> BodyFragmentView::getBody()
{
    if (bodyType == BodyType::FORM_DATA) {
        const auto& body = std::make_shared<domain::implementations::FormdataRequestBody>();

        body->setElements(getRowsFromTreeWidget(ui->elements));
        body->setFiles(getRowsFromTreeWidget(ui->files));

        return body;
    } else if (bodyType == BodyType::RAW) {
        const auto& body = std::make_shared<domain::implementations::RawRequestBody>();

        body->setContentType(ui->contentType->text().toStdString());
        body->setBody(ui->raw->document()->toPlainText().toStdString());

        return body;
    }

    return nullptr;
}

void BodyFragmentView::setBody(const std::shared_ptr<domain::models::RequestBody>& body)
{
    if (const auto& formdata = std::dynamic_pointer_cast<domain::implementations::FormdataRequestBody>(body)) {
        setBody(formdata);
    }
    if (const auto& raw = std::dynamic_pointer_cast<getit::domain::implementations::RawRequestBody>(body)) {
        setBody(raw);
    }
}

void BodyFragmentView::setBody(const std::shared_ptr<domain::implementations::FormdataRequestBody>& body)
{
    for (const auto& [element, value] : body->getElements()) {
        addRowToTreeWidget(element, value, ui->elements);
    }

    for (const auto& [file, filePath] : body->getFiles()) {
        addRowToTreeWidget(file, filePath, ui->files);
    }
}

void BodyFragmentView::setBody(const std::shared_ptr<domain::implementations::RawRequestBody>& body)
{
    ui->contentType->setText(QString::fromStdString(body->getContentType()));
    ui->raw->setPlainText(QString::fromStdString(body->getBody()));
}

void BodyFragmentView::toggleBody()
{
    // Show form data view by default
    bodyType = BodyType::FORM_DATA;
    ui->formdataWidget->show();
    ui->rawWidget->hide();

    if (ui->bodyType->currentText().toLower().toStdString() == "raw") {
        bodyType = BodyType::RAW;
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
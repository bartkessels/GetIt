#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "./ui_BodyFragmentView.h"

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

std::string BodyFragmentView::getContentType()
{
    // Depends on selected bodyType
    return "";
}

std::string BodyFragmentView::getBody()
{
    // Depends on selected bodyType
    return "";
}

void BodyFragmentView::toggleBody()
{
    // Show form data view by default
    ui->formdataWidget->show();
    ui->rawWidget->hide();

    if (ui->bodyType->currentText().toLower().toStdString() == "raw") {
        ui->formdataWidget->hide();
        ui->rawWidget->show();
    }
}

void BodyFragmentView::addDefaultElement()
{
    addElement("Key", "Value");
}

void BodyFragmentView::addElement(const std::string& element, const std::string& value)
{
    addRowToTreeWidget(element, value, ui->elements);
}

void BodyFragmentView::removeSelectedElement()
{
    delete ui->elements->currentItem();
}

void BodyFragmentView::addDefaultFile()
{
    const auto& fileName = QFileDialog::getOpenFileUrl(this);

    if (!fileName.isEmpty()) {
        this->addFile("File", fileName.toLocalFile().toStdString());
    }
}

void BodyFragmentView::addFile(const std::string& fileName, const std::string& filePath)
{
    addRowToTreeWidget(fileName, filePath, ui->files);
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
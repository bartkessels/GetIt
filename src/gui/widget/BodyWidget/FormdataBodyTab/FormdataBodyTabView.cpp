#include "gui/widget/BodyWidget/FormdataBodyTab/FormdataBodyTabView.hpp"
#include "./ui_FormdataBodyTabView.h"

using namespace getit::gui::widget::BodyWidget;

FormdataBodyTabView::FormdataBodyTabView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::FormdataBodyTabView())
{
    ui->setupUi(this);

    connect(ui->btnAddElement, &QPushButton::pressed,
            this, [this]() {
                this->addElement("Element", "Value");
            });
    connect(ui->btnRemoveElement, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedElement();
            });

    connect(ui->btnAddFile, &QPushButton::pressed,
            this, [this]() {
                const auto& fileName = QFileDialog::getOpenFileUrl(this);

                if (!fileName.isEmpty()) {
                    this->addFile("File", fileName.toLocalFile().toStdString());
                }
            });
    connect(ui->btnRemoveFile, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedFile();
            });
}

FormdataBodyTabView::~FormdataBodyTabView()
{
    delete ui;
}

std::map<std::string, std::string> FormdataBodyTabView::getElements()
{
    std::map<std::string, std::string> elements;

    for (int i = 0; i < ui->treeElements->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->treeElements->topLevelItem(i);

        elements.insert_or_assign(
            itm->text(elementIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        );
    }

    return elements;
}

std::map<std::string, std::string> FormdataBodyTabView::getFiles()
{
    std::map<std::string, std::string> files;

    for (int i = 0; i < ui->treeFiles->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->treeFiles->topLevelItem(i);


        files.insert_or_assign(
            itm->text(fileIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        );
    }

    return files;
}

void FormdataBodyTabView::setElements(std::map<std::string, std::string> elements)
{
    for (const auto& [element, value] : elements) {
        this->addElement(element, value);
    }
}

void FormdataBodyTabView::setFiles(std::map<std::string, std::string> files)
{
    for (const auto& [file, value] : files) {
        this->addFile(file, value);
    }
}

void FormdataBodyTabView::addElement(std::string element, std::string value)
{
    const auto& elementRow = new QTreeWidgetItem(ui->treeElements);

    elementRow->setText(elementIndex, QString::fromStdString(element));
    elementRow->setText(valueIndex, QString::fromStdString(value));
    elementRow->setFlags(rowFlags);
}

void FormdataBodyTabView::addFile(std::string file, std::string value)
{
    const auto& fileRow = new QTreeWidgetItem(ui->treeFiles);

    fileRow->setText(fileIndex, QString::fromStdString(file));
    fileRow->setText(valueIndex, QString::fromStdString(value));
    fileRow->setFlags(rowFlags);
}

void FormdataBodyTabView::removeSelectedElement()
{
    delete ui->treeElements->currentItem();
}

void FormdataBodyTabView::removeSelectedFile()
{
    delete ui->treeFiles->currentItem();
}
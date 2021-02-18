#include "gui/widget/ResponseHeadersWidget/ResponseHeadersView.hpp"
#include "./ui_ResponseHeadersView.h"

using namespace getit::gui::widget;

ResponseHeadersView::ResponseHeadersView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseHeadersView())
{
    ui->setupUi(this);
}

ResponseHeadersView::~ResponseHeadersView()
{
    delete ui;
}

void ResponseHeadersView::setHeaders(std::map<std::string, std::string> headers)
{
    ui->treeHeaders->clear();

    std::map<std::string, std::string>::iterator it;

    for (it = headers.begin(); it != headers.end(); it++) {
        this->addHeader(
            it->first,
            it->second
        );
    }
}

void ResponseHeadersView::addHeader(std::string header, std::string value)
{
    const auto& headerRow = new QTreeWidgetItem(ui->treeHeaders);

    headerRow->setText(headerIndex, QString::fromStdString(header));
    headerRow->setText(valueIndex, QString::fromStdString(value));
}
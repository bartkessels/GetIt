#include "gui/widget/UriWidget/UriView.hpp"
#include "./ui_UriView.h"

using namespace getit::gui::widget;

UriView::UriView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::UriView())
{
    ui->setupUi(this);
}

UriView::~UriView()
{
    delete ui;
}

std::string UriView::getUri()
{
    return ui->uri->text().toStdString();
}

void UriView::setUri(std::string uri)
{
    ui->uri->setText(QString::fromStdString(uri));
}
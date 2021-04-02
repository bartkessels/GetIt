#include "gui/widget/ResponseBodyWidget/ResponseBodyView.hpp"
#include "./ui_ResponseBodyView.h"

using namespace getit::gui::widget;

ResponseBodyView::ResponseBodyView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::ResponseBodyView())
{
    ui->setupUi(this);
}

ResponseBodyView::~ResponseBodyView()
{
    delete ui;
}

void ResponseBodyView::addResponseBodyTab(QWidget* tab, std::string name)
{
    ui->responseBodyTabs->addTab(tab, QString::fromStdString(name));
}
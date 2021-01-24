#include "gui/widget/MethodWidget/MethodView.hpp"
#include "./ui_MethodView.h"

using namespace getit::gui::widget;

MethodView::MethodView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::MethodView())
{
    ui->setupUi(this);
}

MethodView::~MethodView()
{
    delete ui;
}

std::string MethodView::getMethod()
{
    return ui->method->currentText().toStdString();
}
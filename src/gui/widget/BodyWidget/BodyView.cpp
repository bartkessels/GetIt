#include "gui/widget/BodyWidget/BodyView.hpp"
#include "./ui_BodyView.h"

using namespace getit::gui::widget;

BodyView::BodyView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::BodyView())
{
    ui->setupUi(this);
}

BodyView::~BodyView()
{
    delete ui;
}

void BodyView::addBodyTab(QWidget* tab, std::string name)
{
    ui->bodyTabs->addTab(tab, QString::fromStdString(name));
}

int BodyView::getSelectedTabIndex()
{
    return ui->bodyTabs->currentIndex();
}
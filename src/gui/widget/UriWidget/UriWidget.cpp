#include "gui/widget/UriWidget/UriWidget.hpp"

using namespace getit::gui::widget;

UriWidget::UriWidget(QWidget* parent):
    QWidget(parent),
    ui(new Ui::UriWidget())
{
    ui->setupUi(this);
}

UriWidget::~UriWidget()
{
    delete ui;
}

void UriWidget::executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data)
{
    const auto& uri = ui->uri->text().toStdString();
    data->setUri(uri);
}
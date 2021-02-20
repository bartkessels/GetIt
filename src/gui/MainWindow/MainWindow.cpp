#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::gui;

MainWindow::MainWindow(const std::shared_ptr<getit::domain::RequestFactory>& factory, QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow())
{
    ui->setupUi(this);
    this->request = factory->getRequest();

    connect(ui->btnSend, &QPushButton::pressed,
            [this]() {
                this->request->send();
            });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registerUriView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view)
{
    request->registerPipeline(controller);
    this->ui->uriWidget->addWidget(view.get());
}

void MainWindow::registerMethodView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view)
{
    request->registerPipeline(controller);
    this->ui->methodWidget->addWidget(view.get());
}

void MainWindow::registerInformationView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view, std::string name)
{
    request->registerPipeline(controller);
    this->ui->informationTabWidget->addTab(
        view.get(),
        QString::fromStdString(name)
    );
}

void MainWindow::registerBodyView(std::shared_ptr<getit::domain::BeforeRequestPipeline> controller, std::shared_ptr<QWidget> view, std::string name)
{
    request->registerPipeline(controller);
    this->ui->bodyTabWidget->addTab(view.get(), QString::fromStdString(name));
}

void MainWindow::registerResponseHeadersView(std::shared_ptr<getit::gui::AfterWidgetController> controller, std::shared_ptr<QWidget> view)
{
    this->registerAfterRequestView(controller, view);
    this->ui->responseHeadersWidget->addWidget(view.get());
}

void MainWindow::registerResponseBodyView(std::shared_ptr<getit::gui::AfterWidgetController> controller, std::shared_ptr<QWidget> view, std::string name)
{
    this->registerAfterRequestView(controller, view);
    this->ui->responseBodyTabWidget->addTab(view.get(), QString::fromStdString(name));
}

void MainWindow::registerAfterRequestView(std::shared_ptr<getit::gui::AfterWidgetController> controller, std::shared_ptr<QWidget> view)
{
    controller->registerView(view);
    request->registerPipeline(controller);
}

void MainWindow::registerView(std::shared_ptr<getit::gui::BeforeWidgetController> controller, std::shared_ptr<QWidget> view)
{
    controller->registerView(view);
    request->registerPipeline(controller);
}

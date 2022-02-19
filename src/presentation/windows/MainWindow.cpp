#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::presentation::windows;

MainWindow::MainWindow(std::shared_ptr<getit::domain::factories::RequestFactory> requestFactory, QWidget* parent):
    QMainWindow(parent),
    requestFactory(std::move(requestFactory)),
    ui(new Ui::MainWindow())
{
    this->ui->setupUi(this);
    this->registerControllers();

    connect(ui->send, &QPushButton::pressed, this, &MainWindow::sendRequest);
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::sendRequest()
{
    const auto& method = ui->method->currentText().toStdString();
    const auto& uri = ui->uri->text().toStdString();

    const auto& request = requestFactory->getRequest(method, uri);
    request->setBody(bodyController->getContent()->body);
    request->setHeaders(headersController->getContent()->headers);
}

void MainWindow::registerControllers()
{
    auto bodyView = new fragments::BodyFragmentView();
    auto headersView = new fragments::HeadersFragmentView();

    bodyController = std::make_shared<fragments::BodyFragmentController>(bodyView);
    headersController = std::make_shared<fragments::HeadersFragmentController>(headersView);

    ui->tabs->addTab(bodyView, "Body");
    ui->tabs->addTab(headersView, "Headers");
}
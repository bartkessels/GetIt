#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::presentation::windows;
using namespace getit::domain::factories;
using namespace getit::service::factories;

MainWindow::MainWindow(std::shared_ptr<RequestFactory> requestFactory, std::shared_ptr<RequestServiceFactory> requestServiceFactory, QWidget* parent):
    QMainWindow(parent),
    requestFactory(std::move(requestFactory)),
    requestServiceFactory(std::move(requestServiceFactory)),
    ui(new Ui::MainWindow())
{
    this->ui->setupUi(this);
    this->registerControllers();

    connect(ui->send, &QPushButton::pressed, this, &MainWindow::sendRequest);
    connect(this, &MainWindow::responseReceived, this, [this](auto response) {
        responseController->setContent(response);
        ui->tabs->setCurrentIndex(ui->tabs->count() - 1);
    });
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

void MainWindow::sendRequest()
{
    auto method = ui->method->currentText().toStdString();
    auto uri = ui->uri->text().toStdString();

    auto request = requestFactory->getRequest(method, uri);
    const auto& requestService = requestServiceFactory->getRequestService();
    const auto& responseContent = std::make_shared<fragments::ResponseFragmentModel>();

    request->setBody(bodyController->getContent()->body);
    request->setHeaders(headersController->getContent()->headers);

    QThread::create([this, requestService, request, responseContent] {
        auto response = requestService->send(request).get();
        responseContent->body = response->body;
        responseContent->headers = response->headers;

        emit responseReceived(responseContent);
    })->start();
}

void MainWindow::registerControllers()
{
    auto bodyView = new fragments::BodyFragmentView();
    auto headersView = new fragments::HeadersFragmentView();
    auto responseView = new fragments::ResponseFragmentView();

    bodyController = std::make_shared<fragments::BodyFragmentController>(bodyView);
    headersController = std::make_shared<fragments::HeadersFragmentController>(headersView);
    responseController = std::make_shared<fragments::ResponseFragmentController>(responseView);

    ui->tabs->addTab(bodyView, "Body");
    ui->tabs->addTab(headersView, "Headers");
    ui->tabs->addTab(responseView, "Response");
}
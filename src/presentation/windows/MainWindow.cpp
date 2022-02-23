#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::data::contracts;
using namespace getit::domain::contracts;
using namespace getit::presentation::windows;
using namespace getit::service::contracts;

MainWindow::MainWindow(
        std::shared_ptr<RequestFactory> requestFactory,
        std::shared_ptr<RequestServiceFactory> requestServiceFactory,
        std::shared_ptr<RequestRepositoryFactory> requestRepositoryFactory,
        QWidget* parent
):
    QMainWindow(parent),
    requestFactory(std::move(requestFactory)),
    requestServiceFactory(std::move(requestServiceFactory)),
    requestRepositoryFactory(std::move(requestRepositoryFactory)),
    ui(new Ui::MainWindow())
{
    this->ui->setupUi(this);
    this->registerControllers();

    connect(ui->send, &QPushButton::pressed, this, &MainWindow::sendRequest);
    connect(ui->menuItemSave, &QAction::triggered, this, &MainWindow::saveRequest);
    connect(ui->menuItemSaveAs, &QAction::triggered, this, &MainWindow::saveRequest);
    connect(this, &MainWindow::responseReceived, this, [this](auto response) {
        responseController->setContent(response);
        ui->tabs->setCurrentIndex(ui->tabs->count() - 1);
    });
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

std::shared_ptr<getit::domain::models::Request> MainWindow::buildRequest()
{
    auto method = ui->method->currentText().toStdString();
    auto uri = ui->uri->text().toStdString();
    auto request = requestFactory->getRequest(method, uri);

    request->setBody(bodyController->getContent());
    request->setHeaders(headersController->getContent());

    return request;
}

void MainWindow::sendRequest()
{
    const auto& requestService = requestServiceFactory->getRequestService();
    auto request = buildRequest();

    QThread::create([this, requestService, request] {
        auto response = requestService->send(request).get();
        emit responseReceived(response);
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

void MainWindow::saveRequest()
{
    if (saveLocation.empty())
        saveRequestAs();

    const auto& request = buildRequest();
    const auto& repository = requestRepositoryFactory->getRepository(request);

    repository->saveRequest(saveLocation);
}

void MainWindow::saveRequestAs()
{
    const auto& filePath = QFileDialog::getSaveFileUrl(this, "Save GetIt Request", QUrl(), "*.getit");

    if (!filePath.isEmpty())
        saveLocation = filePath.toLocalFile().toStdString();
}
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
    connect(ui->menuItemOpen, &QAction::triggered, this, &MainWindow::openRequest);
    connect(this, &MainWindow::responseReceived, this, [this](auto response) {
        responseController->setContent(response);
        ui->tabs->setCurrentIndex(ui->tabs->count() - 1);
    });
    connect(this, &MainWindow::errorOccurred, this, &MainWindow::displayErrorMessage);
}

MainWindow::~MainWindow()
{
    delete this->ui;
}

std::shared_ptr<getit::domain::models::Request> MainWindow::getRequest()
{
    auto method = ui->method->currentText().toStdString();
    auto uri = ui->uri->text().toStdString();
    auto headers = headersController->getContent();
    auto request = requestFactory->getRequest(method, uri, headers);

    request->setBody(bodyController->getContent());

    return request;
}

void MainWindow::setRequest(const std::shared_ptr<getit::domain::models::Request>& request)
{
    ui->method->setCurrentText(QString::fromStdString(request->getMethod()));
    ui->uri->setText(QString::fromStdString(request->getUri()));

    bodyController->setContent(request->getBody());
    headersController->setContent(request->getHeaders());
}

void MainWindow::sendRequest()
{
    const auto& requestService = requestServiceFactory->getRequestService();
    auto request = getRequest();

    QThread::create([this, requestService, request] {
        try
        {
            auto response = requestService->send(request).get();
            emit responseReceived(response);
        }
        catch(const std::exception& e)
        {
            emit errorOccurred(e.what());
        }
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

    const auto& request = getRequest();
    const auto& repository = requestRepositoryFactory->getRepository();

    repository->saveRequest(saveLocation, request);
}

void MainWindow::saveRequestAs()
{
    const auto& filePath = QFileDialog::getSaveFileUrl(this, "Save GetIt Request", QUrl(), "*.getit");

    if (!filePath.isEmpty())
        saveLocation = filePath.toLocalFile().toStdString();
}

void MainWindow::openRequest()
{
    const auto& filePath = QFileDialog::getOpenFileUrl(this, "Open GetIt Request", QUrl(), "*.getit");

    if (filePath.isEmpty())
        return;

    saveLocation = filePath.toLocalFile().toStdString();
    const auto& repository = requestRepositoryFactory->getRepository();
    const auto& request = repository->loadRequest(saveLocation);
    setRequest(request);
}

void MainWindow::displayErrorMessage(const std::string& errorMessage)
{
    QMessageBox::warning(this, windowTitle(), QString::fromStdString(errorMessage));
}
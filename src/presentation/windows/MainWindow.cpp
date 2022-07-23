#include "presentation/windows/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::presentation;
using namespace getit::presentation::windows;

MainWindow::MainWindow(QWidget* parent):
    QMainWindow(parent),
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

void MainWindow::setViewModel(std::shared_ptr<IMainWindowViewModel> viewModel)
{
    this->viewModel = viewModel;
}

void MainWindow::updateState(std::shared_ptr<states::RequestState> state)
{
    if (const auto& error = std::dynamic_pointer_cast<states::Error>(state))
    {
        emit errorOccurred(error->message);
    }
    else if (const auto& fileOpened = std::dynamic_pointer_cast<states::FileOpened>(state))
    {
        emit setRequest(fileOpened->request);
    }
    else if (std::dynamic_pointer_cast<states::Sending>(state))
    {
        // Loading
    }
    else if (const auto& sent = std::dynamic_pointer_cast<states::Sent>(state))
    {
        emit setResponse(sent->response);
    }
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

void MainWindow::sendRequest()
{
    const auto& method = ui->method->currentText().toStdString();
    const auto& uri = ui->uri->text().toStdString();
    const auto& headers = headersController->getContent();
    const auto& body = bodyController->getContent();

    this->viewModel->sendRequest(method, uri, headers, body);
}

void MainWindow::setRequest(const std::shared_ptr<domain::models::Request>& request)
{
    ui->method->setCurrentText(QString::fromStdString(request->getMethod()));
    ui->uri->setText(QString::fromStdString(request->getUri()));
    headersController->setContent(request->getHeaders());
    bodyController->setContent(request->getBody());
}

void MainWindow::setResponse(const std::shared_ptr<domain::models::Response>& response)
{
    responseController->setContent(response);
}

void MainWindow::saveRequest()
{
    if (saveLocation.empty()) {
        const auto& filePath = QFileDialog::getSaveFileUrl(this, "Save GetIt Request", QUrl(), "*.getit");

        if (filePath.isEmpty())
            return;

        saveLocation = filePath.toLocalFile().toStdString();
    }

    const auto& method = ui->method->currentText().toStdString();
    const auto& uri = ui->uri->text().toStdString();
    const auto& headers = headersController->getContent();
    const auto& body = bodyController->getContent();

    this->viewModel->saveRequest(method, uri, headers, body, saveLocation);
}

void MainWindow::openRequest()
{
    const auto& filePath = QFileDialog::getOpenFileUrl(this, "Open GetIt Request", QUrl(), "*.getit");

    if (filePath.isEmpty())
        return;

    saveLocation = filePath.toLocalFile().toStdString();
    this->viewModel->openRequest(saveLocation);
}

void MainWindow::displayErrorMessage(const std::string& errorMessage)
{
    QMessageBox::warning(this, windowTitle(), QString::fromStdString(errorMessage));
}
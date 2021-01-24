#include "gui/MainWindow/MainWindow.hpp"
#include "./ui_MainWindow.h"

using namespace getit::gui;

MainWindow::MainWindow(const std::shared_ptr<getit::domain::RequestFactory>& factory, QWidget* parent):
    QMainWindow(parent),
    ui(new Ui::MainWindow()),
    requestInfoWidget(std::make_shared<widget::RequestInfoWidget>(this)),
    bodyWidget(std::make_shared<widget::BodyWidget>(this))
{
    ui->setupUi(this);
    this->request = factory->getRequest();

    this->connectSignals();

    this->ui->bodyWidget->addWidget(bodyWidget.get());
    this->ui->requestInfoWidget->addWidget(requestInfoWidget.get());

    // Register method
    const auto& methodView = std::make_shared<getit::gui::widget::MethodView>(this);
    const auto& methodController = std::make_shared<getit::gui::widget::MethodController>();
    this->registerView(methodController, methodView);
    this->ui->methodWidget->addWidget(methodView.get());


    // Register uri
    const auto& uriView = std::make_shared<getit::gui::widget::UriView>(this);
    const auto& uriController = std::make_shared<getit::gui::widget::UriController>();
    this->registerView(uriController, uriView);
    this->ui->uriWidget->addWidget(uriView.get());
}

MainWindow::~MainWindow()
{
    delete this->ui;
}


void MainWindow::registerView(std::shared_ptr<getit::gui::BeforeWidgetController> controller, std::shared_ptr<QWidget> view)
{
    controller->registerView(view);
    request->registerPipeline(controller);
}

void MainWindow::connectSignals()
{
    this->connectSendSlot();
}

void MainWindow::connectSendSlot()
{
    connect(this, &MainWindow::requestSent, this, &MainWindow::setResponse);

    connect(ui->btnSend, &QPushButton::pressed,
            this, [=]() {
                // const auto& method = ui->cbMethod->currentText().toStdString();
                // const auto& uri = ui->textUri->text().toStdString();
                // const auto& request = factory->getRequest();

                // this->bodyWidget->addToRequest(request);
                // this->requestInfoWidget->addToRequest(request);
                // request->send();

                // request->send([=](getit::domain::Response* response) {
                //     emit requestSent(response);
                // });
            });
}

void MainWindow::setResponse(getit::domain::Response* response)
{
    // ui->listResponseHeaders->clear();
    // ui->textResponseBody->document()->setPlainText(response->body.c_str());

    // for (const auto& [header, value]: response->headers) {
    //     auto format = boost::format("%1% → %2%") % header % value;
    //     auto widget = new QListWidgetItem(ui->listResponseHeaders);

    //     widget->setText(format.str().c_str());
    // }

    // const auto& requestMethod = ui->cbMethod->currentText().toStdString();
    // const auto& uri = ui->textUri->text().toStdString();
    // const auto& requestMethodUri = requestMethod + " " + uri;
    // ui->lblRequestMethodUri->setText(requestMethodUri.c_str());
}
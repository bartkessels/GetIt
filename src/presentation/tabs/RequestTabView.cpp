#include "presentation/tabs/RequestTabView.hpp"
#include "./ui_RequestTabView.h"

using namespace getit::presentation::tabs;

RequestTabView::RequestTabView(std::shared_ptr<RequestTabImplementation> implementation, QWidget* parent):
    QWidget(parent),
    implementation(implementation),
    ui(new Ui::RequestTabView())
{
    ui->setupUi(this);
    this->injectImplementation(implementation);

    connect(ui->addCookie, &QPushButton::pressed,
            this, [this]() {
                this->addCookie("Cookie", "Value");
            });
    connect(ui->removeCookie, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedCookie();
            });

    connect(ui->addHeader, &QPushButton::pressed,
            this, [this]() {
                this->addHeader("Header", "Value");
            });
    connect(ui->removeHeader, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedHeader();
            });
}

RequestTabView::~RequestTabView()
{
    delete ui;
}

void RequestTabView::injectImplementation(const std::shared_ptr<RequestTabImplementation>& implementation)
{
    ui->injectable->addWidget(this->implementation.get());
}

std::shared_ptr<getit::domain::models::Request> RequestTabView::addToRequest(std::shared_ptr<getit::domain::models::Request> request)
{
    request->setMethod(this->getMethod());
    request->setUri(this->getUri());
    request->setHeaders(this->getHeaders());
    
    return this->implementation->addToRequest(request);
}

void RequestTabView::setResponse(const std::shared_ptr<getit::domain::models::Response>& response)
{
    this->setResponseHeaders(response->headers);
    this->setResponseBody(response->body);
}

void RequestTabView::setMethod(const std::string& method)
{
    ui->method->setCurrentText(QString::fromStdString(method).toUpper());
}

void RequestTabView::setUri(const std::string& uri)
{
    ui->uri->setText(QString::fromStdString(uri));
}

void RequestTabView::setHeaders(std::map<std::string, std::string> headers)
{
    for (const auto& [header, value] : headers) {
        this->addHeader(header, value);
    }
}

void RequestTabView::setCookies(std::map<std::string, std::string> cookies)
{
    for (const auto& [cookie, value] : cookies) {
        this->addCookie(cookie, value);
    }
}

void RequestTabView::setResponseHeaders(std::map<std::string, std::string> headers)
{
    ui->responseHeaders->clear();

    for (const auto& [header, value] : headers) {
        this->addResponseHeader(header, value);
    }
}

void RequestTabView::setResponseBody(std::string body)
{
    ui->responseBody->document()->setPlainText(QString::fromStdString(body));
}

void RequestTabView::addHeader(std::string header, std::string value)
{
    const auto& headerRow = new QTreeWidgetItem(ui->headers);

    headerRow->setText(keyIndex, QString::fromStdString(header));
    headerRow->setText(valueIndex, QString::fromStdString(value));
    headerRow->setFlags(treeItemFlag);
}

void RequestTabView::addResponseHeader(std::string header, std::string value)
{
    const auto& headerRow = new QTreeWidgetItem(ui->responseHeaders);

    headerRow->setText(keyIndex, QString::fromStdString(header));
    headerRow->setText(valueIndex, QString::fromStdString(value));
    headerRow->setFlags(treeItemFlag);
}

void RequestTabView::addCookie(std::string cookie, std::string value)
{
    const auto& cookieRow = new QTreeWidgetItem(ui->cookies);

    cookieRow->setText(keyIndex, QString::fromStdString(cookie));
    cookieRow->setText(valueIndex, QString::fromStdString(value));
    cookieRow->setFlags(treeItemFlag);
}

void RequestTabView::removeSelectedHeader()
{
    delete ui->headers->currentItem();
}

void RequestTabView::removeSelectedCookie()
{
    delete ui->cookies->currentItem();
}

std::string RequestTabView::getMethod()
{
    return ui->method->currentText().toStdString();
}

std::string RequestTabView::getUri()
{
    return ui->uri->text().toStdString();
}

std::map<std::string, std::string> RequestTabView::getHeaders()
{
    std::map<std::string, std::string> headers;

    for (int i = 0; i < ui->headers->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->headers->topLevelItem(i);

        headers.insert_or_assign(
            itm->text(keyIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        );
    }

    return headers;
}

std::map<std::string, std::string> RequestTabView::getCookies()
{
    std::map<std::string, std::string> cookies;

    for (int i = 0; i < ui->cookies->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->cookies->topLevelItem(i);

        cookies.insert_or_assign(
            itm->text(keyIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        );
    }

    return cookies;
}
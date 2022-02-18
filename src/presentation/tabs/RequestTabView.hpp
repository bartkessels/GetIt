#pragma once

#include <map>
#include <QComboBox>
#include <QString>
#include <QTreeWidgetItem>
#include <QWidget>
#include <string>

#include "presentation/tabs/RequestTabImplementation.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class RequestTabView; }
QT_END_NAMESPACE

namespace getit::presentation::tabs
{
    class RequestTabView: public QWidget
    {
        public:
            explicit RequestTabView(std::shared_ptr<RequestTabImplementation> implementation, QWidget* parent = nullptr);
            ~RequestTabView() override;

            std::shared_ptr<domain::models::Request> addToRequest(std::shared_ptr<domain::models::Request> request);
            void setResponse(const std::shared_ptr<domain::models::Response>& response);

            void setMethod(const std::string& method);
            void setUri(const std::string& uri);
            void setHeaders(std::map<std::string, std::string> headers);
            void setCookies(std::map<std::string, std::string> cookies);

            void setResponseHeaders(std::map<std::string, std::string> headers);
            void setResponseBody(std::string body);

            std::string getMethod();
            std::string getUri();
            std::map<std::string, std::string> getHeaders();
            std::map<std::string, std::string> getCookies();

        private:
            void injectImplementation(const std::shared_ptr<RequestTabImplementation>& implementation);

            void addHeader(std::string header, std::string value);
            void addResponseHeader(std::string header, std::string value);
            void addCookie(std::string cookie, std::string value);
            void removeSelectedHeader();
            void removeSelectedCookie();

            Ui::RequestTabView* ui;
            std::shared_ptr<RequestTabImplementation> implementation;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;
    };
}
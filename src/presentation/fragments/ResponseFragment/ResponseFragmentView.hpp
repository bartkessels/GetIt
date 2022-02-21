#pragma once

#include <map>
#include <string>
#include <QString>
#include <QTreeWidgetItem>
#include <QWidget>

#include "presentation/fragments/ResponseFragment/IResponseFragmentView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class ResponseFragmentView : public IResponseFragmentView, public QWidget
    {
        public:
            explicit ResponseFragmentView(QWidget* parent = nullptr);
            ~ResponseFragmentView() override;

            std::map<std::string, std::string> getHeaders() override;
            std::string getBody() override;

            void setHeaders(const std::map<std::string, std::string>& headers) override;
            void setBody(const std::string& body) override;

            void clearHeaders() override;

        private:
            Ui::ResponseFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addHeader(const std::string& header, const std::string& value);
    };
}
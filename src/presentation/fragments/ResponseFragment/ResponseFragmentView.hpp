#pragma once

#include <map>
#include <string>
#include <QString>
#include <QTreeWidgetItem>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class ResponseFragmentView : public QWidget
    {
        public:
            explicit ResponseFragmentView(QWidget* parent = nullptr);
            ~ResponseFragmentView() override;

            std::map<std::string, std::string> getHeaders();
            void setHeaders(const std::map<std::string, std::string>& headers);
            std::string getBody();
            void setBody(const std::string& body);

        private:
            Ui::ResponseFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addHeader(const std::string& header, const std::string& value);
    };
}
#pragma once

#include <map>
#include <memory>
#include <string>
#include <QPushButton>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HeadersView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class HeadersView: public QWidget
    {
        public:
            explicit HeadersView(QWidget* parent = nullptr);
            ~HeadersView();

            std::map<std::string, std::string> getHeaders();
            void setHeaders(std::map<std::string, std::string> headers);

        private:
            Ui::HeadersView* ui;

            const int headerIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags headerFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addHeader(std::string header, std::string value);
            void removeSelectedHeader();
    };
}
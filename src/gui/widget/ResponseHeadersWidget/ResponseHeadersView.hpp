#pragma once

#include <map>
#include <memory>
#include <string>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseHeadersView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class ResponseHeadersView: public QWidget
    {
        public:
            explicit ResponseHeadersView(QWidget* parent = nullptr);
            ~ResponseHeadersView();

            void setHeaders(std::map<std::string, std::string> headers);

        private:
            Ui::ResponseHeadersView* ui;

            const int headerIndex = 0;
            const int valueIndex = 1;

            void addHeader(std::string header, std::string value);
    };
}
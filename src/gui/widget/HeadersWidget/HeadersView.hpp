#pragma once

#include <list>
#include <memory>
#include <string>
#include <QPushButton>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QWidget>
#include <utility>

#include "gui/widget/HeadersWidget/IHeadersView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class HeadersView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class HeadersView: public QWidget, public IHeadersView
    {
        public:
            explicit HeadersView(QWidget* parent = nullptr);
            ~HeadersView();

            std::list<std::pair<std::string, std::string>> getHeaders() override;
            void setHeaders(std::list<std::pair<std::string, std::string>> headers) override;

        private:
            Ui::HeadersView* ui;

            const int headerIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags headerFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addHeader(std::string header, std::string value);
            void removeSelectedHeader();
    };
}
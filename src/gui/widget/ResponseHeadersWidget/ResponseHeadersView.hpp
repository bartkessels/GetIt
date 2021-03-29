#pragma once

#include <map>
#include <memory>
#include <string>
#include <QTreeWidgetItem>
#include <QWidget>

#include "gui/widget/ResponseHeadersWidget/IResponseHeadersView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseHeadersView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class ResponseHeadersView: public QWidget, public IResponseHeadersView
    {
        public:
            explicit ResponseHeadersView(QWidget* parent = nullptr);
            ~ResponseHeadersView() override;

            void setHeaders(std::map<std::string, std::string> headers) override;

        private:
            Ui::ResponseHeadersView* ui;

            const int headerIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags headerFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addHeader(std::string header, std::string value);
    };
}
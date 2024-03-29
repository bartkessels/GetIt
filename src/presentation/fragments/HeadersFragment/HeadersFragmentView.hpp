#pragma once

#include <map>
#include <string>
#include <QPushButton>
#include <QTreeWidgetItem>
#include <QWidget>

#include "presentation/fragments/HeadersFragment/IHeadersFragmentView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class HeadersFragmentView; }
QT_END_NAMESPACE

namespace getit::presentation::fragments
{
    class HeadersFragmentView : public IHeadersFragmentView, public QWidget
    {
        public:
            explicit HeadersFragmentView(QWidget* parent = nullptr);
            ~HeadersFragmentView() override;

            std::map<std::string, std::string> getHeaders() override;
            void setHeaders(const std::map<std::string, std::string>& headers) override;

        private:
            Ui::HeadersFragmentView* ui;

            const int keyIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags treeItemFlag = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addDefaultHeader();
            void addHeader(const std::string& header, const std::string& value);
            void removeSelectedHeader();
    };
}
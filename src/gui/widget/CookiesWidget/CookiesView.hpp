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

#include "gui/widget/CookiesWidget/ICookiesView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class CookiesView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class CookiesView: public QWidget, public ICookiesView
    {
        public:
            explicit CookiesView(QWidget* parent = nullptr);
            ~CookiesView() override;

            std::list<std::pair<std::string, std::string>> getCookies() override;
            void setCookies(std::list<std::pair<std::string, std::string>> cookies) override;

        private:
            Ui::CookiesView* ui;

            const int cookieIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags cookieFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addCookie(std::string cookie, std::string value);
            void removeSelectedCookie();
    };
}
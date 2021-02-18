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
namespace Ui { class CookiesView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class CookiesView: public QWidget
    {
        public:
            explicit CookiesView(QWidget* parent = nullptr);
            ~CookiesView();

            std::map<std::string, std::string> getCookies();
            void setCookies(std::map<std::string, std::string> cookies);

        private:
            Ui::CookiesView* ui;

            const int cookieIndex = 0;
            const int valueIndex = 1;
            const Qt::ItemFlags cookieFlags = Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable | Qt::ItemIsEnabled;

            void addCookie(std::string cookie, std::string value);
            void removeSelectedCookie();
    };
}
#include "gui/widget/CookiesWidget/CookiesView.hpp"
#include "./ui_CookiesView.h"

using namespace getit::gui::widget;

CookiesView::CookiesView(QWidget* parent):
    QWidget(parent),
    ui(new Ui::CookiesView())
{
    ui->setupUi(this);

    connect(ui->btnAddCookie, &QPushButton::pressed,
            this, [this]() {
                this->addCookie("Cookie", "Value");
            });
    connect(ui->btnRemoveCookie, &QPushButton::pressed,
            this, [this]() {
                this->removeSelectedCookie();
            });
}

CookiesView::~CookiesView()
{
    delete ui;
}

std::list<std::pair<std::string, std::string>> CookiesView::getCookies()
{
    std::list<std::pair<std::string, std::string>> cookies;

    for (int i = 0; i < ui->treeCookies->topLevelItemCount(); ++i) {
        QTreeWidgetItem* itm = ui->treeCookies->topLevelItem(i);

        cookies.push_back({
            itm->text(cookieIndex).toStdString(),
            itm->text(valueIndex).toStdString()
        });
    }

    return cookies;
}

void CookiesView::setCookies(std::list<std::pair<std::string, std::string>> cookies)
{
    for (const auto& [cookie, value] : cookies) {
        this->addCookie(cookie, value);
    }
}

void CookiesView::addCookie(std::string cookie, std::string value)
{
    const auto& cookieRow = new QTreeWidgetItem(ui->treeCookies);

    cookieRow->setText(cookieIndex, QString::fromStdString(cookie));
    cookieRow->setText(valueIndex, QString::fromStdString(value));
    cookieRow->setFlags(cookieFlags);
}

void CookiesView::removeSelectedCookie()
{
    delete ui->treeCookies->currentItem();
}
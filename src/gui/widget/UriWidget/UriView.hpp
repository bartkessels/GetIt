#pragma once

#include <string>
#include <QString>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class UriView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class UriView: public QWidget
    {
        public:
            explicit UriView(QWidget* parent = nullptr);
            ~UriView();

            std::string getUri();
            void setUri(std::string uri);

        private:
            Ui::UriView* ui;
    };
}
#pragma once

#include <string>
#include <QString>
#include <QWidget>

#include "gui/widget/UriWidget/IUriView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class UriView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class UriView: public QWidget, public IUriView
    {
        public:
            explicit UriView(QWidget* parent = nullptr);
            ~UriView() override;

            std::string getUri() override;
            void setUri(std::string uri) override;

        private:
            Ui::UriView* ui;
    };
}
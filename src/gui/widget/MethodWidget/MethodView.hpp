#pragma once

#include <memory>
#include <string>
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MethodView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class MethodView: public QWidget
    {
        public:
            MethodView(QWidget* parent = nullptr);
            ~MethodView();

            std::string getMethod();

        private:
            Ui::MethodView* ui;
    };
}
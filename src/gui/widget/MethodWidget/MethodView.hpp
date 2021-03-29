#pragma once

#include <memory>
#include <string>
#include <QWidget>

#include "gui/widget/MethodWidget/IMethodView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MethodView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class MethodView: public QWidget, public IMethodView
    {
        public:
            explicit MethodView(QWidget* parent = nullptr);
            ~MethodView() override;

            std::string getMethod() override;
            void setMethod(std::string method) override;

        private:
            Ui::MethodView* ui;
    };
}
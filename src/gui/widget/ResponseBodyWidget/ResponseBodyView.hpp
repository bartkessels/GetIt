#pragma once

#include <QString>
#include <QWidget>
#include <string>

#include "domain/AfterRequestPipeline.hpp"
#include "domain/Response.hpp"
#include "gui/widget/ResponseBodyWidget/IResponseBodyView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class ResponseBodyView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class ResponseBodyView: public QWidget, public IResponseBodyView
    {
        public:
            explicit ResponseBodyView(QWidget* parent = nullptr);
            ~ResponseBodyView() override;

            void addResponseBodyTab(QWidget* tab, std::string name) override;

        private:
            Ui::ResponseBodyView* ui;
    };
}
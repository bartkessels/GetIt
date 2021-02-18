#pragma once

#include <memory>
#include <QWidget>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestData.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class UriWidget; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class UriWidget: public QWidget, public getit::domain::BeforeRequestPipeline
    {
        public:
            explicit UriWidget(QWidget* parent = nullptr);
            ~UriWidget() override;

            void executeBeforeRequest(std::shared_ptr<getit::domain::RequestData> data) override;

        private:
            Ui::UriWidget* ui;
    };
}
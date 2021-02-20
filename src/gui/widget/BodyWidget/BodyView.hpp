#pragma once

#include <list>
#include <map>
#include <memory>
#include <QString>
#include <QWidget>

#include "domain/BeforeRequestPipeline.hpp"
#include "domain/RequestBody.hpp"
#include "gui/widget/BodyWidget/IBodyView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class BodyView; }
QT_END_NAMESPACE

namespace getit::gui::widget
{
    class BodyView: public QWidget, public IBodyView
    {
        public:
            explicit BodyView(QWidget* parent = nullptr);
            ~BodyView();

            void addBodyTab(QWidget* tab, std::string name) override;
            int getSelectedTabIndex() override;

        private:
            Ui::BodyView* ui;
    };
}
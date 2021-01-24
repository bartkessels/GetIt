#pragma once

#include <memory>
#include <QWidget>

#include "domain/BeforeRequestPipeline.hpp"

namespace getit::gui
{
    struct BeforeWidgetController: public getit::domain::BeforeRequestPipeline
    {
        public:
            ~BeforeWidgetController() = default;

            void registerView(std::shared_ptr<QWidget> view) {
                this->view = view;
            }

            template<class T>
            std::shared_ptr<T> getView() {
                return std::static_pointer_cast<T>(view);
            }

        private:
            std::shared_ptr<QWidget> view;
    };
}
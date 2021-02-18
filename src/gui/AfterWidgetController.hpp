#pragma once

#include <memory>
#include <QWidget>

#include "domain/AfterRequestPipeline.hpp"

namespace getit::gui
{
    struct AfterWidgetController: public getit::domain::AfterRequestPipeline
    {
        public:
            ~AfterWidgetController() = default;

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
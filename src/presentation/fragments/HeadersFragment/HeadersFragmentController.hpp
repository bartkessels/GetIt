#pragma once

#include <memory>

#include "presentation/fragments/HeadersFragment/HeadersFragmentModel.hpp"
#include "presentation/fragments/HeadersFragment/HeadersFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class HeadersFragmentController : public FragmentController<HeadersFragmentModel>
    {
        public:
            explicit HeadersFragmentController(HeadersFragmentView* view);
            ~HeadersFragmentController() override;

            std::shared_ptr<HeadersFragmentModel> getContent() override;
            void setContent(std::shared_ptr<HeadersFragmentModel> content) override;

        private:
            HeadersFragmentView* view;
    };
}
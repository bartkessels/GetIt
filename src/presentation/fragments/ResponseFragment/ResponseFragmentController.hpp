#pragma once

#include <memory>

#include "presentation/fragments/ResponseFragment/ResponseFragmentModel.hpp"
#include "presentation/fragments/ResponseFragment/ResponseFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class ResponseFragmentController : public FragmentController<ResponseFragmentModel>
    {
        public:
            explicit ResponseFragmentController(ResponseFragmentView* view);
            ~ResponseFragmentController() override;

            std::shared_ptr<ResponseFragmentModel> getContent() override;
            void setContent(std::shared_ptr<ResponseFragmentModel> content) override;

        private:
            ResponseFragmentView* view;
    };
}
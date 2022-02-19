#pragma once

#include <memory>

#include "domain/models/Request.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentModel.hpp"
#include "presentation/fragments/BodyFragment/BodyFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class BodyFragmentController : public FragmentController<BodyFragmentModel>
    {
        public:
            explicit BodyFragmentController(BodyFragmentView* view);
            ~BodyFragmentController() override;

            std::shared_ptr<BodyFragmentModel> getContent() override;
            void setContent(std::shared_ptr<BodyFragmentModel> content) override;

        private:
            BodyFragmentView* view;
    };
}
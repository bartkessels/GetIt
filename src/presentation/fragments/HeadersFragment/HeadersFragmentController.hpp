#pragma once

#include <map>
#include <memory>
#include <string>

#include "presentation/fragments/HeadersFragment/IHeadersFragmentView.hpp"
#include "presentation/fragments/FragmentController.hpp"

namespace getit::presentation::fragments
{
    class HeadersFragmentController : public FragmentController<std::map<std::string, std::string>>
    {
        public:
            explicit HeadersFragmentController(IHeadersFragmentView* view);
            ~HeadersFragmentController() override;

            std::map<std::string, std::string> getContent() override;
            void setContent(std::map<std::string, std::string> content) override;

        private:
            IHeadersFragmentView* view;
    };
}
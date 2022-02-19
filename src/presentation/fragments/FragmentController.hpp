#pragma once

#include <memory>

namespace getit::presentation::fragments
{
    template<class M>
    struct FragmentController
    {
        public:
            virtual ~FragmentController() = default;

            virtual std::shared_ptr<M> getContent() = 0;
            virtual void setContent(std::shared_ptr<M> content) = 0;
    };
}
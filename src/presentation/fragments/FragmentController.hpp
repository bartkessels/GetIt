#pragma once

#include <memory>

namespace getit::presentation::fragments
{
    template<class M>
    struct FragmentController
    {
        public:
            virtual ~FragmentController() = default;

            virtual M getContent() = 0;
            virtual void setContent(M content) = 0;
    };
}
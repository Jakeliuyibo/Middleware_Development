#pragma once

namespace utility
{

    template <class T, typename R = void>
    class Visitor
    {
        public:
            typedef T ParamType;
            typedef R RetutnType;

        public:
            Visitor() {}
            virtual ~Visitor() {}
            virtual RetutnType Visit(ParamType &) = 0;
    };


}


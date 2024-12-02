#ifndef BASIC_TYPES_HPP
#define BASIC_TYPES_HPP

namespace GLProject1::GLWraps {
    template <typename T>
    struct Triple {
        T m1;
        T m2;
        T m3;
    };

    using glw_handle_t = unsigned int;
    using PositionVertex = Triple<float>;
}

#endif
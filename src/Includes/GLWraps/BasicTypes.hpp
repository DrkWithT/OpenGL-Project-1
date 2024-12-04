#ifndef BASIC_TYPES_HPP
#define BASIC_TYPES_HPP

namespace GLProject1::GLWraps {
    template <typename T>
    struct Triple {
        T m1;
        T m2;
        T m3;
    };

    enum class UniformDataType {
        data_signed_int,
        data_unsigned_int,
        data_float,
    };

    using glw_handle_t = unsigned int;
    using glw_uniform_handle_t = int;
    using PositionVertex = Triple<float>;
}

#endif
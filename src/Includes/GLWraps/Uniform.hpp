#ifndef UNIFORM_HPP
#define UNIFORM_HPP

#include <type_traits>
#include "GLAD3/glad.h"

#include "GLWraps/BasicTypes.hpp"

namespace GLProject1::GLWraps {
    template <UniformDataType Dt>
    struct uniformtype_to_native {};

    template <>
    struct uniformtype_to_native<UniformDataType::data_signed_int> {
        using type = int;        
    };

    template <>
    struct uniformtype_to_native<UniformDataType::data_unsigned_int> {
        using type = unsigned int;
    };

    template <>
    struct uniformtype_to_native<UniformDataType::data_float> {
        using type = float;
    };

    template <UniformDataType Dt, std::size_t N> requires (N <= 4)
    struct UniformFuncs {
        using item_t = uniformtype_to_native<Dt>::type;
        /// NOTE: There is no variadic unpacking of aggregates, etc. so here's my lazy solution...

        /// @brief Updates the uniform if 1 valued by that of a native type.
        template <typename Nt> requires (std::is_same_v<Nt, item_t>)
        static void updateData(glw_uniform_handle_t handle, Nt v0) {
            if constexpr (N != 1) {
                return;
            }

            if constexpr (std::is_same_v<Nt, int>) {
                glUniform1i(handle, v0);
            } else if constexpr (std::is_same_v<Nt, unsigned int>) {
                glUniform1u(handle, v0);
            } else if constexpr (std::is_same_v<Nt, float>) {
                glUniform1f(handle, v0);
            }
        }

        /// @brief Updates the uniform if 2 valued by that of a native type.
        template <typename Nt> requires (std::is_same_v<Nt, item_t>)
        static void updateData(glw_uniform_handle_t handle, Nt v0, Nt v1) {
            if constexpr (N != 2) {
                return;
            }

            if constexpr (std::is_same_v<Nt, int>) {
                glUniform2i(handle, v0, v1);
            } else if constexpr (std::is_same_v<Nt, unsigned int>) {
                glUniform2u(handle, v0, v1);
            } else if constexpr (std::is_same_v<Nt, float>) {
                glUniform2f(handle, v0, v1);
            }
        }

        /// @brief Updates the uniform if 3 valued by that of a native type.
        template <typename Nt> requires (std::is_same_v<Nt, item_t>)
        static void updateData(glw_uniform_handle_t handle, Nt v0, Nt v1, Nt v2) {
            if constexpr (N != 3) {
                return;
            }

            if constexpr (std::is_same_v<Nt, int>) {
                glUniform3i(handle, v0, v1, v2);
            } else if constexpr (std::is_same_v<Nt, unsigned int>) {
                glUniform3u(handle, v0, v1, v2);
            } else if constexpr (std::is_same_v<Nt, float>) {
                glUniform3f(handle, v0, v1, v2);
            }
        }

        /// @brief Updates the uniform if 4 valued by that of a native type.
        template <typename Nt> requires (std::is_same_v<Nt, item_t>)
        static void updateData(glw_uniform_handle_t handle, Nt v0, Nt v1, Nt v2, Nt v3) {
            if constexpr (N != 4) {
                return;
            }

            if constexpr (std::is_same_v<Nt, int>) {
                glUniform4i(handle, v0, v1, v2, v3);
            } else if constexpr (std::is_same_v<Nt, unsigned int>) {
                glUniform4u(handle, v0, v1, v2, v3);
            } else if constexpr (std::is_same_v<Nt, float>) {
                glUniform4f(handle, v0, v1, v2, v3);
            }
        }
    };

    using RGBUniform = UniformFuncs<UniformDataType::data_float, 3>;
}

#endif
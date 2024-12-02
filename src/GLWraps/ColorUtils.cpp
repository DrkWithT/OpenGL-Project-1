/**
 * @file ColorUtils.cpp
 * @author DrkWithT
 * @brief TBA
 * @date 2024-11-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "GLWraps/ColorUtils.hpp"

namespace GLProject1::GLWraps {
    static constexpr auto max_rgb_component = 255.0f;
    static constexpr ScaledRGBColor whitesmoke_shade {240.0f, 240.0f, 240.0f};
    static constexpr ScaledRGBColor gray_shade {140.0f, 140.0f, 140.0f};
    static constexpr ScaledRGBColor black_shade {0.0f, 0.0f, 0.0f};

    ScaledRGBColor getPredefinedShade(ShadeOpt opt) noexcept {
        switch (opt) {
            case ShadeOpt::whitesmoke:
                return whitesmoke_shade;
            case ShadeOpt::gray:
                return gray_shade;
            case ShadeOpt::black:
            default:
                return black_shade;
        }
    }

    ScaledRGBColor toScaledRGB(const RGBColor& user_color) noexcept {
        const auto [red, green, blue] = user_color;

        return {
            red / max_rgb_component,
            green / max_rgb_component,
            blue / max_rgb_component
        };
    }
}
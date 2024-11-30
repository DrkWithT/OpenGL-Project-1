#ifndef COLOR_UTILS_HPP
#define COLOR_UTILS_HPP

namespace GLProject1::GLWraps {
    struct RGBColor {
        int r_component;
        int g_component;
        int b_component;
    };

    struct ScaledRGBColor {
        float r;
        float g;
        float b;
    };

    enum class ShadeOpt {
        whitesmoke,
        gray,
        black
    };

    [[nodiscard]] ScaledRGBColor getPredefinedShade(ShadeOpt opt) noexcept;

    [[nodiscard]] ScaledRGBColor toScaledRGB(RGBColor user_color) noexcept;
}

#endif
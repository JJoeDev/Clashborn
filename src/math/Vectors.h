#ifndef ARKADE_VECTORS_H
#define ARKADE_VECTORS_H

#include <cmath>
#include <raylib.h>
#include <ostream>

namespace ark::math {
    template<typename T>
    struct Vec2T final {
        Vec2T() = default;
        Vec2T(T X, T Y) : x(X), y(Y) {}
        explicit Vec2T(const Vector2& v) : x(v.x), y(v.y) {}

        T x{};
        T y{};

        constexpr operator Vector2() const noexcept {
            return Vector2{static_cast<float>(x), static_cast<float>(y)};
        }

        constexpr Vec2T& operator+=(const Vec2T& rhs) noexcept {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        constexpr Vec2T& Lerp(const Vec2T& target, float t) noexcept {
            x = (x * (1.0f - t)) + (target.x * t);
            y = (y * (1.0f - t)) + (target.y * t);
            return *this;
        }

        constexpr float Magnitude() const noexcept {
            return std::sqrt(x * x + y * y);
        }

        constexpr float MagnitudeCompare() const noexcept {
            return x * x + y * y;
        }

        constexpr Vec2T& Normalize() noexcept {
            float mag = Magnitude();
            if(mag > 0.0f) {
                x /= mag;
                y /= mag;
            }

            return *this;
        }

        constexpr Vec2T& operator-=(const Vec2T& rhs) noexcept {
            x -= rhs.x;
            y -= rhs.y;
            return *this;
        }

        constexpr Vec2T& operator*=(const Vec2T& rhs) noexcept {
            x *= rhs.x;
            y *= rhs.y;
            return *this;
        }

        constexpr Vec2T& operator*=(const float rhs) noexcept {
            x *= rhs;
            y *= rhs;
            return *this;
        }
    };

    using Vec2i = Vec2T<int>;
    using Vec2f = Vec2T<float>;

    inline Vec2f operator-(const Vec2f& rhs, const Vec2f& lhs) {
        return {rhs.x - lhs.x, rhs.y - lhs.y};
    }

    inline Vec2f operator+(const Vec2f& lhs, const Vec2f& rhs) {
        return {lhs.x + rhs.x, lhs.y + rhs.y};
    }

    inline Vec2f operator*(const Vec2f& lhs, const Vec2f& rhs) {
        return {lhs.x * rhs.x, lhs.y * rhs.y};
    }

    inline Vec2f operator*(const Vec2f& lhs, const float rhs) {
        return {lhs.x * rhs, lhs.y * rhs};
    }

    inline Vec2f operator*(const float lhs, const Vec2f& rhs) {
        return {lhs * rhs.x, lhs * rhs.y};
    }

    inline std::ostream& operator<<(std::ostream& os, const Vec2i& v) {
        os << "(X: " << v.x << ", Y: " << v.y << ")";
        return os;
    }

    inline std::ostream& operator<<(std::ostream& os, const Vec2f& v) {
        os << "(X: " << v.x << ", Y: " << v.y << ")";
        return os;
    }
}

#endif //ARKADE_VECTORS_H
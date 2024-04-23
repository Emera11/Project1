#pragma once
#include <stdio.h>
#include <math.h>

template<typename T>  //Template
struct Vector2D{
    T x;
    T y;

    //デフォルトコンストラクタ
    Vector2D() noexcept = default;
    constexpr Vector2D(const T& x, const T& y) noexcept : x(x), y(y) {};
    explicit constexpr Vector2D(const T& f) noexcept : x(f), y(f) {};

    //代入加算
    inline Vector2D operator+= (const Vector2D& v) noexcept {
        x += v.x;
        y += v.y;
        return *this;
    }

    //内積
    constexpr const float Dot(const Vector2D& v) const noexcept {
        return  (v.x * x) + (v.y * y);
    }

    //ベクトルの長さ
    const float Length() const {
        return sqrt(Dot(*this));
    }

    inline const Vector2D Normalize() const;
};

template<typename T> inline constexpr const Vector2D<T> operator+ (const Vector2D<T>& v1, const Vector2D<T>& v2) noexcept {
    return Vector2D<T>{ v1.x + v2.x, v1.y + v2.y };
}

//＝＝比較
template<typename T> inline bool operator== (const Vector2D<T>& v1, const Vector2D<T>& v2) noexcept {
    return (v1.x == v2.x) && (v1.y == v2.y);
}

//逆ベクトル
template<typename T> inline constexpr const Vector2D<T> operator- (const Vector2D<T>& v) noexcept {
    return Vector2D<T>(-v.x, -v.y);
}

//ベクトルの正規化
template<typename T> inline const Vector2D<T> Vector2D<T>::Normalize() const {
    return *this / Length();
}
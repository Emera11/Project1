#pragma once
#include <stdio.h>
#include <math.h>

template<typename T>  //Template
struct Vector2D{
    T x;
    T y;

    //�f�t�H���g�R���X�g���N�^
    Vector2D() noexcept = default;
    constexpr Vector2D(const T& x, const T& y) noexcept : x(x), y(y) {};
    explicit constexpr Vector2D(const T& f) noexcept : x(f), y(f) {};

    //������Z
    inline Vector2D operator+= (const Vector2D& v) noexcept {
        x += v.x;
        y += v.y;
        return *this;
    }

    //����
    constexpr const float Dot(const Vector2D& v) const noexcept {
        return  (v.x * x) + (v.y * y);
    }

    //�x�N�g���̒���
    const float Length() const {
        return sqrt(Dot(*this));
    }

    inline const Vector2D Normalize() const;
};

template<typename T> inline constexpr const Vector2D<T> operator+ (const Vector2D<T>& v1, const Vector2D<T>& v2) noexcept {
    return Vector2D<T>{ v1.x + v2.x, v1.y + v2.y };
}

//������r
template<typename T> inline bool operator== (const Vector2D<T>& v1, const Vector2D<T>& v2) noexcept {
    return (v1.x == v2.x) && (v1.y == v2.y);
}

//�t�x�N�g��
template<typename T> inline constexpr const Vector2D<T> operator- (const Vector2D<T>& v) noexcept {
    return Vector2D<T>(-v.x, -v.y);
}

//�x�N�g���̐��K��
template<typename T> inline const Vector2D<T> Vector2D<T>::Normalize() const {
    return *this / Length();
}
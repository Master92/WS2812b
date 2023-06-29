/*
 * WS2812b - An STM32 DMA-based PWM generator
 * Copyright (C) 2023  Nils Hofmann
 *
 * This file is part of WS2812b.
 *
 * WS2812b is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * WS2812b is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with WS2812b.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <stdexcept>

template<class T>
class Array {
public:
    struct Iterator {
        using iterator_category = std::forward_iterator_tag;
        using difference_type = std::ptrdiff_t;
        using value_type = T;
        using pointer = T*;  // or also value_type*
        using reference = T&;  // or also value_type&

        constexpr explicit Iterator(pointer ptr) : m_ptr(ptr) {}

        constexpr reference operator*() const { return *m_ptr; }

        constexpr pointer operator->() { return m_ptr; }

        // Prefix increment
        constexpr Iterator& operator++()
        {
            m_ptr++;
            return *this;
        }

        // Postfix increment
        constexpr Iterator operator++(int)
        {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        constexpr friend bool operator==(const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };

        constexpr friend bool operator!=(const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

    private:
        pointer m_ptr;
    };

    constexpr explicit Array(std::size_t count);
    virtual ~Array();

    constexpr auto size() const { return m_size; }

    constexpr auto operator[](size_t index) -> T& { return m_data[index]; }

    constexpr auto operator[](size_t index) const -> const T& { return m_data[index]; }

    constexpr auto begin() { return Iterator(m_data); }

    constexpr auto cbegin() const { return Iterator(m_data); }

    constexpr auto end() { return Iterator(&m_data[m_size]); }

    constexpr auto cend() const { return Iterator(&m_data[m_size]); }

    template<typename... Args>
    constexpr T& emplace_back(Args&& ... args);
    constexpr T& push_back(const T& other);

    template<typename... Args>
    constexpr void fill(size_t cnt, Args&& ... args);

    void resize(size_t cnt);

private:
    T* m_data;
    size_t m_size;
    size_t m_count{0};
};

template<class T>
constexpr T& Array<T>::push_back(const T& other)
{
    new(&m_data[m_count]) T(other);
    return m_data[m_count++];
}

template<class T>
template<typename... Args>
constexpr void Array<T>::fill(size_t cnt, Args&& ... args)
{
    for (auto i = m_count; i < cnt; i++) {
        emplace_back(args...);
    }
}

template<class T>
void Array<T>::resize(size_t cnt)
{
    for (auto i = m_count; i < cnt; i++) {
        emplace_back();
    }
}

template<class T>
template<typename... Args>
constexpr T& Array<T>::emplace_back(Args&& ... args)
{
    new(&m_data[m_count]) T(args...);

    return m_data[m_count++];
}

template<class T>
Array<T>::~Array()
{
    for (size_t i = 0; i < m_size; i++) {
        m_data[i].~T();
    }
    free(m_data);
}

template<class T>
constexpr Array<T>::Array(std::size_t count)
        : m_size(count)
{
    m_data = reinterpret_cast<T*>(std::malloc(m_size * sizeof(T)));
    resize(count);
}



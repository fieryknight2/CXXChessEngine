/****************************************************************************
* MIT License
 * Copyright (c) 2024 Matthew
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 * gui_object.h - Declarations for objects that can be drawn
 * @author Matthew Brown
 * @date 06/16/2024
 *****************************************************************************/
#pragma once

#include "SFML/Window/Event.hpp"

class Object
{
public:
    virtual ~Object() = default;
    Object() = default;

    virtual void destroy() = 0;
    virtual void render() = 0;
    virtual void update() = 0;
    virtual void processEvent(const sf::Event& event) = 0;

    void _render()
    {
        if (isVisible()) render();
    }

    void _update()
    {
        if (isActive()) update();
    }

    void setActive(const bool active)
    {
        m_isActive = active;
    }

    [[nodiscard]] bool isActive() const
    {
        return m_isActive;
    }

    void setVisible(const bool visible)
    {
        m_isVisible = visible;
    }

    [[nodiscard]] bool isVisible() const
    {
        return m_isVisible;
    }

private:
    bool m_isActive = true;
    bool m_isVisible = true;
};

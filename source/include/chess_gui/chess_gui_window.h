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
 * chess_gui_window.h - Declarations for a window with a GUI
 * @author Matthew Brown
 * @date 06/16/2024
 *****************************************************************************/
#pragma once

#include "SFML/Graphics/RenderWindow.hpp"
#include "imgui-SFML.h"
#include "chess_gui/gui_object.h"

#include <memory>
#include <chrono>
#include <utility>

namespace chessgui
{

struct WindowSettings
{
    WindowSettings() = default;

    WindowSettings(std::string title, const sf::Vector2i &windowSize,
                   const sf::ContextSettings &contextSettings) :
        title(std::move(title)), windowSize(windowSize), contextSettings(contextSettings)
    {
    }

    sf::Vector2i windowSize;
    std::string title;
    sf::ContextSettings contextSettings;
};

class ChessGuiWindow
{
public:
    explicit ChessGuiWindow(const WindowSettings &windowSettings);
    virtual ~ChessGuiWindow();

    bool processEvents();
    bool update();
    void render();

    virtual void createGui() = 0;

    void close();

    std::string getTitle() const
    {
        return m_windowSettings.title;
    }

    bool isClosed() const
    {
        return m_isClosed;
    }

private:
    sf::RenderWindow m_window;

    std::vector<std::unique_ptr<Object>> m_objects;
    sf::Clock m_clock;
    WindowSettings m_windowSettings;

    bool m_isClosed = false;
};

} // namespace chessgui

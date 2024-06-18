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
#include "chess_gui/gui_container.h"
#include "chess_gui/gui_inner_window.h"
#include "imgui-SFML.h"

#include <chrono>
#include <memory>
#include <utility>

namespace chessgui
{

struct WindowSettings
{
    WindowSettings() = default;

    WindowSettings(std::string title, const sf::Vector2i &windowSize, const sf::ContextSettings &contextSettings) :
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

    virtual bool processEvents();
    virtual bool update();
    virtual void render();

    virtual void createGui();

    void close();

    [[nodiscard]] std::string getTitle() const { return m_windowSettings.title; }
    [[nodiscard]] bool isClosed() const { return m_isClosed; }
    [[nodiscard]] WindowSettings getWindowSettings() const { return m_windowSettings; }

    std::shared_ptr<GuiInnerWindow> getWindow(uint32_t index) const
    {
        if (index < m_innerWindows.size())
            return m_innerWindows[index];
        return nullptr;
    }
    int getWindowCount() const { return static_cast<int>(m_innerWindows.size()); }
    void addWindow(const std::shared_ptr<GuiInnerWindow> &window) { m_innerWindows.push_back(window); }

protected:
    std::vector<std::shared_ptr<GuiInnerWindow>> m_innerWindows;
    bool m_isClosed = false;

    sf::Clock m_clock;
    WindowSettings m_windowSettings;

private:
    sf::RenderWindow m_window;
};

} // namespace chessgui

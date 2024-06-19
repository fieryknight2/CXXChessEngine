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
 * gui_inner_window.h - Declarations for an inner window
 * @author Matthew Brown
 * @date 06/18/2024
 *****************************************************************************/
#pragma once

#include <memory>
#include <vector>

#include "chess_gui/gui_container.h"
#include "chess_gui/gui_menubar.h"
#include "chess_gui/gui_object.h"

namespace chessgui
{

struct WindowState
{
    WindowState(bool open, const sf::Vector2i &size, bool minimized = false) :
        isOpen(open), isMinimized(minimized), size(size)
    {
    }

    bool isOpen = true;
    bool isMinimized = false;
    sf::Vector2i size;
};

class GuiInnerWindow
{
public:
    virtual ~GuiInnerWindow() = default;
    GuiInnerWindow() : m_name("Unnamed Window") {}
    explicit GuiInnerWindow(std::string name) : m_name(std::move(name)) {}

    virtual void createGui();

    [[nodiscard]] bool closed() const { return m_isClosed; }

    virtual void close();
    virtual void render();
    virtual void update(double deltaTime);
    virtual void processEvent(const sf::Event &event);

    void setName(const std::string &name) { m_name = name; }
    [[nodiscard]] const std::string &getName() const { return m_name; }

    void setState(const WindowState &state) { m_state = state; }
    [[nodiscard]] WindowState getState() const { return m_state; }

protected:
    std::shared_ptr<GuiContainer> m_root;
    std::vector<std::shared_ptr<GuiElement>> m_children;

    bool m_isClosed = false;
    int m_flags = 0;
    std::string m_name;
    std::shared_ptr<GuiMenuBar> m_menuBar = nullptr;
    WindowState m_state{true, sf::Vector2i(0, 0), false};
};

// TODO: Probably add this to a new file later
class GuiMainWindow final : public GuiInnerWindow
{
public:
    explicit GuiMainWindow() : GuiInnerWindow("Chess GUI") {}
    ~GuiMainWindow() override = default;

    void createGui() override;
};

} // namespace chessgui

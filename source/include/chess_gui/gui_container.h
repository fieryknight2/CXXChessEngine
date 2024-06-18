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
 * gui_object.h - Declarations for containters for ImGui
 * @author Matthew Brown
 * @date 06/16/2024
 *****************************************************************************/
#pragma once

#include "SFML/System/Vector2.hpp"
#include "chess_gui/gui_elements.h"

#include <memory>
#include <vector>

namespace chessgui
{

class GuiContainer : public GuiObject
{
public:
    explicit GuiContainer() : GuiObject() {}
    ~GuiContainer() override;

    void destroy() final;
    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

    void addChild(const std::shared_ptr<GuiObject> &child) { m_children.push_back(child); }
    void removeChild(const std::shared_ptr<GuiObject> &object)
    {
        if (auto child = std::ranges::find(m_children.begin(), m_children.end(), object); child != m_children.end())
        {
            m_children.erase(child);
        }
    }

    [[nodiscard]] const std::vector<std::shared_ptr<GuiObject>> &getChildren() const { return m_children; }

    [[nodiscard]] const sf::Vector2f &getPosition() const { return m_position; }
    [[nodiscard]] const sf::Vector2i &getSize() const { return m_size; }
    void setPosition(const sf::Vector2f &position) { m_position = position; }
    void setSize(const sf::Vector2i &size) { m_size = size; }

protected:
    std::vector<std::shared_ptr<GuiObject>> m_children;
    sf::Vector2f m_position{0, 0};
    sf::Vector2i m_size{0, 0};
};

class GuiGrid final : public GuiContainer
{
public:
    explicit GuiGrid(int rows, int columns) : GuiContainer(), m_rows(rows), m_columns(columns) {}
    ~GuiGrid() override = default;

    void render() override;

    void setRows(int rows) { m_rows = rows; }
    void setColumns(int columns) { m_columns = columns; }

    [[nodiscard]] int getRows() const { return m_rows; }
    [[nodiscard]] int getColumns() const { return m_columns; }

private:
    int m_rows = 0;
    int m_columns = 0;
};

class GuiHBox final : public GuiContainer
{
public:
    explicit GuiHBox() = default;
    ~GuiHBox() override = default;

    void render() override;
};

class GuiVBox final : public GuiContainer
{
public:
    explicit GuiVBox() = default;
    ~GuiVBox() override = default;

    void render() override;
};

} // namespace chessgui

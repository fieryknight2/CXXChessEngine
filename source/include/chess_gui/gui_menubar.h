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
 * gui_menubar.h - Creation of the menu bar for the Chess GUI
 * @author Matthew Brown
 * @date 06/17/2024
 *****************************************************************************/
#pragma once

#include "chess_gui/gui_elements.h"

namespace chessgui
{

class GuiMenuBar : public GuiElement
{
public:
    explicit GuiMenuBar();
    ~GuiMenuBar() override = default;

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::MenuBar; }

    void destroy() override {}
    void render() override;
    void update(double deltaTime) override {}
    void processEvent(const sf::Event &event) override {}

    void setNewGame(bool newGame) { m_newGame = newGame; }
    void setOpenGame(bool openGame) { m_openGame = openGame; }
    void setSaveGame(bool saveGame) { m_saveGame = saveGame; }
    void setSaveGameAs(bool saveGameAs) { m_saveGameAs = saveGameAs; }
    void setExit(bool exit) { m_exit = exit; }

    [[nodiscard]] bool getNewGame() const { return m_newGame; }
    [[nodiscard]] bool getOpenGame() const { return m_openGame; }
    [[nodiscard]] bool getSaveGame() const { return m_saveGame; }
    [[nodiscard]] bool getSaveGameAs() const { return m_saveGameAs; }
    [[nodiscard]] bool getExit() const { return m_exit; }

private:
    bool m_newGame = false;
    bool m_openGame = false;
    bool m_saveGame = false;
    bool m_saveGameAs = false;
    bool m_exit = false;
};

} // namespace chessgui

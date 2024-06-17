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
 * chess_gui_main_window.h - Declarations for the main window
 * @author Matthew Brown
 * @date 06/16/2024
 *****************************************************************************/
#pragma once

#include "chess_gui/chess_gui_window.h"

constexpr int MAIN_WINDOW_WIDTH = 800;
constexpr int MAIN_WINDOW_HEIGHT = 600;
constexpr auto MAIN_WINDOW_TITLE = "Chess GUI Application";

namespace chessgui
{

class ChessGuiMainWindow final : public ChessGuiWindow
{
public:
    ChessGuiMainWindow() :
        ChessGuiWindow(
                WindowSettings(MAIN_WINDOW_TITLE, {MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT}, sf::ContextSettings()))
    {
    }

    ~ChessGuiMainWindow() override = default;

    void createGui() override;
};

} // namespace chessgui

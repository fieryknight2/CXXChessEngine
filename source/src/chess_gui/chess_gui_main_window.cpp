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
 * chess_gui_main_window.cpp - Main window for the Chess GUI
 * @author Matthew Brown
 * @date 6/16/2024
 *****************************************************************************/
#include "chess_gui/chess_gui_main_window.h"

#include "SFML/Window.hpp"
#include "imgui.h"
#include "simplelogger.hpp"

using namespace chessgui;

void ChessGuiMainWindow::createGui()
{
    SL_LOG_DEBUG("Initializing GUI for the Main Window");

    m_innerWindows.push_back(std::make_unique<GuiMainWindow>());
    m_innerWindows.back()->setName("Chess GUI");
    m_innerWindows.back()->createGui();
    m_innerWindows.back()->setState(WindowState(true,
                                                sf::Vector2i(static_cast<int>(m_windowSettings.windowSize.x),
                                                             static_cast<int>(m_windowSettings.windowSize.y)),
                                                false));

    // m_innerWindows.push_back(std::make_unique<GuiMainWindow>());
    // m_innerWindows.back()->setName("Chess 2");
    // m_innerWindows.back()->createGui();
    // m_innerWindows.back()->setState(WindowState(true,
    //                                             sf::Vector2i(static_cast<int>(m_windowSettings.windowSize.x),
    //                                                          static_cast<int>(m_windowSettings.windowSize.y)),
    //                                             false));
}

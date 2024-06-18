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
 * gui_menubar.cpp - Implementation of the menu bar for the Chess GUI
 * @author Matthew Brown
 * @date 6/17/2024
 *****************************************************************************/
#include "chess_gui/gui_menubar.h"

#include "imgui.h"

using namespace chessgui;

GuiMenuBar::GuiMenuBar() = default;

void GuiMenuBar::render()
{
    ImGui::BeginMenuBar();
    {
        if (ImGui::BeginMenu("Game"))
        {
            ImGui::MenuItem("New Game", nullptr, &m_newGame);
            ImGui::MenuItem("Open Game", nullptr, &m_openGame);
            ImGui::MenuItem("Save Game", nullptr, &m_saveGame);
            ImGui::MenuItem("Save Game As", nullptr, &m_saveGameAs);
            if (ImGui::MenuItem("Exit", nullptr, nullptr))
            {
                m_exit = true;
            }

            ImGui::EndMenu();
        }
    }
    ImGui::EndMenuBar();
}

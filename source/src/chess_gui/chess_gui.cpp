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
 * chess_gui.cpp - Implementation for ImGUI
 * @author Matthew Brown
 * @date 06/11/2024
 *****************************************************************************/
#include "chess_gui/chess_gui.h"
#include "chess_gui/gui_popup_window.h"
#include "simplelogger.hpp"

namespace chessgui
{

ChessGui::ChessGui() = default;

ChessGui::~ChessGui()
{
    if (!m_mainWindow.isClosed())
    {
        m_mainWindow.close();

    }

    ImGui::SFML::Shutdown();
}

bool ChessGui::run()
{
    SL_LOG_INFO("Starting Main Loop");
    m_mainWindow.createGui();

    while (true)
    {
        if (m_mainWindow.processEvents())
        {
            for (const auto &window: m_windows)
            {
                window->close();
            }

            return true;
        }
        m_mainWindow.update();
        m_mainWindow.render();

        for (const auto &window: m_windows)
        {
            window->processEvents();

            if (!window->isClosed())
            {
                window->update();
                window->render();
            }
        }


        if (const uint32_t count = std::erase_if(m_windows, [](const std::unique_ptr<ChessGuiWindow> &window)
        {
            return window->isClosed();
        }); count)
        {
            SL_LOG_DEBUG("Removed " + std::to_string(count) + " closed windows");
        }
    }
}

} // namespace chessgui

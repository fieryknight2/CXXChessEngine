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
 * chess_gui_window.cpp - Implementation for Chess GUI Window
 * @author Matthew Brown
 * @date 06/16/2024
 *****************************************************************************/
#include "chess_gui/chess_gui.h"

#include "imgui.h"

#include "SFML/Window.hpp"
#include "simplelogger.hpp"

using namespace chessgui;

ChessGuiWindow::ChessGuiWindow(const WindowSettings &windowSettings)
{
    SL_LOG_DEBUG("Opening Window " + windowSettings.title);
    m_window.create(sf::VideoMode(windowSettings.windowSize.x, windowSettings.windowSize.y), windowSettings.title,
                    sf::Style::Default, windowSettings.contextSettings);
    m_window.setFramerateLimit(120);

    if (!m_window.isOpen())
    {
        SL_LOG_FATAL("Failed to open window");
        return;
    }

    if (!ImGui::SFML::Init(m_window))
    {
        SL_LOG_FATAL("Failed to initialize ImGui and SFML");
        return;
    }

    m_windowSettings = windowSettings;
}

ChessGuiWindow::~ChessGuiWindow()
{
    if (m_window.isOpen())
    {
        m_window.close();
    }
}

void ChessGuiWindow::createGui()
{
    SL_LOG_DEBUG("Initializing GUI for window");
}

bool ChessGuiWindow::processEvents()
{
    sf::Event event{};
    while (m_window.pollEvent(event))
    {
        ImGui::SFML::SetCurrentWindow(m_window);
        ImGui::SFML::ProcessEvent(event);

        if (event.type == sf::Event::Closed)
        {
            close();
            return true;
        }

        for (const auto &object: m_objects)
        {
            object->processEvent(event);
        }
    }

    return false;
}

bool ChessGuiWindow::update()
{
    const sf::Time delta = m_clock.restart();
    ImGui::SFML::Update(m_window, delta);

    for (const auto &object: m_objects)
    {
        object->_update();
    }

    return false;
}

void ChessGuiWindow::render()
{
    m_window.clear();

    ImGui::SFML::SetCurrentWindow(m_window);

    for (const auto &object: m_objects)
    {
        object->_render();
    }

    ImGui::SFML::Render(m_window);

    m_window.display();
}

void ChessGuiWindow::close()
{
    SL_LOG_DEBUG("Closing window " + m_windowSettings.title);
    m_isClosed = true;

    for (const auto &object: m_objects)
    {
        object->destroy();
    }
    m_objects.clear(); // Unique pointers delete themselves

    m_window.close();
}

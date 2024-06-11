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

#include "SFML/Window.hpp"

using namespace chessgui;

ChessGui::ChessGui()
{
    m_window.create(sf::VideoMode(800, 600), "Chess GUI");

    ImGui::SFML::Init(m_window);
}

ChessGui::~ChessGui() {}

bool ChessGui::run()
{
    while (true)
    {
        sf::Event event;
        while (m_window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);

            if (event.type == sf::Event::Closed)
            {
                m_window.close();
                return true;
            }
        }

        // ImGui::SFML::Update(m_window, );

        m_window.clear();
        ImGui::SFML::Render(m_window);
        m_window.display();
    }
}

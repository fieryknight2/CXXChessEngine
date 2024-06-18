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
 * gui_container.cpp - Implementation for containers of Gui elements
 * @author Matthew Brown
 * @date 6/17/2024
 *****************************************************************************/
#include "chess_gui/gui_container.h"
#include "imgui.h"
#include "simplelogger.hpp"

namespace chessgui
{

GuiContainer::~GuiContainer()
{
    if (!m_children.empty())
    {
        destroy();
    }
}

void GuiContainer::destroy()
{
    for (const auto &child: m_children)
    {
        child->destroy();
    }
    m_children.clear();
}

void GuiContainer::render()
{
    // ImGui::BeginGroup();
    for (const auto &child: m_children)
    {
        child->render();
    }

    // ImGui::EndGroup();
}

void GuiContainer::update(double deltaTime)
{
    for (const auto &child: m_children)
    {
        child->update(deltaTime);
    }
}

void GuiContainer::processEvent(const sf::Event &event)
{
    for (const auto &child: m_children)
    {
        child->processEvent(event);
    }
}

void GuiGrid::render()
{
    SL_ASSERT_FALSE(m_columns == 0 or m_rows == 0 or m_columns > 511 or m_rows > 511, "GuiGrid: Invalid size");

    ImGui::BeginGroup();

    if (bool v = ImGui::BeginTable(("TableID" + std::to_string(m_id)).c_str(), m_columns); v)
    {
        for (int i = 0; i < m_rows; i++)
        {
            ImGui::TableNextRow();
            for (int j = 0; j < m_columns; j++)
            {
                ImGui::TableNextColumn();
                if (i * m_columns + j >= m_children.size())
                {
                    continue;
                }

                m_children[i * m_columns + j]->render();
            }
        }

        ImGui::EndTable();
    }

    ImGui::EndGroup();
}

void GuiHBox::render()
{
    if (m_children.empty())
    {
        return;
    }

    ImGui::BeginGroup();

    for (const auto &child: m_children)
    {
        child->render();
    }

    ImGui::EndGroup();
}

void GuiVBox::render()
{
    if (m_children.empty())
    {
        return;
    }

    ImGui::BeginGroup();

    for (const auto &child: m_children)
    {
        child->render();
    }

    ImGui::EndGroup();
}

} // namespace chessgui

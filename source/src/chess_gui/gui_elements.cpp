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
 * gui_elements.cpp - Implementation of the GUI elements
 * @author Matthew Brown
 * @date 6/16/2024
 *****************************************************************************/
#include "chess_gui/gui_elements.h"

#include <cstring>
#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

#include "simplelogger.hpp"

namespace chessgui
{
// Init outside of class
uint64_t GuiObject::s_idCounter = 0;

void GuiButton::render() { ImGui::Button(m_text.c_str()); }

void GuiButton::update(double deltaTime) {}

void GuiButton::processEvent(const sf::Event &event) {}

void GuiTextLine::render() { ImGui::Text(m_text.c_str()); }

void GuiTextLine::update(double deltaTime) {}

void GuiTextLine::processEvent(const sf::Event &event) {}

void GuiTextInput::render() { ImGui::InputText(("##" + std::to_string(m_id)).c_str(), &m_text); }

void GuiTextInput::update(double deltaTime) {}

void GuiTextInput::processEvent(const sf::Event &event) {}

void GuiCheckBox::render() { ImGui::Checkbox(m_text.c_str(), &m_checked); }

void GuiCheckBox::update(double deltaTime) {}

void GuiCheckBox::processEvent(const sf::Event &event) {}

void GuiSlider::render() { ImGui::SliderInt(("##" + std::to_string(m_id)).c_str(), &m_value, m_minValue, m_maxValue); }

void GuiSlider::update(double deltaTime) {}

void GuiSlider::processEvent(const sf::Event &event) {}

void GuiNumberSelector::render() { ImGui::InputInt(("##" + std::to_string(m_id)).c_str(), &m_value); }

void GuiNumberSelector::update(double deltaTime) {}

void GuiNumberSelector::processEvent(const sf::Event &event) {}

void GuiMultiSelect::render()
{
    if (m_options.empty())
    {
        return;
    }

    if (bool v = ImGui::BeginCombo(("##" + std::to_string(m_id)).c_str(), m_options[m_selected].c_str()); v)
    {
        for (uint32_t i = 0; i < m_options.size(); i++)
        {
            if (ImGui::Selectable(m_options[i].c_str(), m_selected == i))
            {
                m_selected = static_cast<int>(i);
            }
        }
        ImGui::EndCombo();
    }
}

void GuiMultiSelect::update(double deltaTime) {}

void GuiMultiSelect::processEvent(const sf::Event &event) {}

std::string GuiMultiSelect::getOption(uint32_t index) const
{
    if (index >= m_options.size())
    {
        return "";
    }

    return m_options[index];
}

void GuiMultiSelect::setOption(uint32_t index, const std::string &option)
{
    if (index >= m_options.size())
    {
        return;
    }

    m_options[index] = option;
}

} // namespace chessgui

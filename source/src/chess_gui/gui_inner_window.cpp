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
 * gui_inner_window.cpp - Implementation for inner windows for the Chess GUI
 * @author Matthew Brown
 * @date 6/18/2024
 *****************************************************************************/
#include "chess_gui/gui_inner_window.h"

#include "chess_gui/gui_menubar.h"
#include "imgui.h"
#include "simplelogger.hpp"

namespace chessgui
{
void GuiInnerWindow::createGui() { m_root = std::make_shared<GuiContainer>(); }

void GuiInnerWindow::close()
{
    if (m_state.isOpen)
    {
        m_state.isOpen = false;
    }

    m_isClosed = true;
}

void GuiInnerWindow::update(double deltaTime)
{
    SL_ASSERT_TRUE(m_root != nullptr, "Root container is null");

    m_root->_update(deltaTime);

    for (auto &child: m_children)
    {
        child->_update(deltaTime);
    }
}

void GuiInnerWindow::processEvent(const sf::Event &event)
{
    SL_ASSERT_TRUE(m_root != nullptr, "Root container is null");

    if (m_menuBar and m_menuBar->getExit())
    {
        close();
        return;
    }

    if (event.type == sf::Event::Resized)
    {
        m_state.size = sf::Vector2i(static_cast<int>(event.size.width), static_cast<int>(event.size.height));
    }
    else if (event.type == sf::Event::Closed)
    {
        close();
        return;
    }

    m_root->processEvent(event);

    for (auto &child: m_children)
    {
        child->processEvent(event);
    }
}

void GuiInnerWindow::render()
{
    SL_ASSERT_TRUE(m_root != nullptr, "Root container is null");

    m_root->setSize(m_state.size);

    ImGui::SetNextWindowSize(m_state.size);
    ImGui::SetNextWindowPos(sf::Vector2f(0, 0));
    if (ImGui::Begin(m_name.c_str(), nullptr, m_flags))
    {
        m_root->_render(); // Render the root container
        for (const auto &child: m_children)
        {
            child->_render();
        }
    }

    ImGui::End();
}

void GuiMainWindow::createGui()
{
    SL_LOG_DEBUG("Initializing GUI for the inner Main Window");

    m_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings |
              ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

    m_menuBar = std::make_shared<GuiMenuBar>();
    m_children.push_back(m_menuBar);

    // Create some stuff
    m_root = std::make_shared<GuiContainer>();
    m_root->setSize(sf::Vector2i(500, 500));

    auto hbox = std::make_shared<GuiHBox>();
    hbox->setSize(sf::Vector2i(200, 0));

    hbox->addChild(std::make_shared<GuiButton>("Test Button"));
    hbox->addChild(std::make_shared<GuiTextLine>("Test Text Line"));

    auto vbox = std::make_shared<GuiVBox>();
    vbox->setPosition(sf::Vector2f(100, 100));
    vbox->setSize(sf::Vector2i(400, 400));

    vbox->addChild(std::make_shared<GuiButton>("Test Button"));
    vbox->addChild(std::make_shared<GuiTextLine>("Test Text Line"));

    auto grid = std::make_shared<GuiGrid>(2, 3);
    grid->addChild(std::make_shared<GuiButton>("Grid A"));
    grid->addChild(std::make_shared<GuiTextLine>("Grid B"));

    grid->addChild(std::make_shared<GuiButton>("Grid C"));
    grid->addChild(std::make_shared<GuiTextLine>("Grid D"));
    grid->addChild(vbox);
    grid->addChild(hbox);

    m_root->addChild(std::make_shared<GuiButton>("Test Button"));
    m_root->addChild(std::make_shared<GuiTextLine>("Test Text Line"));
    m_root->addChild(std::make_shared<GuiTextInput>("Test Text Input"));
    m_root->addChild(std::make_shared<GuiCheckBox>("Test Check Box"));
    m_root->addChild(std::make_shared<GuiSlider>(0, 100));
    m_root->addChild(std::make_shared<GuiNumberSelector>());
    m_root->addChild(std::make_shared<GuiMultiSelect>(std::vector<std::string>{"Option 1", "Option 2", "Option 3"}));

    auto second = std::make_shared<GuiContainer>();
    second->addChild(std::make_shared<GuiButton>("Second Button"));
    second->addChild(std::make_shared<GuiTextLine>("Another Text Line"));
    second->addChild(std::make_shared<GuiTextLine>("Another Text Line"));

    m_root->addChild(grid);
    m_root->addChild(second);

    for (int i = 0; i < 100; i++)
    {
        m_root->addChild(std::make_shared<GuiTextLine>("Nonsense"));
    }
}

} // namespace chessgui

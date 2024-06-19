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
 * gui_elements.h - All the elements for GUI like buttons, text boxes, etc.
 * @author Matthew Brown
 * @date 06/17/2024
 *****************************************************************************/
#pragma once

#include <cstdint>
#include <utility>
#include <vector>

#include "chess_gui/gui_object.h"

namespace chessgui
{

enum class GuiElementType
{
    None,
    Button,
    TextLine,
    TextInput,
    CheckBox,
    Slider,
    NumberSelector,
    MultiSelect,
    MenuBar,
    Other,
    GuiContainer,
    GridContainer,
    HBoxContainer,
    VBoxContainer,
};

class GuiElement : public GuiObject
{
public:
    [[nodiscard]] virtual GuiElementType getType() const { return GuiElementType::None; }
};

class GuiButton : public GuiElement
{
public:
    explicit GuiButton(std::string text) : GuiElement(), m_text(std::move(text)) {}

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::Button; }

    void destroy() override {}
    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

    [[nodiscard]] std::string getText() const { return m_text; }
    void setText(const std::string &text) { m_text = text; }

    [[nodiscard]] bool isClicked() const { return m_clicked; }

protected:
    std::string m_text;
    bool m_clicked = false;
};

class GuiTextLine : public GuiElement
{
public:
    explicit GuiTextLine(std::string text) : GuiElement(), m_text(std::move(text)) {}
    GuiTextLine() = default;

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::TextLine; }

    void destroy() override {}
    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

    [[nodiscard]] std::string getText() const { return m_text; }
    void setText(const std::string &text) { m_text = text; }

protected:
    std::string m_text;
};

class GuiTextInput final : public GuiTextLine
{
public:
    explicit GuiTextInput(std::string text) : GuiTextLine(std::move(text)) {}

    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;
};

class GuiCheckBox : public GuiButton
{
public:
    explicit GuiCheckBox(const std::string &text, bool checked = false) : GuiButton(text), m_checked(checked) {}

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::CheckBox; }

    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

private:
    bool m_checked = false;
};

class GuiSlider : public GuiElement
{
public:
    explicit GuiSlider(int minValue, int maxValue) : GuiElement(), m_minValue(minValue), m_maxValue(maxValue) {}
    GuiSlider() = default;

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::Slider; }

    void destroy() override {}
    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

    [[nodiscard]] int getValue() const { return m_value; }
    void setValue(int value) { m_value = value; }

    [[nodiscard]] int getMinValue() const { return m_minValue; }
    void setMinValue(int minValue) { m_minValue = minValue; }

    [[nodiscard]] int getMaxValue() const { return m_maxValue; }
    void setMaxValue(int maxValue) { m_maxValue = maxValue; }

protected:
    int m_minValue = 0;
    int m_maxValue = 100;
    int m_value = 0;
};

class GuiNumberSelector final : public GuiSlider
{
public:
    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::NumberSelector; }

    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;
};

class GuiMultiSelect final : public GuiElement
{
public:
    explicit GuiMultiSelect(const std::vector<std::string> &options) : GuiElement(), m_options(options) {}

    [[nodiscard]] GuiElementType getType() const override { return GuiElementType::MultiSelect; }

    void destroy() override {}
    void render() override;
    void update(double deltaTime) override;
    void processEvent(const sf::Event &event) override;

    [[nodiscard]] int getOptionCount() const { return static_cast<int>(m_options.size()); }
    [[nodiscard]] const std::vector<std::string> &getOptions() const { return m_options; }
    [[nodiscard]] std::string getOption(uint32_t index) const;

    void setOptions(const std::vector<std::string> &options) { m_options = options; }
    void setOption(uint32_t index, const std::string &option);
    void addOption(const std::string &option) { m_options.push_back(option); }

    [[nodiscard]] int getSelected() const { return m_selected; }
    void select(int selected) { m_selected = selected; }

private:
    std::vector<std::string> m_options;
    bool m_dropDownOpen = false;
    int m_selected = 0;
};

} // namespace chessgui

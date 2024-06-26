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
 * gui_main.cpp - Main entry point for ChessGUI application
 * @author Matthew Brown
 * @date 6/10/2024
 *****************************************************************************/
#include <iostream>

#include "chess_gui/chess_gui.h"
#include "simplelogger.hpp"

int main(const int argc, char *argv[])
{
    // Enable file loggers
    SL_CAPTURE_EXCEPTIONS();
    SIMPLE_LOGGER_LOG_VERSION_INFO();
    SL_LOG_VERSION_INFO("ChessGUI", "0.0.1");
    SL_LOG_TO_FILE("chess_gui.log", slog::LogFileMode::OVERWRITE);
    SL_LOG_TO_FILE("chess_gui_debug.log", slog::LogFileMode::OVERWRITE);
    slog::SimpleLogger::GlobalLogger()->getLogger(2)->setMinLogLevel(slog::LogLevel::DEBUG);

    SL_LOG_INFO("Started running ChessGUI");

    // Run the program
    chessgui::ChessGui chessGui;
    chessGui.run();

    SL_LOG_INFO("Finished running");
    return 0;
}

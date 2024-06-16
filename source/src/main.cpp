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
 * Main.cpp - The main entry point for the program
 * @author Matthew Brown
 * @date 5/21/2024
 *****************************************************************************/
#include <iostream>

#include "simplelogger.hpp"

int main(const int argc, char *argv[])
{
    SL_CAPTURE_EXCEPTIONS();

    // File loggers
    SL_LOG_TO_FILE("chess_engine_debug.log", slog::LogFileMode::OVERWRITE);
    slog::SimpleLogger::GlobalLogger()->getLogger(1)->setMinLogLevel(slog::LogLevel::DEBUG);

    SL_LOG_TO_FILE("chess_engine.log", slog::LogFileMode::OVERWRITE);

    // Opening information
    SIMPLE_LOGGER_LOG_VERSION_INFO();
    SL_LOG_VERSION_INFO("Chess Engine", "0.0.1");
    SL_LOG_INFO("Welcome to the Chess Engine!");
    SL_LOG_INFO("This engine is licensed under the MIT License: https://en.wikipedia.org/wiki/MIT_License");
    for (int i = 0; i < argc; ++i)
    {
        SL_LOG_DEBUG("Argument [" + std::to_string(i) + std::string("] is ") + argv[i]);
    }

    // Run the engine...

    SL_LOG_DEBUG("Finished running the Chess Engine");
    return 0; // Not necessary, just looks cleaner to me
}

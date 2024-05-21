# ChessEngine

A chess engine written in classic C++, I originally started writing this
program in Python, but I decided to rewrite in C++ because it will
run significantly faster than Python.

## Build

To build the program, you will need to have a C++ compiler installed, CMake
installed and a program such as Visual Studio, Make or Ninja installed.

### Windows

1. Open a command prompt and navigate to the directory containing the
   `CMakeLists.txt` file.
2. Run the following command to generate the Visual Studio solution:

   ```powershell
   mkdir build
   cd build
   cmake ..
   ```

3. Open the `build\ChessEngine.sln` file in Visual Studio and build the
   solution.

### Linux

1. Open a terminal and navigate to the directory containing the
   `CMakeLists.txt` file.
2. Run the following command to generate the Makefile:
   ```bash
   mkdir build && cd build
   cmake ..
   make -j8
   ```

## Usage

To run the program, simply execute the `ChessEngine` or `ChessEngine.exe` executable file.

```bash
./chess_engine
```

The program will prompt the user to enter a move, and then it will
display the resulting position.

## License

This program is licensed under the MIT License. See the [LICENSE](LICENSE) file
for more information.

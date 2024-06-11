# Source for file: https://github.com/eliasdaler/cmake-fetchcontent-tutorial-code
include(FetchContent)

# SFML
FetchContent_Declare(
        sfml
        URL https://github.com/SFML/SFML/archive/refs/tags/2.6.1.zip
)
FetchContent_MakeAvailable(sfml)
add_subdirectory(sfml)

# Dear ImGui
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG 6f7b5d0ee2fe9948ab871a530888a6dc5c960700  # 1.90.8
)

FetchContent_MakeAvailable(imgui)

FetchContent_Declare(
        imgui-sfml
        GIT_REPOSITORY https://github.com/SFML/imgui-sfml.git
        GIT_TAG de565ac8f2b795dedc0307b60830cb006afd2ecd # 2.6
)
FetchContent_MakeAvailable(imgui-sfml)
add_subdirectory(imgui-sfml)
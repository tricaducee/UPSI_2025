cmake_minimum_required(VERSION 3.25)
project(UPSI_Game LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

if(EMSCRIPTEN)
    message(STATUS "Compilation pour WebAssembly (Emscripten)")
    add_executable(UPSI_Game main.c)

    include(FetchContent)
    FetchContent_Declare(SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG main
    )
    FetchContent_MakeAvailable(SDL3)

    target_link_libraries(UPSI_Game PRIVATE SDL3-static)

    # Génère explicitement un fichier index.html
    set_target_properties(UPSI_Game PROPERTIES 
        OUTPUT_NAME "index"
        SUFFIX ".html"
    )

    # Options Emscripten nécessaires
    target_link_options(UPSI_Game PRIVATE
        "SHELL:-sUSE_WEBGL2=1"
        "SHELL:-sALLOW_MEMORY_GROWTH=1"
    )

else()
    find_package(SDL3 REQUIRED)
    add_executable(UPSI_Game main.c)

    if(APPLE)
        set_target_properties(UPSI_Game PROPERTIES MACOSX_BUNDLE TRUE)
    endif()

    target_link_libraries(UPSI_Game PRIVATE SDL3::SDL3)
endif()

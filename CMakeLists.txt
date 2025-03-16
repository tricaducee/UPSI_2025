cmake_minimum_required(VERSION 3.15)
project(WindowsWar C)

set(CMAKE_C_STANDARD 11)

file(GLOB SOURCES "src/*.c")
include_directories(includes)

add_executable(${PROJECT_NAME} ${SOURCES})

# Copie des assets
file(COPY ${CMAKE_SOURCE_DIR}/assets DESTINATION ${CMAKE_BINARY_DIR})

if(EMSCRIPTEN)
    message("🔧 Configuration Emscripten activée (SDL2 explicite)")

    set(CMAKE_EXECUTABLE_SUFFIX ".html")

    # Flags à la compilation (sans les formats)
    target_compile_options(${PROJECT_NAME} PRIVATE
        -sUSE_SDL=2
        -sUSE_SDL_IMAGE=2
        -sUSE_SDL_TTF=2
        -sUSE_SDL_MIXER=2
    )

    # Flags au linkage (retiré SDL2_IMAGE_FORMATS problématique)
    target_link_options(${PROJECT_NAME} PRIVATE
        -sUSE_SDL=2
        -sUSE_SDL_IMAGE=2
        -sUSE_SDL_TTF=2
        -sUSE_SDL_MIXER=2
        -sSDL2_MIXER_FORMATS='["mp3","ogg"]'
        -sALLOW_MEMORY_GROWTH=1
        --preload-file assets
    )

    # Inclusion explicite des headers SDL2 (recommandé)
    include_directories($ENV{EMSDK}/upstream/emscripten/cache/sysroot/include/SDL2)

else()
    message("🍎 Configuration macOS activée")

    include_directories(
        /opt/homebrew/include/SDL2
        /opt/homebrew/include
    )

    link_directories(/opt/homebrew/lib)

    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)

    find_library(SDL2_LIB SDL2 REQUIRED)
    find_library(SDL2_IMAGE_LIB SDL2_image REQUIRED)
    find_library(SDL2_TTF_LIB SDL2_ttf REQUIRED)
    find_library(SDL2_MIXER_LIB SDL2_mixer REQUIRED)

    target_link_libraries(${PROJECT_NAME}
        ${SDL2_LIB}
        ${SDL2_IMAGE_LIB}
        ${SDL2_TTF_LIB}
        ${SDL2_MIXER_LIB}
        ${COCOA_LIBRARY}
        ${IOKIT_LIBRARY}
        ${COREVIDEO_LIBRARY}
        m)

    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE TRUE
        MACOSX_BUNDLE_ICON_FILE "icon.icns"
        MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist
    )

    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/assets)
endif()

cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# SFML paths
set(SFML_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/Calculator/Assets/SFML/include)
set(SFML_LIB_DIR ${CMAKE_SOURCE_DIR}/Calculator/Assets/SFML/lib)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

# Sources
set(SRC_DIR ${CMAKE_SOURCE_DIR}/Calculator)
file(GLOB SOURCES "${SRC_DIR}/*.cpp")

add_executable(YinCulator ${SOURCES})

# Link SFML
target_link_libraries(YinCulator PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
    sfml-main
    flac
    freetype
    ogg
	oggd
    vorbis
    vorbisenc
    vorbisfile
)

# Copy DLLs (Windows only)
if(WIN32)
    add_custom_command(TARGET YinCulator POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${SRC_DIR}/sfml-graphics-3.dll
            ${SRC_DIR}/sfml-window-3.dll
            ${SRC_DIR}/sfml-system-3.dll
            $<TARGET_FILE_DIR:YinCulator>
    )
endif()

# Copy assets Textures
add_custom_command(TARGET YinCulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Assets/Textures
        $<TARGET_FILE_DIR:YinCulator>/Assets/Textures
)

# Copy assets Fonts
add_custom_command(TARGET YinCulator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SRC_DIR}/Assets/Fonts
        $<TARGET_FILE_DIR:YinCulator>/Assets/Fonts
)

# ===== INSTALL SECTION - Creates clean release folder =====
install(TARGETS YinCulator DESTINATION .)

# Install DLLs
if(WIN32)
    install(FILES
        ${SRC_DIR}/sfml-graphics-3.dll
        ${SRC_DIR}/sfml-window-3.dll
        ${SRC_DIR}/sfml-system-3.dll
        DESTINATION .
    )
endif()

# Install Assets
install(DIRECTORY ${SRC_DIR}/Assets/Textures DESTINATION Assets)
install(DIRECTORY ${SRC_DIR}/Assets/Fonts DESTINATION Assets)

cmake_minimum_required(VERSION 3.15.4)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(
    main 
    src/background.hpp 
    src/background.cpp
    src/ball.hpp 
    src/ball.cpp
    src/drawable.hpp
    src/field.hpp 
    src/field.cpp
    src/handler.hpp
    src/identifiable.hpp 
    src/identifiable.cpp
    src/line.hpp 
    src/line.cpp
    src/main.cpp 
    src/textures.hpp 
    src/textures.cpp
)
target_link_libraries(main PRIVATE sfml-graphics)
target_compile_features(main PRIVATE cxx_std_17)
target_compile_options(main PRIVATE -g)
target_compile_options(main PRIVATE -O0)

if(WIN32)
    add_custom_command(
        TARGET main
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:main>
        VERBATIM)
endif()

## Building from cmd-line
# cmake -B build -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config Release


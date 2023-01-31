cmake_minimum_required(VERSION 3.21)
project(Platform041 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git GIT_TAG v3.11.2)
FetchContent_MakeAvailable(json)

add_executable(Platform041 src/main.cpp)
target_link_libraries(Platform041 PRIVATE sfml-graphics)
target_link_libraries(Platform041 PRIVATE nlohmann_json::nlohmann_json)
target_compile_features(Platform041 PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Platform041 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Platform041> $<TARGET_FILE_DIR:Platform041> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Platform041)

cmake_minimum_required(VERSION 3.21)
project(Platform041 LANGUAGES CXX)

include(FetchContent)

FetchContent_Declare(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

FetchContent_Declare(json GIT_REPOSITORY https://github.com/nlohmann/json.git GIT_TAG v3.11.2)
FetchContent_MakeAvailable(json)

add_executable(Platform041 src/main.cpp src/Bullet.cpp src/ClassicWall.cpp src/Coin.cpp src/Controller.cpp src/CustomWall.cpp src/Enemy.cpp src/Finish.cpp src/KillingObstacle.cpp src/Level.cpp src/Menu.cpp src/Player.cpp)

target_link_libraries(Platform041 PRIVATE 
    sfml-graphics
    nlohmann_json::nlohmann_json)

target_compile_features(Platform041 PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Platform041 POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Platform041> $<TARGET_FILE_DIR:Platform041> COMMAND_EXPAND_LISTS)
endif()

add_custom_target(copy_assets COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_LIST_DIR}/res ${CMAKE_CURRENT_BINARY_DIR}/res)
add_dependencies(Platform041 copy_assets)

install(TARGETS Platform041)
cmake_minimum_required(VERSION 3.10)
project(TravelGuideBot)

set(CMAKE_CXX_STANDARD 17)

# Find Boost
find_package(Boost REQUIRED COMPONENTS system)

# Find TgBot library
find_package(TgBot REQUIRED)

add_executable(travel_guide_bot
    src/main.cpp
    src/bot_logic.cpp
    src/pathfinding.cpp
    src/database.cpp
    src/telegram_bot.cpp
)

target_include_directories(travel_guide_bot PRIVATE include)

# Link Boost libraries
target_link_libraries(travel_guide_bot TgBot::TgBot Boost::system)

cmake_minimum_required(VERSION 2.8)
project(Platformer-prototype)

include_directories(include)

file(GLOB_RECURSE SRC 
    "src/*.cpp"
    "src/*.h"
    "src/*.hpp"
)
add_executable(${PROJECT_NAME} ${SRC})

# This project uses SDL2 to run
# target_link_libraries(SDL2 SDL2_image SDL2_mixer SDL2_ttf)

# set the correct c+ verison
set_target_properties(${PROJECT_NAME} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF    
)
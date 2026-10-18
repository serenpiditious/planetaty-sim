cmake_minimum_required(VERSION 3.12)
project(PlanetarySimulation C)

# 1. Enforce standard C compliance and optimization
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 2. Tell CMake to strictly REQUIRE raylib
find_package(raylib REQUIRED)

# 3. Define your executable and its 3 source files
add_executable(planet_sim 
    main.c 
    simulation.c
    renderer.c
)

# 4. Link raylib and the system math library to your program
# (CMake automatically finds and appends the standard math library 'm')
target_link_libraries(planet_sim PRIVATE raylib m)


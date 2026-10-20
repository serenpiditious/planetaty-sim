cmake_minimum_required(VERSION 3.12)
project(PlanetarySimulation C)

# 1. Enforce standard C compliance and optimization
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# 2. Tell CMake to strictly REQUIRE raylib
find_package(raylib 5.5 CONFIG QUIET)

if(NOT raylib_FOUND)
    include(FetchContent)
    
    # Optional: Turn off raylib's internal examples and games to speed up build times
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG        5.5 # Or use "master" / a specific version tag
    )
    FetchContent_MakeAvailable(raylib)
endif()

# 3. Define your executable and its 3 source files
add_executable(planet_sim 
    main.c 
    simulation.c
    renderer.c
)

# 4. Link raylib and the system math library to your program
# (CMake automatically finds and appends the standard math library 'm')
target_link_libraries(planet_sim PRIVATE raylib m)



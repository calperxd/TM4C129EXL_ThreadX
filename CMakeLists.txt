cmake_minimum_required(VERSION 3.28)

# Include the external project settings
include(ProjectSettings.cmake)

# Define the project name
set(PROJECT_NAME "untitled")
project(${PROJECT_NAME} C ASM)

# Source files
set(SRC_FILES
        src/startup_gcc.c src/main.c
        threadx/ports/cortex_m4/gnu/example_build/tx_initialize_low_level.S
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

# Include compiler options for the main target
target_compile_options(${PROJECT_NAME} PRIVATE ${COMPILER_OPTIONS})

# Add the ThreadX submodule directory
add_subdirectory(threadx)

# Include compiler options for ThreadX
target_compile_options(threadx PUBLIC ${COMPILER_OPTIONS})

# Include directories for the main target
target_include_directories(${PROJECT_NAME} PRIVATE ${TI_SDK} "${CMAKE_CURRENT_SOURCE_DIR}/threadx/common/inc")

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE "${TI_SDK}/driverlib/gcc/libdriver.a" threadx)
target_link_options(${PROJECT_NAME} PRIVATE ${LINKER_FLAGS})

# Debug messages to confirm paths and settings
message(STATUS "Compiler Flags: ${COMPILER_OPTIONS}")
message(STATUS "Linker Flags: ${LINKER_FLAGS}")
message(STATUS "TI SDK Path: ${TI_SDK}")
message(STATUS "Source Files: ${SRC_FILES}")

# Define the path to the toolchain file
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/threadx/cmake/cortex_m4.cmake" CACHE PATH "Path to the toolchain file")

# Check and set the ARM GCC compiler
find_program(ARM_GCC arm-none-eabi-gcc)
find_program(ARM_GCC_AS arm-none-eabi-as)

if(NOT ARM_GCC)
    message(FATAL_ERROR "arm-none-eabi-gcc not found!")
endif()
set(CMAKE_C_COMPILER "${ARM_GCC}")
set(CMAKE_ASM_COMPILER "${ARM_GCC_AS}")
message(STATUS "Using arm-none-eabi-gcc at: ${ARM_GCC}")
message(STATUS "Using arm-none-eabi-gcc at: ${ARM_GCC_AS}")


# Set compiler options
set(COMPILER_OPTIONS
        -g
        -DPART_TM4C129ENCPDT
        -mcpu=cortex-m4
        -mthumb
        -mfpu=fpv4-sp-d16
        -mfloat-abi=soft
        -ffunction-sections
        -fdata-sections
        -Wall
        -fstack-usage
        --specs=nano.specs
)

# Include directories
set(TI_SDK "/home/calper/Downloads/SW-TM4C-2.2.0.295")
include_directories(${TI_SDK} "${CMAKE_CURRENT_SOURCE_DIR}/threadx/common/inc")

# Linker flags
set(LINKER_FLAGS
        -T${CMAKE_SOURCE_DIR}/memory/project0.ld
        -Wl,--gc-sections
        -Wl,--entry=ResetISR
        -nostartfiles
)

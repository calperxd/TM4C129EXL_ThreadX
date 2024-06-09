cmake_minimum_required(VERSION 3.10)

# Procurar pelo compilador arm-none-eabi-gcc
find_program(ARM_GCC arm-none-eabi-gcc)
if (NOT ARM_GCC)
    message(FATAL_ERROR "arm-none-eabi-gcc not found")
endif()

# Procurar pelo compilador arm-none-eabi-g++
find_program(ARM_GXX arm-none-eabi-g++)
if (NOT ARM_GXX)
    message(FATAL_ERROR "arm-none-eabi-g++ not found")
endif()

# Define compilers
set(CMAKE_C_COMPILER ${ARM_GCC})
set(CMAKE_CXX_COMPILER ${ARM_GXX})

# Disable gcc checks
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(Hello C CXX ASM)

# Specific settings to embedded systems
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(PART TM4C129ENCPDT)
set(BIN_NAME ${PROJECT_NAME}.bin)
set(FPU_FLAGS "-mfpu=fpv4-sp-d16")
set(FLOAT_ABI_FLAGS "-mfloat-abi=hard")
set(CMAKE_C_FLAGS "-Wall -mthumb -mcpu=cortex-m4 ${FPU_FLAGS} ${FLOAT_ABI_FLAGS} -DPART_${PART} -Dgcc -O2")
set(CMAKE_CXX_FLAGS "-Wall -mthumb -mcpu=cortex-m4 ${FPU_FLAGS} ${FLOAT_ABI_FLAGS} -DPART_${PART} -Dgcc -O2")
set(CMAKE_ASM_FLAGS "-mthumb -mcpu=cortex-m4 ${FPU_FLAGS} ${FLOAT_ABI_FLAGS}")
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs -nostartfiles -T ${CMAKE_SOURCE_DIR}/linkerscripts/linker.ld -Wl,-Map=${PROJECT_NAME}.map")
set(TI_SDK "/home/calper/Downloads/SW-TM4C-2.2.0.295")
set(ELF_NAME ${PROJECT_NAME}.elf)
set(THREADX_ARCH "cortex_m4")
set(THREADX_TOOLCHAIN "gnu")

# DEFINE
add_definitions(-DTX_INCLUDE_USER_DEFINE_FILE)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(include)
include_directories(${TI_SDK})

# Comandos para substituir o tx_user_sample.h pelo tx_user.h
add_custom_command(
        OUTPUT ${CMAKE_SOURCE_DIR}/external/threadx/common/inc/tx_user.h
        COMMAND ${CMAKE_COMMAND} -E remove ${CMAKE_SOURCE_DIR}/external/threadx/common/inc/tx_user_sample.h
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/include/tx_user.h ${CMAKE_SOURCE_DIR}/external/threadx/common/inc/tx_user.h
        DEPENDS ${CMAKE_SOURCE_DIR}/include/tx_user.h
        COMMENT "Replacing tx_user_sample.h with tx_user.h"
)

file(GLOB SOURCE "${CMAKE_SOURCE_DIR}/source/*.c")
file(GLOB SOURCE_ASM "${CMAKE_SOURCE_DIR}/source/*.S")

add_subdirectory(external/threadx)

add_executable(${ELF_NAME} ${SOURCE} ${SOURCE_ASM})

# Linkar a biblioteca ThreadX
target_link_libraries(${ELF_NAME} ${CMAKE_SOURCE_DIR}/lib/libdriver.a threadx)
target_compile_options(${ELF_NAME} PUBLIC -Wall ${FPU_FLAGS} ${FLOAT_ABI_FLAGS})

add_custom_command(TARGET ${ELF_NAME} POST_BUILD
        COMMAND arm-none-eabi-objcopy -O binary ${ELF_NAME} ${BIN_NAME}
        COMMENT "Converting ${ELF_NAME} to ${BIN_NAME}"
        VERBATIM)

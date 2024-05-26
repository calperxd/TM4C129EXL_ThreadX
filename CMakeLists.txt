cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(Hello C ASM)

# arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(PART TM4C129ENCPDT)
set(BIN_NAME ${PROJECT_NAME}.bin)
set(FPU_FLAGS "-mfpu=fpv4-sp-d16")
set(FLOAT_ABI_FLAGS "-mfloat-abi=hard")
set(CMAKE_C_FLAGS "-Wall -mthumb -mcpu=cortex-m4 ${FPU_FLAGS} ${FLOAT_ABI_FLAGS} -DPART_${PART} -Dgcc -O2")
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs -nostartfiles -T ${CMAKE_SOURCE_DIR}/linkerscripts/linker.ld -Wl,-Map=${PROJECT_NAME}.map")
set(TI_SDK "/home/calper/Downloads/SW-TM4C-2.2.0.295")
set(ELF_NAME ${PROJECT_NAME}.elf)

include_directories(include)
include_directories(${TI_SDK})
include_directories(${CMAKE_SOURCE_DIR}/include)

file(GLOB SOURCE "${CMAKE_SOURCE_DIR}/source/*.c")

add_executable(${ELF_NAME} ${SOURCE})

# Linkar a biblioteca ThreadX
target_link_libraries(${ELF_NAME} m ${CMAKE_SOURCE_DIR}/lib/libdriver.a)
target_compile_options(${ELF_NAME} PUBLIC -Wall ${FPU_FLAGS} ${FLOAT_ABI_FLAGS})


add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Converting ${ELF_NAME} to ${BIN_NAME}"
    VERBATIM)

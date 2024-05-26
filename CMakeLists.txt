cmake_minimum_required(VERSION 3.0)

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

project(Hello C ASM)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)
# Avoid known bug in linux giving:
#    arm-none-eabi-gcc: error: unrecognized command line option '-rdynamic'
set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
set(CMAKE_ASM_COMPILER arm-none-eabi-as)
set(PART TM4C129ENCPDT)
set(CMAKE_C_FLAGS "-Wall -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=hard -DPART_${PART} -Dgcc -O2")
set(CMAKE_EXE_LINKER_FLAGS "-specs=nano.specs -specs=nosys.specs -nostartfiles -T ${CMAKE_SOURCE_DIR}/linkerscripts/linker.ld -Wl,-Map=${PROJECT_NAME}.map")
set(TI_SDK "/home/calper/Downloads/SW-TM4C-2.2.0.295")
set(ELF_NAME ${PROJECT_NAME}.elf)

include_directories(include)
include_directories(${TI_SDK})
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/threadx/common/inc)
include_directories(${CMAKE_SOURCE_DIR}/threadx/ports/cortex_m4/gnu/inc)

file(GLOB SOURCE "${CMAKE_SOURCE_DIR}/source/*.c")

# Ensure ThreadX is built before the project
add_custom_target(build_threadx ALL
    COMMAND ${CMAKE_COMMAND} -B build_threadx -S ${CMAKE_CURRENT_SOURCE_DIR}/threadx -GNinja -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DTHREADX_ARCH=${THREADX_ARCH} -DTHREADX_TOOLCHAIN=${THREADX_TOOLCHAIN} -DTHREADX_FP_FLAGS="${FPU_FLAGS} ${FLOAT_ABI_FLAGS}"
    COMMAND ${CMAKE_COMMAND} --build build_threadx
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/threadx
    COMMENT "Building ThreadX library"
)

add_executable(${ELF_NAME} ${SOURCE})

#target_link_libraries(${ELF_NAME} ${CMAKE_SOURCE_DIR}/lib/libfftw3.a)
target_link_libraries(${ELF_NAME} m ${CMAKE_SOURCE_DIR}/lib/libdriver.a ${CMAKE_SOURCE_DIR}/threadx/build_threadx/libthreadx.a)
target_compile_options(${ELF_NAME} PUBLIC -Wall)

set(BIN_NAME ${PROJECT_NAME}.bin)
add_custom_command(TARGET ${ELF_NAME} POST_BUILD
    COMMAND arm-none-eabi-objcopy -O binary ${ELF_NAME} ${BIN_NAME}
    COMMENT "Converting ${ELF_NAME} to ${BIN_NAME}"
    VERBATIM)


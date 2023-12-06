cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(PICO_BOARD pico)
set(PICO_PLATFORM rp2040)
set(PICO_COMPILER pico_arm_gcc)

set(PROJECT_NAME pio_test)
set(PIO_FILE PioClk/clk.pio)
#set(PIO_FILE2 capture.pio)
set(MAIN_C_FILE main.c)
set(PIO_CLK_EXE ${CMAKE_CURRENT_LIST_DIR}/PioClk/pio_clk.c)

# Optional Line: note this needs to be copied into your project directory
# cp $PICO_SDK_PATH/external/pico_sdk_import.cmake ./
include(pico_sdk_import.cmake)
# Another way of doing it without any copying  
# include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

include_directories(
    ${CMAKE_CURRENT_LIST_DIR}/include
)

project(${PROJECT_NAME} C CXX ASM)

pico_sdk_init()

add_executable(${PROJECT_NAME}
        ${PIO_CLK_EXE} 
)

pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/${PIO_FILE})
#pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/${PIO_FILE2})

target_sources(${PROJECT_NAME} PRIVATE ${MAIN_C_FILE})
target_link_libraries(${PROJECT_NAME}
        pico_stdlib              # for core functionality
        hardware_pio             # for pio_ functions
        hardware_clocks            # for sys clk calls
        hardware_dma 
        )

pico_enable_stdio_usb(${PROJECT_NAME} 1)
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})

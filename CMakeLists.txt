cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

project(MCP23S17 C CXX ASM)

set(SOURCES MCP23S17.cpp)
set(LIB_DEPS "")

if (DEFINED PICO_BOARD)
	set(SOURCES ${SOURCES} platform/pico.cpp)
	set(LIB_DEPS hardware_spi)
endif()

add_library(MCP23S17 STATIC ${SOURCES})
target_include_directories(MCP23S17 PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
)
target_link_libraries(MCP23S17 
        ${LIB_DEPS}
        )





# Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.
cmake_minimum_required(VERSION 2.8)

project(app)

option(BUILD_TESTS "Build test programs" OFF)

set(INC_DIR inc)
set(SRC_DIR src)

file(GLOB SRC
    "${SRC_DIR}/*.cpp"
)

include_directories(${INC_DIR})

# Создает исполняемый файл с именем main
# из исходника main.cpp
add_executable(app ${SRC} "${SRC_DIR}/main.cpp")

if (BUILD_TESTS)
	add_subdirectory(test)
endif(BUILD_TESTS)
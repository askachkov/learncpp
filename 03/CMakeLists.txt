# Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.
cmake_minimum_required(VERSION 2.8)

set(INC_DIR inc)
set(SRC_DIR src)
#set(SRC ${SRC_DIR}/main.cpp 
#		${SRC_DIR}/Calc.cpp)

file(GLOB SRC
    "${SRC_DIR}/*.cpp"
)

include_directories(${INC_DIR})
# Создает исполняемый файл с именем main
# из исходника main.cpp
add_executable(app ${SRC})
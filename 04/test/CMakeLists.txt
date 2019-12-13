# Проверка версии CMake.
# Если версия установленой программы
# старее указаной, произайдёт аварийный выход.
cmake_minimum_required(VERSION 2.8)

# Unit tests
find_package(UnitTest++ REQUIRED)

file(GLOB TEST_SRC "*.cpp")

add_definitions( -DBUILD_TESTS )

include_directories(${UTPP_INCLUDE_DIRS})

add_executable(test ${SRC} ${TEST_SRC})

target_link_libraries(test UnitTest++)
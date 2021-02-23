project(warehouseTsd)

find_package(Qt6Core)
add_executable(warehouseTsd
    cpp/main.cpp
    cpp/model.cpp
    cpp/model.h
    cpp/testHandler.h)
target_link_libraries(warehouseTsd lib_warehouse Qt6::Core)
target_include_directories(warehouseTsd PUBLIC include
    PUBLIC $<TARGET_PROPERTY:lib_warehouse,INTERFACE_INCLUDE_DIRECTORIES>)

cmake_minimum_required (VERSION 3.2)
project(libpcrfc VERSION 0.1 LANGUAGES C CXX)

option(TESTING "Enable testing" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -O3")

file(GLOB SRC src/*.c)
add_library(pcrfc ${SRC})

if(TESTING)
    add_definitions(-DFAKE_MALLOC)
endif()

target_include_directories(pcrfc PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    PRIVATE src)
    
install(TARGETS pcrfc
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin)
    
install(DIRECTORY include/ DESTINATION include)


if(TESTING)
    
    add_subdirectory(deps/googletest/googletest)
    
    enable_testing()
    file(GLOB TEST_SRC tests/*.cpp)
    

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include
                        ${gtest_SOURCE_DIR}/include
                        ${gtest_SOURCE_DIR})
    
    add_executable(runtests ${TEST_SRC})
                        
    target_link_libraries(runtests gtest gtest_main pthread)
    target_link_libraries(runtests pcrfc)
    
    add_test(NAME all COMMAND runtests)
    
endif()


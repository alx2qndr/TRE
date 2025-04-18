cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(TinyRenderingEngine VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory("${CMAKE_SOURCE_DIR}/external")

add_executable(${PROJECT_NAME} 
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/src/Application.cpp"
    "${CMAKE_SOURCE_DIR}/src/Window.cpp"
    "${CMAKE_SOURCE_DIR}/src/Context.cpp"
    "${CMAKE_SOURCE_DIR}/src/Device.cpp"
    "${CMAKE_SOURCE_DIR}/src/Model.cpp"
    "${CMAKE_SOURCE_DIR}/src/Swapchain.cpp"
    "${CMAKE_SOURCE_DIR}/src/Pipeline.cpp"
    "${CMAKE_SOURCE_DIR}/src/Renderer.cpp"
    "${CMAKE_SOURCE_DIR}/src/Object.cpp"
)

target_link_libraries(${PROJECT_NAME} PUBLIC external::external)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_SOURCE_DIR}/include")
include(FetchContent)

add_library(external INTERFACE)
add_library(external::external ALIAS external)

find_package(glfw3 QUIET CONFIG)
if (NOT glfw3_FOUND)
    message(WARNING "glfw3 package not found. Attempting to fetch it from the repository...")
    FetchContent_Declare(
        glfw3
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
    )
    FetchContent_MakeAvailable(glfw3)
endif()

find_package(Vulkan REQUIRED)
if (NOT Vulkan_FOUND)
    message(FATAL_ERROR "Vulkan package not found. Please install Vulkan SDK and try again.")
endif()

find_package(glm QUIET CONFIG)
if (NOT glm_FOUND)
    message(WARNING "glm package not found. Attempting to fetch it from the repository...")
    FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG 1.0.1
    )
    FetchContent_MakeAvailable(glm)
endif()

add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/stb_image")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/tiny_obj_loader")

target_link_libraries(external INTERFACE
    glfw
    Vulkan::Vulkan
    glm::glm
    stb_image
    tiny_obj_loader
)

cmake_minimum_required(VERSION 3.30)
project(virtual_geometry_engine)

set(CMAKE_CXX_STANDARD 20)

# Vulkan dependencies
find_package(Vulkan REQUIRED)

# Find and configure GLFW
set(GLFW_INCLUDE_DIR /opt/homebrew/Cellar/glfw/3.4/include)
set(GLFW_LIBRARY /opt/homebrew/Cellar/glfw/3.4/lib/libglfw.3.4.dylib)

# Find and configure GLM
set(GLM_INCLUDE_DIR /opt/homebrew/Cellar/glm/1.0.1/include)
set(GLM_LIBRARY /opt/homebrew/Cellar/glm/1.0.1/lib/libglm.dylib)

include_directories(${GLFW_INCLUDE_DIR} ${GLM_INCLUDE_DIR})
link_directories(/opt/homebrew/Cellar/glfw/3.4/lib /opt/homebrew/Cellar/glm/1.0.1/lib)

add_executable(virtual_geometry_engine src/main.cpp
        src/Renderer/Window.cpp
        src/demo.cpp
        src/renderer/Pipeline.cpp
        src/renderer/Device.cpp
        src/renderer/SwapChain.cpp
        src/renderer/Model.cpp
        src/game/GameObject.cpp
        src/renderer/Renderer.cpp
        src/renderer/SimpleRenderSystem.cpp
        src/renderer/Camera.cpp
        src/game/KeyboardMovementController.cpp)

# Include directories
target_include_directories(virtual_geometry_engine PRIVATE src)
target_include_directories(virtual_geometry_engine SYSTEM PRIVATE ${CMAKE_SOURCE_DIR}/lib)

# Link Vulkan
target_link_libraries(virtual_geometry_engine Vulkan::Vulkan)

# Link GLFW
target_link_libraries(virtual_geometry_engine ${GLFW_LIBRARY})

# Link GLM
target_link_libraries(virtual_geometry_engine ${GLM_LIBRARY})

# Find all shader files
file(GLOB SHADER_FILES "${CMAKE_SOURCE_DIR}/src/shaders/*.vert" "${CMAKE_SOURCE_DIR}/src/shaders/*.frag")

# Set the output directory for SPIR-V files
set(SPIRV_OUTPUT_DIR "${CMAKE_BINARY_DIR}/shaders")

# Set models path
set(MODELS_DIR "${CMAKE_SOURCE_DIR}/models")

# Ensure the output directory exists
file(MAKE_DIRECTORY ${SPIRV_OUTPUT_DIR})

# Compile each shader file using glslc
foreach(SHADER_FILE ${SHADER_FILES})
    get_filename_component(FILE_NAME ${SHADER_FILE} NAME)
    set(SPIRV_FILE "${SPIRV_OUTPUT_DIR}/${FILE_NAME}.spv")
    add_custom_command(
            OUTPUT ${SPIRV_FILE}
            COMMAND /usr/local/bin/glslc ${SHADER_FILE} -o ${SPIRV_FILE}
            DEPENDS ${SHADER_FILE}
            COMMENT "Compiling shader ${FILE_NAME} to SPIR-V"
            VERBATIM
    )
    list(APPEND SPIRV_FILES ${SPIRV_FILE})
endforeach()

# Ensure shaders are compiled before building the main executable
add_custom_target(CompileShaders ALL DEPENDS ${SPIRV_FILES})
add_dependencies(virtual_geometry_engine CompileShaders)

# Copy SPIR-V files to the build directory
add_custom_command(
        TARGET virtual_geometry_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SPIRV_OUTPUT_DIR}
        ${CMAKE_BINARY_DIR}/shaders
)
# copy models
add_custom_command(
        TARGET virtual_geometry_engine POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${MODELS_DIR}
        ${CMAKE_BINARY_DIR}/models
)
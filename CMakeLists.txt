cmake_minimum_required(VERSION 3.6)
project(OHook CXX)
enable_language(C)

set(CMAKE_CXX_STANDARD 23)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/MP /MD /bigobj)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# ==============================================
# LIBRARIES
# ==============================================

# Detours
file(GLOB DETOURS_SOURCES Libraries/detours/*.cpp)
file(GLOB DETOURS_HEADERS Libraries/detours/*.h)
add_library(detours STATIC ${DETOURS_SOURCES} ${DETOURS_HEADERS})
target_include_directories(detours PUBLIC Libraries/detours)

# JsonCPP
file(GLOB_RECURSE JSONCPP_SOURCES Libraries/jsoncpp/dist/*.cpp)
add_library(jsoncpp STATIC ${JSONCPP_SOURCES})
target_include_directories(jsoncpp PUBLIC Libraries/jsoncpp/include)

# GLEW
file(GLOB GLEW_SOURCES Libraries/glew/src/glew.c)
set_source_files_properties(${GLEW_SOURCES} PROPERTIES LANGUAGE C)
add_library(glew STATIC ${GLEW_SOURCES})
target_include_directories(glew PUBLIC Libraries/glew/include)
target_compile_definitions(glew PRIVATE $<$<BOOL:${WIN32}>:GLEW_STATIC>)

# ImGUI
file(GLOB IMGUI_SOURCES Libraries/ImGui/*.cpp Libraries/ImGui/impls/*.cpp)
file(GLOB IMGUI_HEADERS Libraries/ImGui/*.h Libraries/ImGui/impls/*.h)
if(WIN32)
    file(GLOB IMGUI_PLATFORM_SOURCES Libraries/ImGui/impls/windows/*.cpp)
    file(GLOB IMGUI_PLATFORM_HEADERS Libraries/ImGui/impls/windows/*.h)
elseif(UNIX AND NOT APPLE)
    file(GLOB IMGUI_PLATFORM_SOURCES Libraries/ImGui/impls/linux/*.cpp)
    file(GLOB IMGUI_PLATFORM_HEADERS Libraries/ImGui/impls/linux/*.h)
endif()
list(APPEND IMGUI_SOURCES ${IMGUI_PLATFORM_SOURCES})
list(APPEND IMGUI_HEADERS ${IMGUI_PLATFORM_HEADERS})

add_library(imgui STATIC ${IMGUI_SOURCES} ${IMGUI_HEADERS})
target_include_directories(imgui PUBLIC Libraries/ImGui Libraries/glew/include)
target_compile_definitions(imgui PRIVATE IMGUI_DEFINE_MATH_OPERATORS $<$<BOOL:${WIN32}>:GLEW_STATIC>)

# RendererHook
file(GLOB_RECURSE RENDERERHOOK_SOURCES Libraries/RendererHook/*.cpp)
file(GLOB_RECURSE RENDERERHOOK_HEADERS Libraries/RendererHook/*.h)
add_library(RendererHook STATIC ${RENDERERHOOK_SOURCES} ${RENDERERHOOK_HEADERS})
target_include_directories(RendererHook PUBLIC Libraries/RendererHook Libraries/glew/include)
target_compile_definitions(RendererHook PRIVATE $<$<BOOL:${WIN32}>:GLEW_STATIC>)
target_link_libraries(RendererHook PUBLIC detours imgui glew jsoncpp)

# ==============================================
# GAME SDK
# ==============================================

# PaliaSDK
file(GLOB_RECURSE PALIASDK_SOURCES PaliaSDK/*.cpp)
file(GLOB_RECURSE PALIASDK_HEADERS PaliaSDK/*.hpp)
add_library(PaliaSDK STATIC ${PALIASDK_SOURCES} ${PALIASDK_HEADERS})
target_include_directories(PaliaSDK PUBLIC PaliaSDK)
target_precompile_headers(PaliaSDK PRIVATE PaliaSDK/SDK.hpp)

# ==============================================
# OHOOK MAIN PROJECT
# ==============================================

# Clean up any existing PDB file
if(EXISTS "${CMAKE_BINARY_DIR}/OHook.pdb")
   file(REMOVE ${CMAKE_BINARY_DIR}/OHook.pdb)
endif()

# Collect OHook sources with proper organization
file(GLOB_RECURSE OHOOK_CORE_SOURCES OHook/Core/*.cpp)
file(GLOB_RECURSE OHOOK_CORE_HEADERS OHook/Core/*.h)

file(GLOB_RECURSE OHOOK_DETOURS_SOURCES OHook/Detours/*.cpp)
file(GLOB_RECURSE OHOOK_DETOURS_HEADERS OHook/Detours/*.h)

file(GLOB_RECURSE OHOOK_DETOURS_MAIN_SOURCES OHook/Detours/Main/*.cpp)
file(GLOB_RECURSE OHOOK_DETOURS_MAIN_HEADERS OHook/Detours/Main/*.h)

file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_SOURCES OHook/Detours/Supporters/*.cpp)
file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_HEADERS OHook/Detours/Supporters/*.h)

file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_TOOLS_SOURCES OHook/Detours/Supporters/AutoTools/*.cpp)
file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_TOOLS_HEADERS OHook/Detours/Supporters/AutoTools/*.h)

file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_ENTITLEMENTS_SOURCES OHook/Detours/Supporters/Entitlements/*.cpp)
file(GLOB_RECURSE OHOOK_DETOURS_SUPPORTERS_ENTITLEMENTS_HEADERS OHook/Detours/Supporters/Entitlements/*.h)

file(GLOB_RECURSE OHOOK_HANDLERS_SOURCES OHook/Handlers/*.cpp)
file(GLOB_RECURSE OHOOK_HANDLERS_HEADERS OHook/Handlers/*.h)

file(GLOB_RECURSE OHOOK_OVERLAYS_SOURCES OHook/Overlay/*.cpp)
file(GLOB_RECURSE OHOOK_OVERLAYS_HEADERS OHook/Overlay/*.h)

file(GLOB_RECURSE OHOOK_MISC_SOURCES OHook/Misc/*.cpp)
file(GLOB_RECURSE OHOOK_MISC_HEADERS OHook/Misc/*.h)

# Main OHook files (dllmain.cpp, etc.)
file(GLOB OHOOK_MAIN_SOURCES OHook/*.cpp)
file(GLOB OHOOK_MAIN_HEADERS OHook/*.h)

# Console sources
file(GLOB CONSOLE_SOURCES console/*.cpp)
file(GLOB CONSOLE_HEADERS console/*.hpp)

# Languages sources
file(GLOB LANGUAGES_SOURCES languages/*.cpp)
file(GLOB LANGUAGES_HEADERS languages/*.h)

# Combine all OHook sources
set(OHOOK_ALL_SOURCES 
    ${OHOOK_CORE_SOURCES}
    ${OHOOK_FEATURES_SOURCES} 
    ${OHOOK_HANDLERS_SOURCES}
    ${OHOOK_DETOURS_SOURCES}
    ${OHOOK_DETOURS_MAIN_SOURCES}
    ${OHOOK_DETOURS_SUPPORTERS_SOURCES}
    ${OHOOK_DETOURS_SUPPORTERS_TOOLS_SOURCES}
    ${OHOOK_DETOURS_SUPPORTERS_ENTITLEMENTS_SOURCES}
    ${OHOOK_OVERLAYS_SOURCES}
    ${OHOOK_MISC_SOURCES}
    ${OHOOK_MAIN_SOURCES}
    ${CONSOLE_SOURCES}
    ${LANGUAGES_SOURCES}
)

set(OHOOK_ALL_HEADERS
    ${OHOOK_CORE_HEADERS}
    ${OHOOK_FEATURES_HEADERS}
    ${OHOOK_HANDLERS_HEADERS}
    ${OHOOK_DETOURS_HEADERS}
    ${OHOOK_DETOURS_MAIN_HEADERS}
    ${OHOOK_DETOURS_SUPPORTERS_HEADERS}
    ${OHOOK_DETOURS_SUPPORTERS_TOOLS_HEADERS}
    ${OHOOK_DETOURS_SUPPORTERS_ENTITLEMENTS_HEADERS}
    ${OHOOK_OVERLAYS_HEADERS}
    ${OHOOK_MISC_HEADERS}
    ${OHOOK_MAIN_HEADERS}
    ${CONSOLE_HEADERS}
    ${LANGUAGES_HEADERS}
)

# Create the OHook DLL
add_library(OHook SHARED ${OHOOK_ALL_SOURCES} ${OHOOK_ALL_HEADERS})

# Include directories for OHook
target_include_directories(OHook PRIVATE 
    OHook
    OHook/Core
    OHook/Features
    OHook/Handlers
    OHook/Detours
    OHook/Detours/Main
    OHook/Detours/Supporters
    OHook/Detours/Supporters/AutoTools
    OHook/Detours/Supporters/Entitlements
    OHook/Overlay
    OHook/Misc
    console
    languages
    Libraries/glew/include
    Libraries/ImGui
    Libraries/jsoncpp/include
    Libraries/RendererHook
    PaliaSDK
)

# Compile definitions
target_compile_definitions(OHook PRIVATE $<$<BOOL:${WIN32}>:GLEW_STATIC>)

# Link libraries
target_link_libraries(OHook PRIVATE 
    RendererHook 
    PaliaSDK 
    jsoncpp
    glew
    $<$<BOOL:${WIN32}>:ws2_32> 
    $<$<BOOL:${WIN32}>:iphlpapi> 
    $<$<BOOL:${WIN32}>:psapi> 
    $<$<BOOL:${WIN32}>:opengl32.lib> 
    $<$<BOOL:${WIN32}>:Winmm.lib>
)
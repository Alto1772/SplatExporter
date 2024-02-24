cmake_minimum_required(VERSION 3.12.0)
project(SplatExtractor)

set(CMAKE_CXX_STANDARD 20 CACHE STRING "The C++ standard to use")
#set(CMAKE_C_STANDARD 11 CACHE STRING "The C standard to use")
set(CMAKE_C_STANDARD 11)

################################################################################
# Download vcpkg for external dependencies on Windows
################################################################################

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    include(CMake/automate-vcpkg.cmake)

    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        set(VCPKG_TRIPLET x64-windows-static)
        set(VCPKG_TARGET_TRIPLET x64-windows-static)
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32")
        set(VCPKG_TRIPLET x86-windows-static)
        set(VCPKG_TARGET_TRIPLET x86-windows-static)
    endif()

    vcpkg_bootstrap()
    vcpkg_install_packages(libpng openssl)
endif()

################################################################################
# Source files
################################################################################

# -- src --

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
file(GLOB_RECURSE CXX_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.cpp)
file(GLOB_RECURSE C_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c ${CMAKE_CURRENT_SOURCE_DIR}/src/**/*.c)
set(ALL_SRC_FILES ${CXX_FILES} ${C_FILES})

# -- libgfxd -- 

#set(LIBGFXD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/libgfxd)
#set(LIBGFXD_C_FILES 
#    ${LIBGFXD_DIR}/gfxd.c
#    ${LIBGFXD_DIR}/uc_f3d.c
#    ${LIBGFXD_DIR}/uc_f3db.c
#    ${LIBGFXD_DIR}/uc_f3dex.c
#    ${LIBGFXD_DIR}/uc_f3dex2.c
#    ${LIBGFXD_DIR}/uc_f3dexb.c
#)

#list(APPEND ALL_SRC_FILES ${LIBGFXD_C_FILES})

################################################################################
# Build executable
################################################################################

add_executable(${PROJECT_NAME} ${ALL_SRC_FILES})

################################################################################
# Libraries
################################################################################

# -- yaml-cpp --

include(FetchContent)

FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG 0.8.0
)
FetchContent_GetProperties(yaml-cpp)

if(NOT yaml-cpp_POPULATED)
  message(STATUS "Fetching yaml-cpp...")
  FetchContent_Populate(yaml-cpp)
  add_subdirectory(${yaml-cpp_SOURCE_DIR} ${yaml-cpp_BINARY_DIR})
endif()

target_link_libraries(${PROJECT_NAME} PUBLIC yaml-cpp::yaml-cpp)

# -- OpenSSL (External) --

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE OpenSSL::Crypto)

# -- libpng (External) --

#find_package(PNG REQUIRED)
#target_link_libraries(${PROJECT_NAME} PRIVATE PNG::PNG)

################################################################################
# Compile and link options
################################################################################

if(MSVC)
    if("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x64")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od;
                /RTC1
            >
            $<$<CONFIG:Release>:
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL
        )
    elseif("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "x86")
        target_compile_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /Od
            >
            $<$<CONFIG:Release>:
                /O2;
                /Oi;
                /Gy
            >
            /permissive-;
            /sdl;
            /W3;
            ${DEFAULT_CXX_DEBUG_INFORMATION_FORMAT};
            ${DEFAULT_CXX_EXCEPTION_HANDLING}
        )
        target_link_options(${PROJECT_NAME} PRIVATE
            $<$<CONFIG:Debug>:
                /INCREMENTAL
            >
            $<$<CONFIG:Release>:
                /OPT:REF;
                /OPT:ICF
            >
            /DEBUG:FULL
        )
    endif()
endif()

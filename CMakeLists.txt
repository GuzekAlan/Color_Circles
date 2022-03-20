cmake_minimum_required(VERSION 3.15)

set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

project(SFML_Testing LANGUAGES CXX)

file(GLOB sources "src/*.cpp")

add_executable(app ${sources})



include_directories("include")

include(FetchContent)

FetchContent_Declare(
  SFML
  URL "https://github.com/SFML/SFML/archive/2.5.1.zip"
)

# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
# )

# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)

FetchContent_GetProperties(SFML)

if(NOT SFML_POPULATED)
  if (LINK_DEPS_STATIC)
    set(SFML_STATIC_LIBRARIES TRUE CACHE BOOL "Use static libraries")
  endif()

  set(SFML_INSTALL_PKGCONFIG_FILES OFF CACHE BOOL "Install pkgconfig files")

  if (USE_SYSTEM_DEPS)
    find_package(SFML ${SFML_VERSION} COMPONENTS graphics QUIET)
  else()
    FetchContent_Populate(SFML)

    # No need to build audio and network modules
    set(SFML_BUILD_AUDIO FALSE CACHE BOOL "Build audio")
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "Build network")
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR} EXCLUDE_FROM_ALL)
  endif()
endif()



target_link_libraries(app
    PRIVATE
        sfml-graphics
        sfml-system
        sfml-window
)

set_property(TARGET app PROPERTY 
  VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
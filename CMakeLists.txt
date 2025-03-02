cmake_minimum_required(VERSION 3.28)

set(PROJECT_NAME "eve_industry")
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
#set(CPP_FRAMEWORKS_DIR "")
#set(Boost_INCLUDE_DIR "")
#set(Boost_LIBRARY_DIR "")
#set(OPENSSL_ROOT_DIR "")
#set(OPENSSL_INCLUDE_DIR "")
#set(OPENSSL_LIBRARIES "")
#set(WX_ROOT_DIR "")
#set(WX_LIB_DIR "")

project(${PROJECT_NAME} VERSION 1.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(WIN32)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif()

if(NOT CMAKE_CONFIGURATION_TYPES)
    get_property(HAVE_MULTI_CONFIG_GENERATOR GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
    # Set default configuration types for multi-config generators
    if(HAVE_MULTI_CONFIG_GENERATOR)
        set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
    endif()
endif()

file(TO_CMAKE_PATH "${CMAKE_INSTALL_PREFIX}" CMAKE_INSTALL_PREFIX)

# https://blog.kitware.com/cmake-and-the-default-build-type/
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(default_build_type "Debug")
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release")
endif()

include(files.cmake)

find_package(nlohmann_json REQUIRED)

find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
    include_directories(${OPENSSL_INCLUDE_DIR})
	target_link_libraries(${PROJECT_NAME} ${OPENSSL_LIBRARIES} )
endif()

find_package(Boost 1.83)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIR})
  target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )
endif()

IF (WIN32)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS")
	set(wxWidgets_CONFIGURATION mswu)
ENDIF()

set(wxWidgets_ROOT_DIR ${WX_ROOT_DIR})
set(wxWidgets_LIB_DIR ${WX_LIB_DIR})

find_package(wxWidgets REQUIRED COMPONENTS net core base aui)				   
if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
	target_include_directories(${PROJECT_NAME} PUBLIC ${wxWidgets_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
endif()
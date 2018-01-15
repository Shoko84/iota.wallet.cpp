###
### README
###
### if your installation fail or if your paths are customized, please indicate them through the following vars
### --> (QT_BASE_PATH) default =	"C:/Qt/5.9.1/" on windows
###									"$ENV{HOME}/Qt/5.9.1/" on linux
### --> (FSLIB_STATIC) default = "/usr/lib/gcc/x86_64-linux-gnu/5/libstdc++fs.a" use only in linux to compile with the filesystem experimental library in c++14

### GENERAL SETTINGS
cmake_minimum_required(VERSION 2.8.11)

# Create project
set(APP_NAME "IOTAWallet++")
project(${APP_NAME})

### USEFUL VARIABLES
set(CMAKE_INCLUDE_CURRENT_DIR ON)

### COMPILATOR OPTIONS
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### QT BASE PATH
if (NOT QT_BASE_PATH)
	if (WIN32)
		set(QT_BASE_PATH "C:/Qt/5.9.1/")
	elseif (UNIX AND NOT APPLE)
		set(QT_BASE_PATH $ENV{HOME}/Qt/5.9.1/)
	endif()
endif()

### LIBCSTD++FS (UNIX)
if (UNIX AND NOT APPLE AND NOT FSLIB_STATIC)
	set(FSLIB_STATIC "/usr/lib/gcc/x86_64-linux-gnu/5/libstdc++fs.a")
endif()

set(APP_DIR ${PROJECT_SOURCE_DIR})
set(BIN_OUTPUT_DIR ${APP_DIR}/bin)
message("Starting generation for ${APP_NAME} in ${APP_DIR} - ${CMAKE_SYSTEM_NAME} (${CMAKE_SYSTEM_VERSION})")

### HEADERS FILES
include_directories(
	# --- RAPIDJSON LIB
	${APP_DIR}/include/
  	# --- WIDGETS
    ${APP_DIR}/src/widget/class/MainWindow
    ${APP_DIR}/src/widget/class/InteractiveLabel
  	# --- SYSTEMS
	${APP_DIR}/src/systems/templates
	${APP_DIR}/src/systems/class/UISystem/
  	# --- LAUNCHER
	${APP_DIR}/src/launcher/class/
  	# --- ERRORS
	${APP_DIR}/src/standalone/errors/class/
	# --- CRAWLER
	${APP_DIR}/src/standalone/crawler/class/
)

# Enable debug symbols by default
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()

### APP TARGET
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_OUTPUT_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${BIN_OUTPUT_DIR})
if (WIN32)
	set(BIN_MSVC_PATH ${QT_BASE_PATH}/msvc2015/bin)
endif()

message("The executable will be generated at ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# Running moc/uic/rcc automatically
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

message("Retrieving compilator options...")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake_modules")

if (WIN32)
	if (MSVC)
		message("MSVC found!")
	else (NOT MSVC)
		message(FATAL_ERROR "MSVC compilator not found")
	endif()
endif()

if(WIN32)
	set(CMAKE_PREFIX_PATH ${QT_BASE_PATH}/msvc2015/lib/cmake)
elseif (UNIX AND NOT APPLE)
	set(CMAKE_PREFIX_PATH ${QT_BASE_PATH}/gcc_64)
endif()

### LIBRARIES
# QT COMPONENTS
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
# QT INCLUDES
include_directories(${Qt5Network_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

### APP SRCS
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES			${APP_DIR}/src/*.cpp)
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES_H		${APP_DIR}/src/*.h)
file(GLOB_RECURSE SOURCE_LAUNCHER_FILES_HPP		${APP_DIR}/src/*.hpp)

# APP HEADERS
file(GLOB_RECURSE HEADER_LAUNCHER_FILES_H		${APP_DIR}/include/*.h)
file(GLOB_RECURSE HEADER_LAUNCHER_FILES_HPP		${APP_DIR}/include/*.hpp)

# APP FORMS UI
## All *.ui file goes there as
qt5_wrap_ui(UIS_HDRS
    ${APP_DIR}/src/widget/class/MainWindow/mainwindow.ui
)

### EXECUTABLE
add_executable(${APP_NAME}
  WIN32
  ${SOURCE_LAUNCHER_FILES}
  ${HEADER_LAUNCHER_FILES_H}
  ${HEADER_LAUNCHER_FILES_HPP}
  ${SOURCE_LAUNCHER_FILES_H}
  ${SOURCE_LAUNCHER_FILES_HPP}
  ${UIS_HDRS}
)

### LIBRARIES LINKING
# STDC++FS (ONLY IN UNIX)
if (UNIX AND NOT APPLE)
	add_library(stdc++fs UNKNOWN IMPORTED)
	set_property(TARGET stdc++fs PROPERTY IMPORTED_LOCATION ${FSLIB_STATIC})
	target_link_libraries(${APP_NAME} stdc++fs)
endif()
# QT
target_link_libraries(${APP_NAME} Qt5::Widgets)

# Windows specific build steps
if(WIN32)
	file(GLOB_RECURSE DLL_LIB_FILES ${PROJECT_SOURCE_DIR}/lib/win/dll/*.dll)
	if (DLL_LIB_FILES)
		add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${DLL_LIB_FILES} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
	endif()
	# Run winddeployqt if it can be found
	find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${BIN_MSVC_PATH})
	add_custom_command(TARGET ${APP_NAME} POST_BUILD COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${APP_NAME}>)
endif()

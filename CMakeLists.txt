project(WntrNtwk)
cmake_minimum_required(VERSION 2.8)

set(WNTRNTWK_MAJOR_VERSION 0)
set(WNTRNTWK_MINOR_VERSION 0)
set(WNTRNTWK_MICRO_VERSION 1)
set(WNTRNTWK_VERSION
    ${WNTRNTWK_MAJOR_VERSION}.${WNTRNTWK_MINOR_VERSION}${WNTRNTWK_MICRO_VERSION})

## Custom modules
list(APPEND CMAKE_MODULE_PATH "cmake/Modules")

include(WintermuteDefaults)
include(WintermuteMacros)

## Packages

find_package(PythonLibs REQUIRED)
find_package(Boost 1.4 COMPONENTS
    python
    REQUIRED)
find_package(Qt4 4.4.3 COMPONENTS
    QtCore
    QtNetwork
    QJSON
    QtDBus
    QT_DONT_USE_QTGUI
    REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(QCA qca2>=2.0.2)

## Used to generate QR images (soon, but might be moved to WntrGui).
#pkg_check_modules(QRENCODE libqrencode>=3.1.1-1)

## Used to implement mail servers and clients..
#pkg_check_modules(QMFCLIENT qmfclient>=1.0)
#pkg_check_modules(QMFMESSAGESERVER qmfmessageserver>=1.0)

enable_doxygen()

## Qt-specific stuff
set(UseQt4 true)
include("${QT_USE_FILE}")


## Main variables
set(VS_KEYWORD Qt4VSv1.0)
set(VS_SCC_PROJECTNAME "Wintermute Network")
set(WNTRNTWK_INCLUDE_DIR "${WINTER_INCLUDE_INSTALL_DIR}/wntr/ntwk" CACHE PATH "Includes directory.")
set(WNTRNTWK_LIB_DIR "${WINTER_LIB_INSTALL_DIR}" CACHE PATH "Library install directory.")
set(WNTRNTWK_INCLUDE_DIRS "${WNTRNTWK_INCLUDE_DIR}"
    ${Boost_INCLUDE_DIR}
    ${QJSON_INCLUDE_DIR}
    ${QT_INCLUDE_DIR}
    ${PYTHON_INCLUDE_DIRS})
set(WNTRNTWK_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/share/cmake/WntrNtwk" CACHE PATH "CMake directory.")
set(WNTRNTWK_LIBRARIES ${Boost_LIBRARIES} ${QT_LIBRARIES} ${QJSON_LIBRARIES} ${PYTHON_LIBRARIES})

## Includes
include_directories(${WNTRNTWK_INCLUDE_DIRS})

## Files
file(GLOB WNTRNTWK_SHPP "src/*.hpp")
file(GLOB WNTRNTWK_SCPP "src/*.cpp")
file(GLOB CMAKE_MODULES "${PROJECT_SOURCE_DIR}/cmake/Modules/*.cmake")
QT4_WRAP_CPP(WNTRNTWK_SCPP "${WNTRNTWK_SHPP}")

## Targets
add_library(wntrntwk SHARED
    ${WNTRNTWK_SCPP})

set_target_properties(wntrntwk PROPERTIES
    VERSION ${GENERIC_LIB_VERSION}
    SOVERSION ${GENERIC_LIB_SOVERSION})

target_link_libraries(wntrntwk
    ${WNTRNTWK_LIBRARIES})

## Configs
configure_file("cmake/WntrNtwkConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/InstallFiles/WntrNtwkConfig.cmake" @ONLY)

configure_file("cmake/WntrNtwkConfigVersion.cmake.in"
    "${PROJECT_BINARY_DIR}/InstallFiles/WntrNtwkConfigVersion.cmake" @ONLY)

configure_file("${PROJECT_SOURCE_DIR}/wntrntwk.pc.in"
   "${PROJECT_BINARY_DIR}/InstallFiles/wntrntwk.pc" @ONLY)

## Installs
install(TARGETS wntrntwk
    EXPORT WntrNtwkLibraryDepends
    LIBRARY DESTINATION "${WNTRNTWK_LIB_DIR}")

install(EXPORT WntrNtwkLibraryDepends
    DESTINATION "${WNTRNTWK_CMAKE_DIR}")

install(FILES
    "${PROJECT_BINARY_DIR}/InstallFiles/WntrNtwkConfig.cmake"
    "${PROJECT_BINARY_DIR}/InstallFiles/WntrNtwkConfigVersion.cmake"
    DESTINATION "${WNTRNTWK_CMAKE_DIR}")

install(FILES ${WNTRNTWK_SHPP}
    DESTINATION "${WNTRNTWK_INCLUDE_DIR}")

install(FILES ${CMAKE_MODULES}
    DESTINATION "${CMAKE_MODULE_DIR}")

install(FILES "${PROJECT_BINARY_DIR}/InstallFiles/wntrntwk.pc"
    DESTINATION "${WNTRNTWK_LIB_DIR}/pkgconfig/")

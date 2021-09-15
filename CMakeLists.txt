cmake_minimum_required(VERSION 3.20)

project(PD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 6.2.0 COMPONENTS Core Gui Network Quick LinguistTools Sql REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SQLCipher IMPORTED_TARGET REQUIRED sqlcipher)

set(QAPPLICATION_CLASS QGuiApplication)
add_subdirectory(3rdparty/SingleApplication)

add_subdirectory(QtGraphicalEffects)
list(APPEND QML_DIRS "${CMAKE_CURRENT_BINARY_DIR}")
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator extra qml import paths")
add_compile_definitions($<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PDBaseListModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PDBaseListModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PDBaseModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PDBaseModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PluginManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/PluginManager.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/QMLPropertyHelpers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Core/QObjectPropertyMap.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/DBManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/DBManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/QSQLCipherDriver/QSQLCipherDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/QSQLCipherDriver/QSQLCipherDriver.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/MainWindow.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ActivitiesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ActivitiesModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/PanelModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/PanelModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ThemesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ThemesModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/PDApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PDApplication.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/Platform.hpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/src/qml.qrc
    )

add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/src/PluginInterface)

if(APPLE)
    list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/Platform.mm)
else()
    list(APPEND PROJECT_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/Platform.cpp)
endif()

add_subdirectory(src/PDPlugins)

qt_add_executable(PD ${PROJECT_SOURCES})
qt_add_translations(PD
    TS_FILES
        ${CMAKE_CURRENT_SOURCE_DIR}/translations/PD_en_US.ts
        ${CMAKE_CURRENT_SOURCE_DIR}/translations/PD_zh_CN.ts
    RESOURCE_PREFIX "/translations")

include(src/qml/qml.cmake)

# For Android deployment, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# set_property(TARGET PD APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

# For macOS deployment
# ~/Qt/6.2.0/macos/bin/macdeployqt ./PD.app/ -qmldir=${CMAKE_CURRENT_SOURCE_DIR}/src/qml/ -qmlimport=.

target_compile_definitions(PD PRIVATE
    -DQT_DISABLE_DEPRECATED_BEFORE=0x060200
    -DQT_USE_QSTRINGBUILDER=1
    -DQT_NO_CAST_FROM_ASCII)

set_target_properties(PD PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER "pd.moody.me"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )

target_include_directories(PD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

target_link_libraries(PD
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::Quick
        Qt::Sql
        Qt::SqlPrivate
        SingleApplication::SingleApplication
        PkgConfig::SQLCipher
        PD::AllPlugins
        PD::PDPluginInterface)

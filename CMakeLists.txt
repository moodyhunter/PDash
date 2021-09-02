cmake_minimum_required(VERSION 3.14)

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

add_subdirectory(QtGraphicalEffects)
list(APPEND QML_DIRS "${CMAKE_CURRENT_BINARY_DIR}")
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator 4.1 extra qml import paths")

set(PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PDApplication.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/PDApplication.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/QSQLCipherDriver/QSQLCipherDriver.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/QSQLCipherDriver/QSQLCipherDriver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/DBManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DB/DBManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/QMLPropertyHelpers.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/QObjectPropertyMap.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/PDBaseModel.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ActivitiesModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ActivitiesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/PDBaseModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/PDBaseModel2.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/Base/PDBaseModel2.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/MainWindowModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/MainWindowModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ThemesModel.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Models/ThemesModel.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugins/PluginInterface.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugins/PluginManager.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Plugins/PluginManager.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qml.qrc
    )

if(APPLE)
    list(APPEND PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/MainWindow-macOS.hpp")
    list(APPEND PROJECT_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/platforms/MainWindow-macOS.mm")
endif()

qt_add_executable(PD MANUAL_FINALIZATION ${PROJECT_SOURCES})
qt_import_qml_plugins(PD)
qt_finalize_executable(PD)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/translation/PD_zh_CN.ts)

qt_add_resources(PD "translations"
    PREFIX "/translations"
    BASE ${CMAKE_CURRENT_BINARY_DIR}
    FILES ${QM_FILES})

# For Android deployment, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# set_property(TARGET PD APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

# For macOS deployment
# ~/Qt/6.2.0/macos/bin/macdeployqt ./PD.app/ -qmldir=../src/qml/ -qmlimport=.

target_compile_definitions(PD PRIVATE -DQT_DISABLE_DEPRECATED_BEFORE=0x060200)

set_target_properties(PD PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_GUI_IDENTIFIER pd.moody.me
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )

option(PD_DEBUG_MODEL OFF)
if(PD_DEBUG_MODEL)
    find_package(Qt6 6.2.0 COMPONENTS Widgets REQUIRED)
    target_compile_definitions(PD PRIVATE PD_DEBUG_MODEL=1)
    target_link_libraries(PD PRIVATE Qt::Widgets)
endif()

target_compile_definitions(PD PRIVATE QT_USE_QSTRINGBUILDER QT_NO_CAST_FROM_ASCII)

target_include_directories(PD PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(PD PRIVATE ${Qt6Sql_PRIVATE_INCLUDE_DIRS})
target_compile_definitions(PD PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(PD
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::Quick
        Qt::Sql
        PkgConfig::SQLCipher)

cmake_minimum_required(VERSION 3.14)

project(PD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 6.1.0 COMPONENTS Core Gui Network Quick LinguistTools REQUIRED)

set(TS_FILES translation/PD_zh_CN.ts)

add_subdirectory(QtGraphicalEffects)
list(APPEND QML_DIRS "${CMAKE_CURRENT_BINARY_DIR}")
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Qt Creator 4.1 extra qml import paths")

set(PROJECT_SOURCES
    src/main.cpp
    src/platforms/macOS-blurredWindow.mm
    src/platforms/macOS-blurredWindow.hpp
    src/qml.qrc
    ${TS_FILES}
    )

qt_add_executable(PD MANUAL_FINALIZATION ${PROJECT_SOURCES})
# For linking against statically built Qt
qt_import_qml_plugins(PD)

qt_finalize_executable(PD)

# See https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
# set_property(TARGET PD APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/android)

qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})

set_target_properties(PD PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER pd.moody.me
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    )


target_compile_definitions(PD PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(PD
    PRIVATE
        Qt::Core
        Qt::Gui
        Qt::Network
        Qt::Quick
         )

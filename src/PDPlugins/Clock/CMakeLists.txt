project(Clock)

set(CMAKE_AUTOMOC ON)

pd_add_plugin(Clock
    STATIC
    CLASS_NAME "PDClock"
    SOURCES
        back.cpp
        back.hpp
    QML_FILES
        ClockItem.qml)

project(Clock)

set(CMAKE_AUTOMOC ON)

pd_add_plugin(Clock
    STATIC
    CLASS_NAME "PDClock"
    SOURCES
        Clock.cpp
        Clock.hpp
    QML_FILES
        qml/ClockItem.qml)

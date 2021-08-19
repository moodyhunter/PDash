import QtQuick

Item {
    id: globalTheme
    property color background
    property color dark
    property color highlight
    property color highlightText
    property color text
    property color warn
    property color shadow
    property color border
    property color deep
    property color deepText
    property color logoBakground
    property color logoContainer
    property color logoText
    property color startIcon
    property color handlerHoverColor: Qt.lighter(globalTheme.border, 1.5)
    property string backgroundImage
    property double backgroundOpacity: 0.3

    states: [
        State {
            name: "LightState"
            PropertyChanges {
                target: globalTheme
                background: "#FFFFFF"
                dark: "#FAFAFA"
                highlight: "#6BBDBD"
                highlightText: "#FFFFFF"
                text: "#3F3F3F"
                warn: "#FF6767"
                shadow: "#29000000"
                border: "#27707070"
                deep: "#6BADAD"
                deepText: "#FFFFFF"
                logoBakground: highlight
                logoContainer: background
                logoText: highlightText
                startIcon: "#BBDE5E"
                backgroundImage: "qrc:/icons/card_background.jpg"
                backgroundOpacity: 0.9
            }
        },
        State {
            name: "DarkState"
            PropertyChanges {
                target: globalTheme
                background: "#653B4252"
                dark: "#2E3440"
                highlight: "#5E81AC"
                highlightText: "#ECEFF4"
                text: "#ECEFF4"
                warn: "#BF616A"
                shadow: "#29000000"
                border: "#3381A1C1"
                deep: "#3B4252"
                deepText: "#ECEFF4"
                logoBakground: dark
                logoContainer: background
                logoText: highlightText
                startIcon: Qt.lighter(highlight, 1.1)
                backgroundImage: "qrc:/icons/card_background.jpg"
                backgroundOpacity: 0.7
            }
        }
    ]
}

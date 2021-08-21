import QtQuick
import QtQuick.Controls
import QtGraphicalEffects
import QtQuick.Layouts

import pd.mooody.me

Popup {
    id: popup
    closePolicy: Popup.NoAutoClose
    width: parent.width
    height: parent.height
    modal: true

    readonly property int _paddingH: parent.width / 2 - 200
    readonly property int _paddingV: parent.height / 2 - 70
    bottomPadding: _paddingV
    topPadding: _paddingV
    leftPadding: _paddingH
    rightPadding: _paddingH

    background: Rectangle {
        color: "#90000000"
    }

    NumberAnimation {
        id: hidinganimation
        target: popup
        property: "opacity"
        easing.type: Easing.OutCirc
        to: 0.00
        duration: 250
        onFinished: popup.close()
    }

    contentItem: Rectangle {
        color: AppTheme.background
        border.width: 1
        border.color: AppTheme.border
        radius: 10
        anchors.leftMargin: 100
        ColumnLayout {
            anchors.fill: parent
            spacing: 0

            Label {
                font.pixelSize: 20
                text: qsTr("Enter Your Password")
                Layout.alignment: Qt.AlignCenter
            }

            TextField {
                id: pswdText
                color: AppTheme.text
                Layout.fillWidth: true
                Layout.leftMargin: 50
                Layout.rightMargin: 50
                horizontalAlignment: TextInput.AlignHCenter
                selectByMouse: true
                font: fixedFont
                background: Rectangle {
                    border.color: AppTheme.border
                    border.width: 1
                    color: AppTheme.dark
                }
                passwordCharacter: '*'
                echoMode: "Password"
                Keys.onEnterPressed: {
                    parent.submit()
                }
            }

            Label {
                id: errmsgLabel
                color: "red"
                visible: false
                font: fixedFont
                Layout.alignment: Qt.AlignCenter
            }

            Button {
                text: qsTr("Unlock Database")
                onClicked: parent.submit()
                Layout.alignment: Qt.AlignCenter
            }

            function submit() {
                if (DBManager.openDatabase("default", pswdText.text)) {
                    errmsgLabel.visible = false
                    hidinganimation.start()
                } else {
                    errmsgLabel.visible = true
                    pswdText.clear()
                    errmsgLabel.text = qsTr("Failed to Open Database")
                }
            }
        }
    }

    Component.onCompleted: pswdText.forceActiveFocus()
} //Popup

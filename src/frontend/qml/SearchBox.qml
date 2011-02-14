import Qt 4.7

FocusScope {
    property string text: "search for music"

    id: focusScope
    width: 510
    height: 60

    BorderImage {
        id: img
        source: "images/searchbox.png"

        width: parent.width
        height: parent.height

        border { left: 4; top: 4; right: 4; bottom: 4; }
    }

    Text {
        id: helpText
        anchors {
            fill: textInput
        }
        verticalAlignment: Text.AlignVCenter
        text: parent.text
        color: "gray"
        font.italic: true
        font.pixelSize: 20
    }

    MouseArea { 
        anchors.fill: parent
        onClicked: {
            parent.focus = true
            textInput.openSoftwareInputPanel ()
        } 
    }

    Image {
        id: search
        anchors {
            right: parent.right
            rightMargin: 16
            verticalCenter: parent.verticalCenter
        }
        source: "images/find.png"
        height: 35
        width: height
        sourceSize {
            height: height
            width: width
        }
    }

    TextInput {
        id: textInput
        anchors {
            left: parent.left
            right: search.left
            leftMargin: 25
            rightMargin: 10
            verticalCenter: parent.verticalCenter
        }
        focus: true
        selectByMouse: true
        font.pixelSize: 20
    }

    states: State {
        name: "hasText"; when: textInput.text != ''
        PropertyChanges { target: helpText; opacity: 0 }
    }

    transitions: [
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}

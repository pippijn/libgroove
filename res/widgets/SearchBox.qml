import Qt 4.7

FocusScope {
    property string text: "search for music"

    anchors {
        horizontalCenter: parent.horizontalCenter
    }
    width: parent.width - 40
    height: 60

    Image {
        source: "/images/searchbox"

        width: parent.width
        height: parent.height
    }

    Text {
        id: helpText
        anchors {
            fill: searchInput
        }
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        text: parent.text
        color: "gray"
        font.italic: true
        font.pixelSize: searchInput.font.pixelSize
    }

    MouseArea { 
        anchors.fill: parent
        onClicked: {
            parent.focus = true
            searchInput.openSoftwareInputPanel ()
        } 
    }

    MouseArea {
        id: search

        onClicked: {
            controller.search (searchInput.text)
        }

        anchors {
            right: parent.right
            rightMargin: 16
            verticalCenter: parent.verticalCenter
        }

        height: 35
        width: height

        Image {
            anchors {
                fill: parent
            }
            source: "/icons/search"
            sourceSize {
                height: height
                width: width
            }
        }
    }

    TextInput {
        id: searchInput
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

        Keys.onEnterPressed: {
            controller.search (searchInput.text)
        }
        /*
        Keys.onDownPressed: {
            completionListView.incrementCurrentIndex ()
        }
        */
        Keys.onReleased: {
            if (!autocompleteTimer.running)
                autocompleteTimer.start ()
        }

        Timer {
            id: autocompleteTimer
            interval: 1000

            onTriggered: {
                controller.autocomplete (searchInput.text)
            }
        }
    }

    states: State {
        name: "hasText"; when: searchInput.text != ''
        PropertyChanges { target: helpText; opacity: 0 }
    }

    transitions: [
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}

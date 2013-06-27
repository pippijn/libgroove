import Qt 4.7

FocusScope {
    property string text: "search for music"

    anchors {
        horizontalCenter: parent.horizontalCenter
    }
    width: parent.width * 0.9
    height: 60

    function doSearch () {
        searchIcon.state = "searching"
        controller.search (searchInput.text)
    }

    Rectangle {
        width: parent.width
        height: parent.height
        radius: 10
        color: "#dddddd"
        border.color: "#747474"
        border.width: 2

        Rectangle {
            width: parent.width - 20
            height: parent.height - 20
            x: 10
            y: 10
            color: "white"
            border.color: "black"
        }
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
        id: search

        onClicked: doSearch ()

        anchors {
            right: parent.right
            rightMargin: 16
            verticalCenter: parent.verticalCenter
        }

        height: 35
        width: height

        Rectangle {
            id: searchIcon
            state: "inactive"
            anchors.fill: parent

            Image {
                id: searchIconInactive
                anchors.fill: parent
                source: "/icons/search"
                opacity: 1
                sourceSize {
                    height: height
                    width: width
                }
            }
            AnimatedImage {
                id: searchIconSearching
                height: 32
                width: height
                x: (parent.height - height) / 2
                y: (parent.width - width) / 2
                source: "/icons/loading"
                opacity: 0
            }

            Connections {
                target: searchModel

                onSearchCompleted: {
                    searchIcon.state = "inactive"
                    console.log (numOfResults)
                }
            }

            states: [
                State {
                    name: "inactive"
                    PropertyChanges {
                        target: searchIconInactive
                        opacity: 1
                    }
                    PropertyChanges {
                        target: searchIconSearching
                        opacity: 0
                    }
                },

                State {
                    name: "searching"
                    PropertyChanges {
                        target: searchIconInactive
                        opacity: 0
                    }
                    PropertyChanges {
                        target: searchIconSearching
                        opacity: 1
                    }
                }
            ]

            transitions: [
                Transition {
                    to: "searching"

                    NumberAnimation {
                        exclude: searchIconInactive
                        properties: "opacity"
                        duration: 1000
                    }
                },

                Transition {
                    to: "inactive"

                    NumberAnimation {
                        exclude: searchIconSearching
                        properties: "opacity"
                        duration: 300
                    }
                }
            ]
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

        Keys.onReturnPressed: doSearch ()
        Keys.onEnterPressed: doSearch ()
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

    states: [
        State {
            name: "hasText"; when: searchInput.text != ''
            PropertyChanges { target: helpText; opacity: 0 }
        }
    ]

    transitions: [
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}

import Qt 4.7

Component {
    Rectangle {
        width: ListView.view.width
        height: ListView.view.parent.rowHeight
        color: "transparent"

        MouseArea {
            anchors {
                fill: parent
            }

            onClicked: {
                ListView.view.currentIndex = index
                console.log ("Selected index: " + index)
            }

            Text {
                text: modelData
            }
        }
    }
}

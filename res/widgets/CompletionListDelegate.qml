import Qt 4.7

Component {
    Rectangle {
        ListView.onAdd: {
            console.log ("Item added!")
        }

        ListView.onRemove: {
            console.log ("Item removed!")
        }

        width: ListView.view.width
        height: 30
        color: "transparent"

        MouseArea {
            anchors {
                fill: parent
            }

            onClicked: {
                ListView.incrementCurrentIndex ()
                console.log ("Current index: " + index)
                console.log ("Current index: " + ListView.currentIndex)
            }

            Text {
                text: modelData
            }
        }
    }
}

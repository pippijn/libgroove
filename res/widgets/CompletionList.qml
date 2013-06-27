import Qt 4.7

Rectangle {
    property int rowHeight: 30

    color: "white"
    border.color: "black"
    radius: 4
    height: rowHeight * 5 + anchors.margins / 2

    Component {
        id: highlight
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }
            color: "lightsteelblue"; radius: 5
            y: listView.currentItem.y
            Behavior on y {
                SpringAnimation {
                    spring: 3
                    damping: 0.2
                }
            }
        }
    }

    ListView {
        id: listView
        model: completion
        clip: true
        highlightFollowsCurrentItem: true

        anchors {
            fill: parent
            margins: 10
        }

        delegate: CompletionListDelegate { }
        highlight: highlight
    }
}

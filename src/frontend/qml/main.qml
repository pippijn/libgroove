import Qt 4.7

Rectangle {
    width: 700
    height: 300
    color: "#999999"

    Rectangle {
        width: 700;
        height: 300;
        color: "#edecec"

        MouseArea {
            anchors.fill: parent
            onClicked: parent.focus = false;
        }
        Column {
            anchors {
                fill: parent
                leftMargin: 8
                topMargin: 8
            }
            spacing: 10

            SearchBox {
                id: search
                focus: true
            }
        }
    }
}

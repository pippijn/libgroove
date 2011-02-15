import Qt 4.7

Rectangle {
    color: "white"
    border.color: "black"
    radius: 4

    ListView {
        model: completion
        clip: true

        anchors {
            fill: parent
            margins: 10
        }

        delegate: CompletionListDelegate { }
    }
}

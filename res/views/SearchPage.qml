import Qt 4.7
import "/widgets"

Rectangle {
    color: "transparent"

    SearchResults { }

    SearchBox {
        id: searchBox
        focus: true
    }

    CompletionList {
        anchors {
            left:   searchBox.left
            right:  searchBox.right
            top:    searchBox.bottom
            margins: 18
            topMargin: -16
        }
        visible: false
    }
}

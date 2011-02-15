import Qt 4.7
import "/widgets"

Rectangle {
    id: searchPage
    /*color: "#000000"*/
    color: "transparent"

    SearchResults {
        id: searchList
    }

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
    }
}

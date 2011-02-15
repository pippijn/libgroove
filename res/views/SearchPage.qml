import Qt 4.7
import "/widgets"

Rectangle {
    id: searchPage
    /*color: "#000000"*/
    color: "transparent"

    ListView {
        id: searchList
        model: searchModel
        /*model: TestModel { }*/

        anchors {
            left:   parent.left
            right:  parent.right
            bottom: parent.bottom
            top:    searchBox.bottom
            margins: 10
        }

        delegate: SongListDelegate { }
    }

    SearchBox {
        id: searchBox
        focus: true
    }
}

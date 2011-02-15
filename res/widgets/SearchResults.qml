import Qt 4.7

ListView {
    model: searchModel
    /*model: TestModel { }*/

    anchors {
        left:   parent.left
        right:  parent.right
        bottom: parent.bottom
        top:    searchBox.bottom
        margins: 10
    }

    delegate: SearchResultsDelegate { }
}

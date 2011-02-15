import Qt 4.7
import "/widgets"

Rectangle {
    width: 798
    height: 441
    color: "black"

    Image {
        id: background
        width: parent.width
        height: parent.height
        source: "/images/background"
    }

    Rectangle {
        width: parent.width
        height: parent.height - y
        y: 20
        color: "transparent"

        PageStack { id: pageStack; }

        SearchPage {
            id: searchPage
            width: parent.width - 10
            height: parent.height
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: parent.bottom
            }
            visible: false
        }
    }

    Component.onCompleted: {
        pageStack.push (searchPage)
    }
}

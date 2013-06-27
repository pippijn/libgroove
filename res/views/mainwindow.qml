import Qt 4.7
import "/widgets"

Rectangle {
    width: 798
    height: 441
    color: "black"

    property Item currentIcon: searchIcon

    function changePage (page, icon) {
        currentIcon = icon
        if (pageStack.currentPage != page)
            pageStack.replace (page)
    }

    Keys.onPressed: {
        // ctrl-q
        if (event.key == 81)
            Qt.quit ();
    }

    Image {
        width: parent.width
        height: parent.height
        sourceSize {
            width: width
            height: height
        }
        source: "/images/background"
    }

    Rectangle {
        width: parent.width
        height: parent.height - y
        y: 20
        color: "transparent"

        PageStack { id: pageStack; }

        SettingsPage {
            id: settingsPage
            width: parent.width - 10
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: toolbar.top
            }
            visible: false
        }

        SearchPage {
            id: searchPage
            width: parent.width - 10
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: toolbar.top
            }
            visible: false
        }

        PlaylistPage {
            id: playlistPage
            width: parent.width - 10
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: toolbar.top
            }
            visible: false
        }

        FavouritesPage {
            id: favouritesPage
            width: parent.width - 10
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                bottom: toolbar.top
            }
            visible: false
        }

        Rectangle {
            id: toolbar
            anchors.bottom: parent.bottom
            width: parent.width
            height: 40

            gradient: Gradient {
                GradientStop { position: 0.0; color: "#555" }
                GradientStop { position: 1.0; color: "#333" }
            }

            Image {
                id: toolIndicator
                width: 40
                height: width
                x: currentIcon.x - 5
                Behavior on x {
                    SpringAnimation {
                        spring: 3
                        damping: 0.5
                    }
                }
                source: "/icons/tb-current"
            }

            Image {
                id: settingsIcon
                width: 30
                height: width
                x: 5 + parent.height * 0
                y: 5
                source: "/icons/tb-settings"

                MouseArea {
                    anchors.fill: parent

                    onClicked: changePage (settingsPage, settingsIcon)
                }
            }

            Image {
                id: searchIcon
                width: 30
                height: width
                x: 5 + parent.height * 1
                y: 5
                source: "/icons/tb-search"

                MouseArea {
                    anchors.fill: parent

                    onClicked: changePage (searchPage, searchIcon)
                }
            }

            Image {
                id: playlistIcon
                width: 30
                height: width
                x: 5 + parent.height * 2
                y: 5
                source: "/icons/tb-playlist"

                MouseArea {
                    anchors.fill: parent

                    onClicked: changePage (playlistPage, playlistIcon)
                }
            }

            Image {
                id: favouritesIcon
                width: 30
                height: width
                x: 5 + parent.height * 3
                y: 5
                source: "/icons/tb-favourites"

                MouseArea {
                    anchors.fill: parent

                    onClicked: changePage (favouritesPage, favouritesIcon)
                }
            }

            MouseArea {
                width: 30
                height: width
                x: parent.width - parent.height - 5
                y: 5

                onClicked: Qt.quit ()

                Image {
                    anchors.fill: parent
                    source: "/icons/tb-quit"
                    sourceSize {
                        width: width
                        height: height
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        pageStack.push (searchPage)
    }
}

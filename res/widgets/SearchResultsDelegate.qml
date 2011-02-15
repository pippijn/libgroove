import Qt 4.7

Component {
    Rectangle {
        width: ListView.view.width
        height: 100
        color: "transparent"

        MouseArea {
            anchors {
                fill: parent
            }
            onClicked: {
                console.log ("Current index: " + index)
                searchList.currentIndex = index
                //pageStack.push (songViewPage)
            }

            Rectangle {
                width: 90
                height: 90
                color: "black"
                Image {
                    anchors {
                        verticalCenter: parent.verticalCenter
                        horizontalCenter: parent.horizontalCenter
                    }
                    width: 88
                    height: 88
                    source: coverArtFilename
                }
            }

            Text {
                x: 100
                color: "#ffffff"
                text: artistName + " - " + songName
                font.pixelSize: 20
            }
        }

        Row {
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
            spacing: 20

            Image {
                source: "/icons/play"

                width: 40
                height: 40

                MouseArea {
                    anchors {
                        fill: parent
                    }
                    onClicked: {
                        console.log ("Playing " + artistName + " - " + songName)

                        /*
                        var isPlaying = playerBackend.isPlaying

                        playerBackend.queueSong(index)

                        if (isPlaying)
                            playerBackend.skipTo(playerBackend.playlistTrackCount)
                        */
                    }
                }
            }


            Image {
                source: "/icons/next"

                width: 40
                height: 40

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log ("Queueing " + artistName + " - " + songName)
                        //playerBackend.queueSong (index);
                    }
                }
            }
        }
    }
}

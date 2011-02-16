import Qt 4.7

ListView {
    id: playlist
    model: playlistModel
    /*model: TestPlaylist { }*/

    anchors {
        fill: parent
        margins: 10
    }

    delegate: PlaylistDelegate { }
}

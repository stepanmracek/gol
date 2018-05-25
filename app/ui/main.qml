import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import GameOfLife 1.0

ApplicationWindow {
    id: root
    width: 480
    height: 480
    visible: true

    Timer {
        id: timer
        interval: 100
        onTriggered: board.step()
        repeat: true
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        QmlBoard {
            id: board;
            Layout.fillWidth: true
            Layout.preferredHeight: parent.height - panel.height
        }

        RowLayout {
            id: panel
            Layout.fillWidth: true

            Button {
                text: timer.running ? "Stop" : "Start"
                onClicked: timer.running ? timer.stop() : timer.start()
            }

            Button {
                text: "Step"
                visible: !timer.running
                onClicked: board.step()
            }

            Slider {
                from: 20
                to: 1000
                stepSize: 20
                value: timer.interval
                onValueChanged: timer.interval = value
                Layout.fillWidth: true
            }

            Label {
                text: timer.interval + "ms"
            }
        }
    }
}

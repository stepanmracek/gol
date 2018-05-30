import QtQuick 2.9
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

import GameOfLife 1.0

ApplicationWindow {
    id: root
    width: 320
    height: 480
    visible: true

    Timer {
        id: timer
        interval: 100
        onTriggered: {
            var elapsed = board.step();
            fps.text = elapsed > 0 ? (1000.0 / board.step()).toFixed(1) + "fps" : "1000fps"
        }
        repeat: true
    }

    ColumnLayout {
        anchors.fill: parent

        ToolBar {
            id: toolBar
            width: 360
            Layout.fillWidth: true

            RowLayout {
                id: rowLayout
                anchors.leftMargin: 5
                anchors.fill: parent

                Label {
                    id: label
                    text: qsTr("Game of Life")
                    Layout.fillWidth: true
                }

                ToolButton {
                    id: toolButton
                    text: qsTr("⋮")
                    onClicked: menu.open()

                    Menu {
                        id: menu
                        MenuItem {
                            text: qsTr("Add noise")
                            visible: !timer.running
                            onClicked: board.random()
                        }
                        MenuItem {
                            text: qsTr("New bounded board")
                            visible: !timer.running
                            onClicked: newBoundedBoard.open()
                        }
                    }
                }
            }
        }

        QmlBoard {
            id: board;
            Layout.fillHeight: true
            Layout.fillWidth: true

            Label {
                id: fps
                anchors.right: parent.right
                visible: timer.running
            }
        }

        RowLayout {
            id: panel
            Layout.fillWidth: true

            Button {
                text: timer.running ? "⏸" : "⏵"
                onClicked: timer.running ? timer.stop() : timer.start()
            }

            Button {
                text: "⏯"
                visible: !timer.running
                onClicked: board.step()
            }

            Slider {
                from: 20
                to: 1000
                stepSize: 20
                visible: timer.running
                value: timer.interval
                onValueChanged: timer.interval = value
                Layout.fillWidth: true
            }
        }
    }

    Popup {
        id: newBoundedBoard
        modal: true
        x: (parent.width - width) / 2
        y: (parent.height - height) / 2

        GridLayout {
            anchors.fill: parent
            columns: 2
            Label { text: qsTr("Width") }
            SpinBox { id: spinWidth; value: 20; from: 1; to: 1024 }

            Label { text: qsTr("Height") }
            SpinBox { id: spinHeight; value: 20; from: 1; to: 1024 }

            Button {
                text: qsTr("Create")
                onClicked: board.newBounded()
            }
        }
    }
}

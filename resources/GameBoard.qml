import QtQuick 2.0
import Game 1.0
import GameAdds 1.0

GridView {
    id: root
    width: 300
    height: 400
    cellWidth: width / model.xDimension
    cellHeight: height / model.yDimension
    interactive: false
    focus: true

    model : GameBoardModel {
        onScoreChanged: {
            if (!(value % 1000)) {
                timer.interval -= 100;
                speed.text = parseInt(speed.text) + 5;
            }

            score.text = value;
        }

        onNextFigureChanged: {
            image.source = getFigureImageByType(value);
        }
    }

    delegate: Tile {
        width: root.cellWidth
        height: root.cellHeight
        visible: display
        gradient: Gradient {
            GradientStop {
                position: 0.0;
                color: "gainsboro"
            }
            GradientStop {
                position: 0.2;
                color: filled ? figureColor : "white"
            }
        }
    }

    Timer {
        id: timer
        interval: 1000;
        running: true;
        repeat: true;
        onTriggered: root.model.moveFigure(NModel.DOWN);
    }

    Image {
        source: "qrc:/resources/img/background.png";
        anchors.fill: parent;
        opacity: 0.2
    }

    Keys.onPressed: {
        if (event.key === Qt.Key_A) {
            root.model.moveFigure(NModel.LEFT);
            event.accepted = true;
        }
        else if (event.key === Qt.Key_D) {
            root.model.moveFigure(NModel.RIGHT);
            event.accepted = true;
        }
        else if (event.key === Qt.Key_S) {
            root.model.moveFigure(NModel.DOWN);
            event.accepted = true;
        }
        else if (event.key === Qt.Key_Space) {
            root.model.throwFigure();
            event.accepted = true;
        }
        else if (event.key === Qt.Key_W) {
            root.model.rotateFigure();
            event.accepted = true;
        }
    }
}

import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.15
import GameAdds 1.0

Window {
    maximumHeight: 400
    minimumHeight: 400
    maximumWidth: 400
    minimumWidth: 400
    visible: true
    title: qsTr("Tetris")

    function getFigureImageByType(type) {
        switch(type)
        {
        case NModel.I:
            return "qrc:/resources/img/figureI.png";
        case NModel.J:
            return "qrc:/resources/img/figureJ.png";
        case NModel.L:
            return "qrc:/resources/img/figureL.png";
        case NModel.O:
            return "qrc:/resources/img/figureO.png";
        case NModel.S:
            return "qrc:/resources/img/figureS.png";
        case NModel.T:
            return "qrc:/resources/img/figureT.png";
        case NModel.Z:
            return "qrc:/resources/img/figureZ.png";
        default:
            return "";
        }
    }

    GameBoard {
        id: board
    }

    ToolSeparator {
        x: 300
        y: 0
        width: 15
        height: 480
        contentItem: Rectangle { color: "darkgrey" }
    }

    ToolSeparator {
        x: 306
        y: 188
        width: 95
        height: 15
        orientation: Qt.Horizontal
        contentItem: Rectangle { color: "darkgrey" }
    }

    Text {
        x: 320
        y: 233
        text: qsTr("Speed:")
        font.bold: true
    }

    Text {
        id: speed
        x: 320
        y: 253
        text: qsTr("5")
    }

    Text {
        x: 320
        y: 273
        text: qsTr("Score:")
        font.bold: true
    }

    Text {
        id: score
        x: 320
        y: 293
        text: qsTr("100")
    }

    Image {
        id: image
        x: 334
        y: 60
        width: 40
        height: 80
        source: getFigureImageByType(board.model.getNextFigureType())
    }
}

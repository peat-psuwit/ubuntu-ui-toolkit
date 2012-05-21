import QtQuick 1.1
import "../Components"

Rectangle {
    id: window

    width: 800
    height: 600

    Column {
        anchors.centerIn: parent
        spacing: 5

        Button {
            width: 200
            height: 100
            color: "blue"
            text: "text only (centered)"
            fontColor: "white"
            pressColor: "darkblue"
            onClicked: print("clicked text-only button")
        }

        IconButton {
            icon: "call_icon.png"
            verticalMargin: 10
            height: 100
            width: 200
            color: "#008800"
            pressColor: "#004400"
            onClicked: print("Clicked icon-only button")
        }
        Button {
            icon: "call_icon.png"
            height: 100
            width: 200
            iconHeight: height - 20
            color: "#008800"
            pressColor: "#004400"
            onClicked: print("Clicked icon-only button2")
            iconLocation: "top"
        }
        Button {
            icon: "call_icon.png"
            height: 50
            width: 200
            color: "orange"
            pressColor: "yellow"
            text: "icon on right"
            iconLocation: "right"
            iconHeight: height - 10;
        }
        Row {
            spacing: 4
            Button {
                icon: "call_icon.png"
                height: 100
                width: 98
                iconWidth: 50
                color: "green"
                pressColor: "orange"
                text: "Icon on top"
                iconLocation: "top"
            } // Button
            Button {
                icon: "call_icon.png"
                height: 100
                width: 98
                iconWidth: 50
                color: "red"
                pressColor: "darkred"
                text: "Text on top"
                iconLocation: "bottom"
            } // Button
        } // Row
        Button {
            icon: "call_icon.png"
            height: 50
            width: 200
            color: "orange"
            pressColor: "yellow"
            text: "icon on left"
            iconLocation: "left"
            iconHeight: height - 10
        }
    } // column
} // window

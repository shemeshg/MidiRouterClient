import QtQuick
import QtQuick.Controls


Button {
    id: btn
    property string hooverText: ""
    property bool isAnimation: true

    CoreToolTip {
        id: toolTip
    }
    HoverHandler {
        id: hoverHandler
        onHoveredChanged: {
            if (!hovered)
                toolTip.hide()
        }
    }

    onHoveredChanged: {
        if (hooverText) {
            toolTip.show(hooverText, 3000)
        }
    }

    icon.width: CoreSystemPalette.font.pixelSize
    icon.height: CoreSystemPalette.font.pixelSize


    palette.alternateBase: CoreSystemPalette.alternateBase
    palette.base: CoreSystemPalette.base
    palette.button: CoreSystemPalette.button
    palette.buttonText: CoreSystemPalette.buttonText
    palette.dark: CoreSystemPalette.dark
    palette.highlight: CoreSystemPalette.highlight
    palette.highlightedText: CoreSystemPalette.highlightedText
    palette.light: CoreSystemPalette.light
    palette.mid: CoreSystemPalette.mid
    palette.midlight: CoreSystemPalette.midlight
    palette.placeholderText: CoreSystemPalette.placeholderText
    palette.shadow: CoreSystemPalette.shadow
    palette.text: CoreSystemPalette.text
    palette.window: CoreSystemPalette.window
    palette.windowText: CoreSystemPalette.windowText

    font: CoreSystemPalette.font

    onReleased: {
        if (isAnimation) {
            colorAnimation.start()
        }


    }



    PropertyAnimation {
          id: colorAnimation
          target: btn
          property: "palette.buttonText"
          from: CoreSystemPalette.buttonText
          to: CoreSystemPalette.midlight
          duration: 100
          easing.type: Easing.InOutQuad
          onStopped: {
              revertColorAnimation.start();
          }

      }

      PropertyAnimation {
          id: revertColorAnimation
          target: btn
          property: "palette.buttonText"
          from: CoreSystemPalette.midlight
          to: CoreSystemPalette.buttonText
          duration: 100
          easing.type: Easing.InOutQuad
          running: false // To prevent it from running initially
      }



}

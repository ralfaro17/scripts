#Requires AutoHotkey v2.0

+CapsLock::Send "{NumLock}"
global osdEnabled := true
global numpadSequence := "", osdGui := "", osdText := "", useGuiOSD := true

#HotIf GetKeyState("NumLock", "T")

; Remapped numpad keys
7::Send "{Numpad7}"
8::Send "{Numpad8}"
9::Send "{Numpad9}"
u::Send "{Numpad4}"
i::Send "{Numpad5}"
o::Send "{Numpad6}"
j::Send "{Numpad1}"
k::Send "{Numpad2}"
l::Send "{Numpad3}"
m::Send "{Numpad0}"

; ALT + keys to add to sequence
!7::appendToSequence("7")
!8::appendToSequence("8")
!9::appendToSequence("9")
!u::appendToSequence("4")
!i::appendToSequence("5")
!o::appendToSequence("6")
!j::appendToSequence("1")
!k::appendToSequence("2")
!l::appendToSequence("3")
!m::appendToSequence("0")
!Backspace::removeLastDigit()

#HotIf

; Toggle between GUI OSD and Tooltip OSD
^!o::toggleOSDMode()

captureAltCodeOutput(sequence) {
    ; Create a hidden GUI with an Edit control
    captureGui := Gui("-Caption +ToolWindow +AlwaysOnTop")
    captureGui.BackColor := "Black"
    captureGui.SetFont("s10", "Consolas")
    edit := captureGui.AddEdit("vHiddenEdit w200 h30")
    
    ; Move the GUI off-screen and hide it
    captureGui.Show("x-9999 y-9999 NoActivate")
    edit.Focus()

    ; Send the ALT+numpad sequence
    Send("{Alt Down}")
    for _, digit in StrSplit(sequence)
        Send("{Numpad" digit "}")
    Send("{Alt Up}")

    Sleep 50 ; Give it a moment to process the input

    ; Read the value from the Edit control
    char := edit.Value

    ; Clean up
    captureGui.Destroy()

    return char
}


toggleOSDEnabled() {
    global osdEnabled, osdGui

    osdEnabled := !osdEnabled

    if !osdEnabled {
        ToolTip
        if osdGui
            osdGui.Hide()
    }
}


toggleOSDMode() {
    global useGuiOSD, osdGui, osdEnabled

    if !osdEnabled {        
        return
    }

    ; Hide previous OSD
    if useGuiOSD {
        if osdGui
            osdGui.Hide()
    } else {
        ToolTip
    }

    useGuiOSD := !useGuiOSD
    showOSD()
}



appendToSequence(digit) {
    global numpadSequence
    numpadSequence .= digit
    showOSD()
}

removeLastDigit() {
    global numpadSequence
    if StrLen(numpadSequence) > 0 {
        numpadSequence := SubStr(numpadSequence, 1, -1)
        showOSD()
    }
}

showOSD() {
    global numpadSequence, useGuiOSD, osdGui, osdEnabled

    if !osdEnabled {
        ToolTip
        if osdGui
            osdGui.Hide()
        return
    }

    display := "ALT+" numpadSequence
    code := Integer(numpadSequence)
    try expected := (code <= 255 ? captureAltCodeOutput(numpadSequence) : Chr(code))
    catch
        expected := ""

    display .= " → " expected

    if useGuiOSD {
        if !osdGui {
            osdGui := Gui("-Caption +AlwaysOnTop +ToolWindow", "OSD")
            osdGui.BackColor := "Black"
            osdGui.SetFont("s12 cWhite", "Segoe UI")
            osdGui.Add("Text", "vDisplayText w200 h30 Center")
        }
        osdGui["DisplayText"].Text := display
        osdGui.Show("NoActivate xCenter y10")
    } else {
        ToolTip(display)
    }
}


; GUI OSD Implementation
initOSDGui() {
    global osdGui, osdText

    if !osdGui {
        osdGui := Gui("+AlwaysOnTop -Caption +ToolWindow +Owner +LastFound")
        osdGui.BackColor := "Black"
        osdGui.SetFont("s16 cWhite", "Segoe UI")

        osdText := osdGui.Add("Text", "Center w400 h50 vOSDText", "")
        ; Position GUI at top center
        screenWidth := A_ScreenWidth
        screenHeight := A_ScreenHeight
        guiX := (screenWidth - 400) // 2
        guiY := screenHeight - 100
        osdGui.Show("x" guiX " y" guiY " NoActivate")
    }
}

/*

The following code is a legacy Implementation of the OSD modes

showGUIOSD() {
    global numpadSequence, osdGui, osdText
    if (numpadSequence = "") {
        if osdGui
            osdGui.Hide()
        return
    }

    initOSDGui()

    code := Integer(numpadSequence)
    try {
        text := (code <= 255 ? "ALT Code: " : "Unicode: ") numpadSequence " → " (code <= 255 ? captureAltCodeOutput(numpadSequence) : Chr(code))
    } catch {
        text := "Code: " numpadSequence " → [Invalid Character]"
    }

    osdText.Value := text
    osdGui.Show("NoActivate")
}

showTooltipOSD() {
    global numpadSequence
    output := ""
    if (numpadSequence != "") {
        code := Integer(numpadSequence)
        try {
            output := (code <= 255 ? "ALT Code: " : "Unicode: ") numpadSequence " → " (code <= 255 ? captureAltCodeOutput(numpadSequence) : Chr(code))
        } catch {
            output := "Code: " numpadSequence " → [Invalid Character]"
        }
    }
    ToolTip output
}
*/

; To output the correct value
sendAltCode() {
    global numpadSequence, osdGui, useGuiOSD

    if useGuiOSD {
        if osdGui
            osdGui.Hide()
    } else {
        ToolTip
    }

    if (numpadSequence != "") {
        code := Integer(numpadSequence)
        if (code <= 255) {
            Send("{Alt Down}")
            for _, digit in StrSplit(numpadSequence)
                Send("{Numpad" digit "}")
            Send("{Alt Up}")
        } else {
            try {
                char := Chr(code)
                SendText(char)
            } catch {
                MsgBox "Invalid Unicode: " numpadSequence
            }
        }
        numpadSequence := ""
    }
}


~*Alt Up::sendAltCode()
^!d::toggleOSDEnabled()  ; Ctrl + Alt + D to toggle OSD completely
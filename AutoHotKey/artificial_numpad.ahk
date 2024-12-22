#Requires AutoHotkey v2.0

+CapsLock::Send "{NumLock}"

; Variables to store the sequence of numpad keys
global numpadSequence := ""

#HotIf GetKeyState("NumLock", "T")
/* 7::Send "{NumpadDiv}"
8::Send "{NumpadMult}"
9::Send "{NumpadSub}"
0::Send "{NumpadAdd}"
p::Send "{NumpadEnter}"
ñ::Send "{NumpadDot}"
 */
u::Send "{Numpad7}"
i::Send "{Numpad8}"
o::Send "{Numpad9}"
j::Send "{Numpad4}"
k::Send "{Numpad5}"
l::Send "{Numpad6}"
m::Send "{Numpad1}"
,::Send "{Numpad2}"
.::Send "{Numpad3}"
!u::global numpadSequence .= "7"
!i::global numpadSequence .= "8"
!o::global numpadSequence .= "9"
!j::global numpadSequence .= "4"
!k::global numpadSequence .= "5"
!l::global numpadSequence .= "6"
!m::global numpadSequence .= "1"
!,::global numpadSequence .= "2"
!.::global numpadSequence .= "3"

; Function to handle the sequence completion and sending the ALT code
sendAltCode() {
    global numpadSequence
    if (numpadSequence) {
        ; Send the ALT code
        try{
            Send Chr(numpadSequence)
        }
        ; Clear the sequence
        numpadSequence := ""
    }
}

; Hotkey to handle ALT release and send the complete sequence
~*Alt Up::sendAltCode()
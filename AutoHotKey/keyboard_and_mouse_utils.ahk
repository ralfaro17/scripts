#Requires AutoHotkey v2.0
speed := 5

XButton1 & WheelUp::  WheelLeft
XButton1 & WheelDown::WheelRight

XButton2 & WheelUp::  Send '{WheelUp '   speed '}'
XButton2 & WheelDown::Send '{WheelDown ' speed '}'

!+WheelUp:: Send '^{PgUp}'
!+WheelDown:: Send '^{PgDn}'

!WheelUp:: Send '{WheelUp '   speed '}'
!WheelDown:: Send '{WheelDown ' speed '}'

#HotIf MouseIsAtTopOfTheScreen()
WheelUp::  Send '^{PgUp}'
WheelDown::Send '^{PgDn}'

MouseIsAtTopOfTheScreen() {  
   MouseGetPos &x, &y
   return y < 35 && x > 0 && x < A_ScreenWidth - 300
}

#HotIf GetKeyState("ScrollLock","T")
*XButton1::  {
    Send('^{PgUp}')
}
#HotIf
*XButton1::  {
    Send('{XButton1}')
}

#HotIf GetKeyState("ScrollLock","T")
*XButton2::  {
    Send('^{PgDn}')
}
#HotIf
*XButton2::  {
    Send('{XButton2}')
}

; Remapping of Numpad keys to behave as "regular Number + shift" when pressing "ctrl + Numpad Number"
^Numpad1::Send "+{1}"
^Numpad2::Send "+{2}"
^Numpad3::Send "+{3}"
^Numpad4::Send "+{4}"
^Numpad5::Send "+{5}"
^Numpad6::Send "+{6}"
^Numpad7::Send "+{7}"
^Numpad8::Send "+{8}"
^Numpad9::Send "+{9}"

; Increase Volume
#F8::Send "{Volume_Up}"

; Decrease Volume
#F7::Send "{Volume_Down}"

; Mute/Unmute Volume
#F6::Send "{Volume_Mute}"

; Increase Brightness
#F12::
{
    Run("C:\Users\Abel\Documents\Apps\nircmd\nircmd.exe changebrightness +10")
}

; Decrease Brightness
#F11::
{
    Run("C:\Users\Abel\Documents\Apps\nircmd\nircmd.exe changebrightness -10")
}

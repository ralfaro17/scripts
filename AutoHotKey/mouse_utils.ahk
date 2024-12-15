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
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

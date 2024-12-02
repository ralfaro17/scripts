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

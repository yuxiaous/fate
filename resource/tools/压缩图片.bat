::pngquanti.exe *.png -f --ext .png

@echo off
for /R "..\GamePublish" %%i in (*.png) do (
  echo %%i
  PNGoo.0.1.1\libs\pngquanti\pngquanti.exe %%i --force --ext .png --speed 1
)
pause.
@echo off

if "%1"=="@all" (
	for /f %%t in ('dir /ad/b frameworks\runtime-src\proj.android\targets') do (
		echo publish target %%t
		packAndroid.bat -t %%t -m release
	)
) else (
	for %%t in (%*) do if not %%t=="" (
		echo publish target %%t
		packAndroid.bat -t %%t -m release
	)
)


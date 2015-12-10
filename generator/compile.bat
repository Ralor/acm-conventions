@echo off
build_exe -cOb2 -d . __main__.py
upx --best __main__.exe python34.dll

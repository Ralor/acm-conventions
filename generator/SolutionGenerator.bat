@echo off
set launcher=python __main__.py
rem set launcher=__main__
set version=12

set data=data\
set sln=%data%solution.py
set vcxproj=%data%vcxproj.xml
set filters=%data%vcxproj.filters.xml
set template=%data%template.cpp
set project={upper}{number}
set src={lower}.cpp
set input={lower}.in
set local=LOCAL_PROJECT
set def=%data%cogdefinitions.ini
set custom=-D version=%version%
%launcher% %sln% %vcxproj% %filters% %template% %project% %src% %input% %local% %def% --cog %custom%

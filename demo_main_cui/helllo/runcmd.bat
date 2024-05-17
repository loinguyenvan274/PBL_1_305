@echo off
if "%1"=="" (
    set "directory=%cd%"
) else (
    set "directory=%~1"
)
dir "%directory%"

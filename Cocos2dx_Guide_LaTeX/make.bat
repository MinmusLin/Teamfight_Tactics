@echo off

chcp 65001 >nul

set THESIS=main

if "%~1" == "" (
    set flag=all
) else (
    set flag=%1
)

if not "%flag%" == "all" if not "%flag%" == "clean" (
    call :help
    goto :EOF
)

if "%flag%" == "all" (
    if exist "error.log" (
        del "error.log"
    )
    call :all
    if ERRORLEVEL 1 (
        copy "%THESIS%.log" "error.log" >nul
        call :clean
        echo Error! Please check error.log for more details.
    ) else (
        call :clean
        echo Done.
    )
    goto :EOF
)

if "%flag%" == "clean" (
    call :clean
    echo Done.
    goto :EOF
)

:all
    set TEXINPUTS=style;%TEXINPUTS%
    latexmk -xelatex -synctex=1 -quiet -interaction=nonstopmode -file-line-error -halt-on-error -shell-escape %THESIS% 2>nul
goto :EOF

:clean
    latexmk -quiet -c %THESIS% 2>nul
    del /q "%THESIS%.nav" "%THESIS%.snm" "%THESIS%.vrb" "%THESIS%.synctex.gz" 2>nul
goto :EOF

:help
    echo Usage: make [options]
    echo.
    echo Options:
    echo   - all      Use xelatex to compile the LaTeX document.
    echo   - clean    Clean temporary files.
    echo   - help     Show this help message.
    echo.
    echo Note: make without any option is equivalent to make all.
goto :EOF

exit /B 0
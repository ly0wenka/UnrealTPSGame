rem @echo off

call "%~dp0\..\..\config.bat"

rem build sources
goto:skipbuild
call "%RunUATPath%" BuildCookRun ^
-project="%ProjectPath%" ^
-platform="%Platform%" ^
-clientconfig="%Configuration%" ^
-archivedirectory="%AchivePath%" ^
-build -cook
:skipbuild

rem run tests (-nullRHI SetFilter Stress;)
"%EditorPath%" "%ProjectPath%" -ExecCmds="Automation RunTests %TestNames%.Screenshots.MainPlayerHUDShouldBeRendered" ^
 -log -abslog="%TestOutputLogPath%" -nosplash -ReportOutputPath="%ReportOutputPath%"
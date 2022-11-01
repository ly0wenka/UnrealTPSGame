@echo off

call "%~dp0\..\config.bat"

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
"%EditorPath%" "%ProjectPath%" -ExecCmds="Automation RunTests %TestNames%;Quit" ^
 -log -abslog="%TestOutputLogPath%" -nosplash -ReportOutputPath="%ReportOutputPath%"

rem copy test artifacts
set TestsDir=%~dp0
set TestsDataDir=%~dp0data
robocopy "%TestsDataDir%" "%ReportOutputPath%" /E

rem start local server and show report
set Port=8081
set Localhost=http://localhost:%Port%

pushd "%ReportOutputPath%"
start "" "%Localhost%"
call http-server -p="%Port%"
popd
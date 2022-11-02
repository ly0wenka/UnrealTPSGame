set BuildBatPath="C:\Program Files\Epic Games\UE_5.0\Engine\Build\BatchFiles\Build.bat"
set ProjectPath="E:\repos\unreal\UnrealTPSGame\TPS.uproject"
rem build
%BuildBatPath% TPSEditor Win64 Development -Project=%ProjectPath% -WaitMutex -FromMsBuild
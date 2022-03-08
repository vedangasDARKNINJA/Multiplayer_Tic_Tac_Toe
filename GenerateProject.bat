@ECHO OFF

PUSHD %~dp0
CALL premake5.exe vs2022 --opengl43
POPD

PAUSE
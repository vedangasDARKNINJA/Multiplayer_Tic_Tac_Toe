@ECHO OFF


PUSHD %~dp0
CD ..
CALL premake5.exe vs2019 --opengl43
POPD
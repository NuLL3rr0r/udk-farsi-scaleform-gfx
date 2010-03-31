SetCompress off

OutFile "../../bin/SimpleTextTool.exe"
InstallDir "$TEMP\~gs1tools"
Icon "build.ico"
SilentInstall silent

Section "MainSection" SEC01
  SetOutPath "$INSTDIR"
  SetOverwrite on
  File "mingwm10.dll"
  File "libgcc_s_dw2-1.dll"
  File "QtCore4.dll"
  File "QtGui4.dll"
  File "SimpleTextTool.exe"
  ExecWait '"$INSTDIR\SimpleTextTool.exe"'
  SetOutPath "$TEMP"
  Delete "$INSTDIR\SimpleTextTool.exe"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  RMDir "$INSTDIR"
SectionEnd


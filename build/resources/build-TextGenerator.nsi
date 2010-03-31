SetCompress off

OutFile "../../bin/TextGenerator.exe"
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
  File "QtSql4.dll"
  File "TextGenerator.exe"
  SetOutPath "$INSTDIR\sqldrivers"
  File "qsqlite4.dll"
  SetOutPath "$EXEPATH"
  ExecWait '"$INSTDIR\TextGenerator.exe" "$EXEPATH"'
  SetOutPath "$TEMP"
  Delete "$INSTDIR\TextGenerator.exe"
  Delete "$INSTDIR\mingwm10.dll"
  Delete "$INSTDIR\libgcc_s_dw2-1.dll"
  Delete "$INSTDIR\QtCore4.dll"
  Delete "$INSTDIR\QtGui4.dll"
  Delete "$INSTDIR\QtSql4.dll"
  Delete "$INSTDIR\sqldrivers\qsqlite4.dll"
  RMDir "$INSTDIR\sqldrivers"
  RMDir "$INSTDIR"
SectionEnd


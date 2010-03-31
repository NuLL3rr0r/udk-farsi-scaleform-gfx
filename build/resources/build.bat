@echo off


upx.exe -9 -o mingwm10.dll libs_mingwm10.dll
upx.exe -9 -o libgcc_s_dw2-1.dll libs_libgcc_s_dw2-1.dll
upx.exe -9 -o QtCore4.dll libs_QtCore4.dll
upx.exe -9 -o QtGui4.dll libs_QtGui4.dll
upx.exe -9 -o QtSql4.dll libs_QtSql4.dll
REM # DO NOT PACK qsqlite4.dll, causes some trouble.
copy libs_qsqlite4.dll qsqlite4.dll
upx.exe -9 -o SimpleTextTool.exe ../../src/SimpleTextTool-build/release/SimpleTextTool.exe
upx.exe -9 -o TextGenerator.exe ../../src/TextGenerator-build/release/TextGenerator.exe


makensis.exe build-SimpleTextTool.nsi
makensis.exe build-TextGenerator.nsi

del /F /S /Q mingwm10.dll
del /F /S /Q libgcc_s_dw2-1.dll
del /F /S /Q QtCore4.dll
del /F /S /Q QtGui4.dll
del /F /S /Q qsqlite4.dll
del /F /S /Q QtSql4.dll
del /F /S /Q SimpleTextTool.exe
del /F /S /Q TextGenerator.exe


cd ..


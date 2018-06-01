!include "MUI.nsh"

!define MUI_ABORTWARNING # This will warn the user if he exits from the installer.

!insertmacro MUI_PAGE_WELCOME # Welcome to the installer page.
!insertmacro MUI_PAGE_DIRECTORY # In which folder install page.
!insertmacro MUI_PAGE_INSTFILES # Installing page.
!insertmacro MUI_PAGE_FINISH # Finished installation page.

!insertmacro MUI_LANGUAGE "Portuguese"

Name "OpenICP-BR" # Name of the installer (usually the name of the application to install).
OutFile "..\bin\Instalador-OpenICP-BR.exe" # Name of the installer's file.
InstallDir "$LOCALAPPDATA\OpenICP-BR" # Default installing folder ($PROGRAMFILES is Program Files folder).
ShowInstDetails show # This will always show the installation details.
RequestExecutionLevel user

Section
	WriteUninstaller $INSTDIR\uninstaller.exe
SectionEnd
	
Section "OpenICP" # In this section add your files or your folders.
  # Add your files with "File (Name of the file)", example: "File "$DESKTOP\MyApp.exe"" ($DESKTOP is Desktop folder); or add your folders always with "File (Name of the folder)\*", always add your folders with an asterisk, example: "File /r $DESKTOP\MyApp\*" (this will add its files and (with /r its subfolders)).
  SetOutPath $INSTDIR
  File "..\bin\OpenICP.exe"
  File "..\bin\*.dll"
  File /r "..\bin\res"
  CreateDirectory "$SMPROGRAMS\OpenICP-BR"
  CreateShortCut "$SMPROGRAMS\OpenICP-BR\Remover OpenICP-BR.lnk" "$INSTDIR\uninstaller.exe"
  CreateShortCut "$SMPROGRAMS\OpenICP-BR\OpenICP-BR.lnk" "$INSTDIR\OpenICP.exe"
SectionEnd

Section "Uninstall"
	# Always delete uninstaller first
	Delete $INSTDIR\uninstaller.exe
	# now delete installed files
	RMDir /r /REBOOTOK $INSTDIR
	RMDir /r /REBOOTOK "$SMPROGRAMS\OpenICP-BR"
SectionEnd
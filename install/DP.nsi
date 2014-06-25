;NSIS Modern User Interface version 1.63


!define MUI_PRODUCT "Developer Playground" ;Name
!define MUI_VERSION "Version 1.1" ;Define your own software version here

!include "MUI.nsh"

;--------------------------------
;Configuration

  ;General
  OutFile "DPSetup.exe"

  ;Folder selection page
  InstallDir "$PROGRAMFILES\${MUI_PRODUCT}"
  
  ;Remember install folder
  InstallDirRegKey HKCU "Software\${MUI_PRODUCT}" ""

;--------------------------------
;Modern UI Configuration

  !define MUI_LICENSEPAGE
  !define MUI_COMPONENTSPAGE
  !define MUI_DIRECTORYPAGE
  
  !define MUI_ABORTWARNING
  
  !define MUI_UNINSTALLER
  !define MUI_UNCONFIRMPAGE
  
;--------------------------------
;Languages
 
  !insertmacro MUI_LANGUAGE "English"
  
;--------------------------------
;Language Strings

  ;Description
  LangString DESC_SecCopyUI ${LANG_ENGLISH} "Install Developer Playground."
  LangString DESC_SecShortCuts ${LANG_ENGLISH} "Install Start Menu Shortcuts."
  

;--------------------------------
;Data
  
  LicenseData "License.txt"

;--------------------------------
;Installer Sections

Section "Developer Playground" SecCopyUI

  SetOutPath "$INSTDIR"
  ;File "DPHelper.dll"
  File "DPInfiltrator.dll"
  File "DP.exe"
  File "license.txt"	
  
  SetOutPath $INSTDIR\help
  ;File /r "help\*.*"
    
  ;Store install folder
  WriteRegStr HKCU "Software\${MUI_PRODUCT}" "" $INSTDIR
  
  ;Create uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  ;RegDLL "$INSTDIR\DPHelper.dll"

SectionEnd

; optional section
Section "Start Menu Shortcuts" SecShortCuts
  CreateDirectory "$SMPROGRAMS\Developer Playground"
  CreateShortCut "$SMPROGRAMS\Developer Playground\Developer Playground.lnk" "$INSTDIR\DP.EXE" "" "$INSTDIR\DP.EXE" 0
  CreateShortCut "$SMPROGRAMS\Developer Playground\Documentation.lnk" "$INSTDIR\help\index.htm" "" "$INSTDIR\help\index.htm" 0
SectionEnd


;Display the Finish header
;Insert this macro after the sections if you are not using a finish page
;!insertmacro MUI_SECTIONS_FINISHHEADER

;--------------------------------
;Descriptions

!insertmacro MUI_FUNCTIONS_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SecCopyUI} $(DESC_SecCopyUI)
!insertmacro MUI_FUNCTIONS_DESCRIPTION_END
 
;--------------------------------
;Uninstaller Section

Section "Uninstall"

  ;ADD YOUR OWN STUFF HERE!
  UnRegDLL "$INSTDIR\DPHelper.dll"

  Delete $INSTDIR\license.txt
  Delete $INSTDIR\DPHelper.dll 
  Delete $INSTDIR\DPInfiltrator.dll 
  Delete $INSTDIR\DP.exe
  Delete $INSTDIR\help\*.*
 
  Delete "$SMPROGRAMS\Developer Playground\*.*"  
  RMDir "$INSTDIR\help"
  RMDir "$SMPROGRAMS\Developer Playground"
  RMDir /r "$INSTDIR"

  DeleteRegKey /ifempty HKCU "Software\${MUI_PRODUCT}"
  
  ;Display the Finish header
  ;!insertmacro MUI_UNFINISHHEADER

SectionEnd
[Setup]
AppName=Host
AppVersion=1.0
DefaultDirName={commonpf}\Host
DefaultGroupName=Host
OutputDir=../build/Install_Output
OutputBaseFilename=HostSetup
Compression=lzma
SolidCompression=yes
SetupIconFile=../squares.ico
ArchitecturesInstallIn64BitMode=x64os

[Files]
Source: "../build/Release/Host.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "../build/Release/config.ini"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{autoprograms}\Host"; Filename: "{app}\Host.exe"

[Run]
Filename: "reg"; Parameters: "add HKCU\Software\Microsoft\Windows\CurrentVersion\Run /v Host /d ""{app}\Host.exe"" /f"; Flags: runhidden
Filename: "icacls"; Parameters: """{app}\config.ini"" /grant Everyone:(F)"; Flags: runhidden

; Uninstall entries
[UninstallDelete]
Type: files; Name: "{app}\Host.exe"
Type: files; Name: "{app}\config.ini"
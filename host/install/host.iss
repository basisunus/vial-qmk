[Setup]
AppName=Host
AppVersion=1.0
DefaultDirName={pf}\Host
DefaultGroupName=Host
OutputBaseFilename=HostSetup
Compression=lzma
SolidCompression=yes

[Files]
Source: "Host.exe"; DestDir: "{app}"; Flags: ignoreversion

[Icons]
Name: "{autoprograms}\MyApp"; Filename: "{app}\MyApp.exe"; Tasks: "desktopicon"

[Run]
Filename: "reg"; Parameters: "add HKCU\Software\Microsoft\Windows\CurrentVersion\Run /v MyApp /d ""{app}\MyApp.exe"" /f"; Flags: runhidden
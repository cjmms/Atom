; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define MyAppName "Space Jump"
#define MyAppVersion "1.0"
#define MyAppPublisher "Atom, Inc."
#define MyAppURL "https://abhikalpunakal.com"
#define MyAppExeName "Atom.exe"

[Setup]
; NOTE: The value of AppId uniquely identifies this application. Do not use the same AppId value in installers for other applications.
; (To generate a new GUID, click Tools | Generate GUID inside the IDE.)
AppId={{E7266615-9098-484A-9D6E-B1C8F91EF174}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={autopf}\Atom
DisableProgramGroupPage=yes
LicenseFile=copyright\DigiPen_EULA.txt
InfoBeforeFile=copyright\Welcome.txt
InfoAfterFile=copyright\Done.txt
; Remove the following line to run in administrative install mode (install for all users.)
PrivilegesRequired=lowest
OutputDir=package
OutputBaseFilename=space_jump_setup
SetupIconFile=logos\icon.ico
RestartIfNeededByRun=no
ArchitecturesAllowed=x64
WizardSmallImageFile=logos\banner.bmp
WizardImageFile=logos\digipen_atom_game_panel.bmp
Compression=lzma
SolidCompression=yes
WizardStyle=modern

[Languages]
Name: "english"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 6.1; Check: not IsAdminInstallMode
Name: "uninstallicon"; Description: "Start menu shortcut for unistaller"; GroupDescription: "{cm:AdditionalIcons}";

[Files]
Source: "app\Atom.exe"; DestDir: "{app}"; Flags: ignoreversion
;Source: "app\Atom.pdb"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\fmod.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\fmodstudio.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\fsbank.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\libfsbvorbis64.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\opus.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "copyright\DigiPen_EULA.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "app\Atom\res\*"; DestDir: "{app}/Atom/res"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "redist\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "logos\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; NOTE: Don't use "Flags: ignoreversion" on any shared system files

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; Tasks: uninstallicon
Name: "{group}\Uninstall-{#MyAppName}"; Filename: "{uninstallexe}"; Tasks: uninstallicon
Name: "{autodesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\VC_redist.x64.exe"; Parameters: "/install /quiet /norestart"; StatusMsg: "Installing Microsoft vs2019 Redistributable";
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent;
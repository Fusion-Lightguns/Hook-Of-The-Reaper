#ifndef GLOBAL_H
#define GLOBAL_H

#include <qobject.h>

//Global Settings
#define MAXPLAYERLIGHTGUNS      4
#define UNASSIGN                69

#define NOGUIARG                "-nogui"

//Serial COM Port Data
//Max Number of COM Ports
#define MAXCOMPORTS             20
#define BEGINCOMPORTNAME        "COM"

//Number of Different Settings
#define BAUD_NUMBER             8
#define DATABITS_NUMBER         4
#define PARITY_NUMBER           5
#define STOPBITS_NUMBER         3
#define FLOW_NUMBER             3

//Arrays that Store the Different Settings
//Located in the Top of hookOfTheReaper.cpp
extern QString BAUDNAME_ARRAY[];
extern qint32  BAUDDATA_ARRAY[];
extern QString DATABITSNAME_ARRAY[];
extern quint8  DATABITSDATA_ARRAY[];
extern QString PARITYNAME_ARRAY[];
extern quint8  PARITYDATA_ARRAY[];
extern QString STOPBITSNAME_ARRAY[];
extern quint8  STOPBITSDATA_ARRAY[];
extern QString FLOWNAME_ARRAY[];
extern quint8  FLOWDATA_ARRAY[];


//Default Light Gun Definition - There is No Zero, so 2 is 1
#define NUM_DEFAULTLG           2

//First Default Light Gun
//Retro Shooter: RS3 Reaper
#define RS3_REAPER              1
#define REAPERNAME              "Retro Shooter: RS3 Reaper"
#define REAPERBAUD              0
#define REAPERDATA              0
#define REAPERPARITY            0
#define REAPERSTOP              0
#define REAPERFLOW              0
#define REAPERMAXAMMO           "5"
#define REAPERRELOAD            "6"
#define REAPERMAXAMMONUM        5
#define REAPERRELOADNUM         6

//Struct that Stores the Default Light gun Data
struct S_DEFAULTLG
{
    quint8 BAUD;
    quint8 DATA;
    quint8 PARITY;
    quint8 STOP;
    quint8 FLOW;
    QString MAXAMMO;
    QString RELOADVALUE;
    quint16 MAXAMMON;
    quint16 RELOADVALUEN;
};

extern S_DEFAULTLG DEFAULTLG_ARRAY[];


//TCP Socket
//Address Name & Port Number
#define TCPHOSTNAME             "localhost"
#define TCPHOSTPORT             8000
//Time to Wait for TCP Socket Connection (msec)
#define TIMETOWAIT              10000
//Time for the TCP Socket Timer (msec)
#define TCPTIMERTIME            10200



//File & Dir Data

#define ENDOFFILE               "END_OF_FILE"

//Saved Light Gun & COM Devices Files & Dir
#define DATAFILEDIR             "data"
#define LIGHTGUNSAVEFILE        "lightguns.hor"
#define COMDEVICESAVEFILE       "comdevices.hor"
#define STARTLIGHTGUNSAVEFILE   "Light Gun Data File"
#define PLAYERSASSIGNMENTS      "Player Assignments"
#define STARTCOMDEVICESAVEFILE  "COM Device Data File"
#define LIGHTGUNNUMBERFILE      "Light Gun #"
#define COMDEVICENUMBERFILE     "COM Device #"

//INI Game & Default Files
#define INIFILEDIR              "ini"
#define INIMAMEFILEDIR          "MAME"
#define ENDOFINIFILE            ".ini"
#define INIDEFAULTFILE          "iniDefault.hor"
#define JUSTMAME                "Mame"
#define SIGNALSTATE             "Output"

//Default Light Gun Game & Default Files
#define DEFAULTLGDIR            "defaultLG"
#define ENDOFLGFILE             ".txt"
#define LGDEFAULTFILE           "lgDefault.hor"



//Settings
#define SETTINGSSAVEFILE        "settings.hor"
#define STARTSETTINGSFILE       "Settings"
#define DEFAULTREFRESHDISPLAY   400

//Input Masks for Refresh Display Time in Settings
#define REFRESHDISPLAYMASK      "000000"



//Display
#define GAMEINFO                "Game Info:"
#define GAMEINFODASHES          "------------"
#define ROMEQUALS               "ROM="
#define ORIENTATIONEQUAL0       "Orientation=0"
#define PAUSEEQUALS0            "Pause=0"
#define OUTPUTSIGNALS           "Output Signals:"
#define OUTPUTSIGNALSDASHES     "-----------------"
#define PAUSEEQUALS             "Pause = "
#define PAUSEINDEX              5
#define ORIENTATIONINDEX        4
#define MAMENOGAMEEMPTY         "___empty"





//Process TCP Socket Data
#define MAMESTART               "mame_start = "
#define MAMESTARTNOGAME         "mame_start = ___empty"
#define MAMESTOPFRONT           "mame_stop"
//Used In TCPReadReady
#define MAMEENDLINE             "\r"
#define STATECHANGE             "statechange"
#define PAUSE                   "pause"
#define ROTATE                  "rotate"
#define REFRESHTIME             "refreshtime"
#define ORIENTATION             "Orientation"




//Processing INI & Default Light Gun
#define MAMESTARTAFTER          "mame_start"

//Process INI Commands
#define PORTCMDSTART1           "cm"
#define PORTCMDSTART2           "cs"
#define COMPORTOPEN             "cmo"
#define COMPORTCLOSE            "cmc"
#define COMPORTSETTINGS         "css"
#define COMPORTSETLINE          "csl"
#define COMPORTREAD             "cmr"
#define COMPORTWRITE            "cmw"
#define BAUDREMOVE               0,5
#define PARITYREMOVE             0,7
#define DATAREMOVE               0,5
#define STOPREMOVE               0,5
#define SIGNALDATAVARIBLE       "%s%"
#define ININULLCMD              "nll"

struct INIPortStruct
{
    qint32 baud;
    quint8 data;
    quint8 parity;
    quint8 stop;
};


//Process Default LG Game File
#define PLAYERSSTART            "Players"
#define SIGNALSTARTCHAR         ':'
#define PLAYERSTARTCHAR         '*'
#define COMMANDSTARTCHAR        '>'

//Process Default LG Commands
#define CMDSIGNAL               '>'
#define OPENCOMPORT             ">Open_COM"
#define OPENCOMPORT2CHAR        "O"
#define CLOSECOMPORT            ">Close_COM"
#define CLOSECOMPORT2CHAR       "C"
#define DAMAGECMD               ">Damage"
#define RECOILCMD               ">Recoil"
#define RELOADCMD               ">Reload"
#define AMMOCMD                 ">Ammo"
#define AMMOCMDCOUNT            5
#define AMMOVALUECMD            ">Ammo_Value"
#define SHAKECMD                ">Shake"
#define AUTOLEDCMD              ">Auto_LED"
#define ARATIO169CMD            ">AspectRatio_16:9"
#define ARATIO169CMD13CHAR      "1"
#define ARATIO43CMD             ">AspectRatio_4:3"
#define JOYMODECMD              ">Joystick_Mode"
#define KANDMMODECMD            ">Keyboard_Mouse_Mode"
#define ALLPLAYERS              "*All"
#define DLGNULLCMD              ">Null"



//Not Used Yet, But Needed for Future
//#define DEFAULTCDDIR            "defaultCD"


#endif // GLOBAL_H

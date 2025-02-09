#ifndef LIGHTGUN_H
#define LIGHTGUN_H


#include <QSerialPortInfo>

#include <QObject>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
//#include <QDebug>

class LightGun
{
public:
    //Constructors
    LightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, qint32 cpBaud, quint8 cpDataBits, quint8 cpParity, quint8 cpStopBits, quint8 cpFlow, quint16 maNumber, quint16 rvNumber);
    LightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, qint32 cpBaud, quint8 cpDataBits, quint8 cpParity, quint8 cpStopBits, quint8 cpFlow);
    LightGun(LightGun const &lgMember);
    LightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, qint32 cpBaud, quint8 cpDataBits, quint8 cpParity, quint8 cpStopBits, quint8 cpFlow, bool dipSwitchSet, quint8 dipSwitchNumber);


    //Set Functions that Sets the Stated Variable
    void SetDefaultLightGun(bool lgDefault);
    void SetDefaultLightGunNumer(quint8 dlgNum);
    void SetLightGunName(QString lgnString);
    void SetLightGunNumber(quint8 lgNumber);
    void SetComPortNumber(quint8 cpNumber);
    void SetComPortString(QString cpString);
    void SetComPortInfo(QSerialPortInfo cpInfo);
    void SetComPortBaud(qint32 cpBaud);
    void SetComPortDataBits(quint8 cpDataBits);
    void SetComPortParity(quint8 cpParity);
    void SetComPortStopBits(quint8 cpStopBits);
    void SetComPortFlow(quint8 cpFlow);
    void SetMaxAmmo(quint8 maNumber);
    void SetReloadValue(quint8 rvNumber);
    void SetDipSwitchPlayerNumber(quint8 dsNumber);

    //Get Functions that Gets the Stated Variable
    bool GetDefaultLightGun();
    quint8 GetDefaultLightGunNumber();
    QString GetLightGunName();
    quint8 GetLightGunNumber();
    quint8 GetComPortNumber();
    QString GetComPortString();
    QSerialPortInfo GetComPortInfo();
    qint32 GetComPortBaud();
    quint8 GetComPortDataBits();
    quint8 GetComPortParity();
    quint8 GetComPortStopBits();
    quint8 GetComPortFlow();
    quint8 GetMaxAmmo();
    quint8 GetReloadValue();
    quint8 GetDipSwitchPlayerNumber(bool &isSet);

    //If a Default Light Gun, is Needed Varibles Set
    bool IsMaxAmmoSet();
    bool IsReloadValueSet();


    //Copies a Light Gun - Used when Deleting a Light Gun
    //To move higher up Light guns Down 1
    void CopyLightGun(LightGun const &lgMember);


    //Load Default Light Gun Commands
    void LoadDefaultLGCommands();

    QStringList SplitLoadedCommands(QString commandList);

    //Sends Out the Needed Commands for a Default Light Gun
    //Used In the Hooker Engine
    QStringList OpenComPortCommands(bool &isSet);
    QStringList CloseComPortCommands(bool &isSet);
    QStringList DamageCommands(bool &isSet);
    QStringList RecoilCommands(bool &isSet);
    QStringList ReloadCommands(bool &isSet);
    QStringList AmmoCommands(bool &isSet);
    QStringList AmmoValueCommands(bool &isSet, quint16 ammoValue);
    QStringList ShakeCommands(bool &isSet);
    QStringList AutoLEDCommands(bool &isSet);
    QStringList AspectRatio16b9Commands(bool &isSet);
    QStringList AspectRatio4b3Commands(bool &isSet);
    QStringList JoystickModeCommands(bool &isSet);
    QStringList MouseAndKeyboardModeCommands(bool &isSet);


private:


    ///////////////////////////////////////////////////////////////////////////

    //Default Light Gun
    bool                defaultLightGun;
    quint8              defaultLightGunNum;
    quint16             maxAmmo;
    quint16             reloadValue;
    bool                maxAmmoSet;
    bool                reloadValueSet;

    //Light Gun Name & Number
    quint8              lightGunNum;
    QString             lightGunName;

    //COM Port Info
    quint8              comPortNum;
    QString             comPortString;
    QSerialPortInfo     comPortInfo;
    qint32              comPortBaud;
    quint8              comPortDataBits;
    quint8              comPortParity;
    quint8              comPortStopBits;
    quint8              comPortFlow;

    quint8              dipSwitchPlayerNumber;
    bool                isDipSwitchPlayerNumberSet;

    QString             currentPath;
    QString             dataPath;
    QString             defaultLGFilePath;

    //Commands QStringLists
    QStringList         openComPortCmds;
    QStringList         closeComPortCmds;
    QStringList         damageCmds;
    QStringList         recoilCmds;
    QStringList         reloadCmds;
    QStringList         ammoCmds;
    QStringList         ammoValueCmds;
    QStringList         shakeCmds;
    QStringList         autoLedCmds;
    QStringList         aspect16x9Cmds;
    QStringList         aspect4x3Cmds;
    QStringList         joystickCmds;
    QStringList         keyMouseCmds;

    bool                openComPortCmdsSet;
    bool                closeComPortCmdsSet;
    bool                damageCmdsSet;
    bool                recoilCmdsSet;
    bool                reloadCmdsSet;
    bool                ammoCmdsSet;
    bool                ammoValueCmdsSet;
    bool                shakeCmdsSet;
    bool                autoLedCmdsSet;
    bool                aspect16x9CmdsSet;
    bool                aspect4x3CmdsSet;
    bool                joystickCmdsSet;
    bool                keyMouseCmdsSet;

    quint16             lastAmmoValue;



};

#endif // LIGHTGUN_H

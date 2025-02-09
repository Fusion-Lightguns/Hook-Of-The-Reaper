#include "ComDeviceList.h"

//Constructor
ComDeviceList::ComDeviceList()
{
    quint8 i;
    bool canMKDIR = true;

    //Set Defaults
    numberLightGuns = 0;
    numberComPortDevices = 0;
    useDefaultLGFirst = true;

    //More Set Defaults
    for(quint8 comPortIndx=0;comPortIndx<MAXCOMPORTS;comPortIndx++)
    {
        availableComPorts[comPortIndx] = true;
        p_lightGunList[comPortIndx] = nullptr;
        p_comPortDeviceList[comPortIndx] = nullptr;
    }

    //More Set Defaults
    for(i = 0; i < MAXPLAYERLIGHTGUNS; i++)
    {
        playersLightGun[i] = UNASSIGN;
    }

    //Get Current Path
    currentPath = QDir::currentPath();


    //qDebug() << currentPath;
    currentPathDir.setPath (currentPath);

    //Check if data Directory Exsits
    dataDirExists = currentPathDir.exists (DATAFILEDIR);

    //If Not, then Make Directory
    if(!dataDirExists)
    {
        //qDebug() << "Dir DOES NOT exists";
        currentPathDir.mkdir (DATAFILEDIR);
    }

    dataPath = currentPath + "/" + DATAFILEDIR;

    //Define Save Files and Their Paths
    lightGunsSaveFile = dataPath + "/" + LIGHTGUNSAVEFILE;
    comDevicesSaveFile = dataPath + "/" + COMDEVICESAVEFILE;
    settingsSaveFile = dataPath + "/" + SETTINGSSAVEFILE;

    //Checks For INI Directory
    iniDirExists = currentPathDir.exists (INIFILEDIR);


    //If Not, then Make Directory
    if(!iniDirExists)
        canMKDIR = currentPathDir.mkdir (INIFILEDIR);
    else
        canMKDIR = true;

    //qDebug() << "Current Path: " << currentPath;
    //qDebug() << "iniDirExists: " << iniDirExists << " canMKDIR: " << canMKDIR;

    if(!canMKDIR)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not make the directory ini. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    currentPathDir.setPath (currentPath+"/"+INIFILEDIR);

    //Checks For MAME Directory
    iniMAMEDirExists = currentPathDir.exists (INIMAMEFILEDIR);

    //If Not, then Make Directory
    if(!iniMAMEDirExists)
        currentPathDir.mkdir (INIMAMEFILEDIR);


    //Set Dir back to Current Path
    currentPathDir.setPath (currentPath);

    //Load Light Gun Data
    LoadLightGunList();

    //Load COM Device Data
    LoadComDeviceList();

    //Load Seetings
    LoadSettings();

}

//Deconstructor
ComDeviceList::~ComDeviceList()
{
    //Clean Up Pointers
    for(quint8 deleteIndx=0;deleteIndx<MAXCOMPORTS;deleteIndx++)
    {
        if(p_lightGunList[deleteIndx] != nullptr)
            delete p_lightGunList[deleteIndx];
        if(p_comPortDeviceList[deleteIndx] != nullptr)
            delete p_comPortDeviceList[deleteIndx];
    }
}

//Add Light Gun to the List
void ComDeviceList::AddLightGun(LightGun const &lgMember)
{
    quint8 usedComPortNum;

    p_lightGunList[numberLightGuns] = new LightGun(lgMember);

    usedComPortNum = p_lightGunList[numberLightGuns]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberLightGuns++;
}

void ComDeviceList::AddLightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, quint32 cpBaud, quint16 cpDataBits, quint16 cpParity, quint16 cpStopBits, quint16 cpFlow, quint16 maNumber, quint16 rvNumber)
{
    quint8 usedComPortNum;

    p_lightGunList[numberLightGuns] = new LightGun(lgDefault, dlgNum, lgName, lgNumber, cpNumber, cpString, cpInfo, cpBaud, cpDataBits, cpParity, cpStopBits, cpFlow, maNumber, rvNumber);

    usedComPortNum = p_lightGunList[numberLightGuns]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberLightGuns++;
}

void ComDeviceList::AddLightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, quint32 cpBaud, quint16 cpDataBits, quint16 cpParity, quint16 cpStopBits, quint16 cpFlow)
{
    quint8 usedComPortNum;

    p_lightGunList[numberLightGuns] = new LightGun(lgDefault, dlgNum, lgName, lgNumber, cpNumber, cpString, cpInfo, cpBaud, cpDataBits, cpParity, cpStopBits, cpFlow);

    usedComPortNum = p_lightGunList[numberLightGuns]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberLightGuns++;
}

void ComDeviceList::AddLightGun(bool lgDefault, quint8 dlgNum, QString lgName, quint8 lgNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, quint32 cpBaud, quint16 cpDataBits, quint16 cpParity, quint16 cpStopBits, quint16 cpFlow, bool dipSwitchSet, quint8 dipSwitchNumber)
{
    quint8 usedComPortNum;

    p_lightGunList[numberLightGuns] = new LightGun(lgDefault, dlgNum, lgName, lgNumber, cpNumber, cpString, cpInfo, cpBaud, cpDataBits, cpParity, cpStopBits, cpFlow, dipSwitchSet, dipSwitchNumber);

    usedComPortNum = p_lightGunList[numberLightGuns]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberLightGuns++;
}


//Add COM Devices to the List
void ComDeviceList::AddComPortDevice(ComPortDevice const &cpdMember)
{
    quint8 usedComPortNum;

    p_comPortDeviceList[numberComPortDevices] = new ComPortDevice(cpdMember);

    usedComPortNum = p_comPortDeviceList[numberComPortDevices]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberComPortDevices++;
}

void ComDeviceList::AddComPortDevice(QString cpdString, quint8 cpdNumber, quint8 cpNumber, QString cpString, QSerialPortInfo cpInfo, quint32 cpBaud, quint16 cpDataBits, quint16 cpParity, quint16 cpStopBits, quint16 cpFlow)
{
    quint8 usedComPortNum;

    p_comPortDeviceList[numberComPortDevices] = new ComPortDevice(cpdString, cpdNumber, cpNumber, cpString, cpInfo, cpBaud, cpDataBits, cpParity, cpStopBits, cpFlow);

    usedComPortNum = p_comPortDeviceList[numberComPortDevices]->GetComPortNumber ();
    availableComPorts[usedComPortNum] = false;

    numberComPortDevices++;
}

void ComDeviceList::CopyAvailableComPortsArray(bool *targetArray, quint8 size)
{
    for (quint8 i = 0; i < size; i++)
    {
        *(targetArray + i) = *(availableComPorts + i);
    }
}

//Get Numbers in Certain Lists
quint8 ComDeviceList::GetNumberLightGuns()
{
    return numberLightGuns;
}

quint8 ComDeviceList::GetNumberComPortDevices()
{
    return numberComPortDevices;
}

//Switch Available COM Port
void ComDeviceList::SwitchComPortsInList(quint8 oldPort, quint8 newPort)
{
    availableComPorts[oldPort] = true;
    availableComPorts[newPort] = false;
}

//Delete a Certain Light Gun in the List
void ComDeviceList::DeleteLightGun(quint8 lgNumber)
{
    quint8 index;
    quint8 openComPort;

    openComPort = p_lightGunList[lgNumber]->GetComPortNumber ();
    availableComPorts[openComPort] = true;

    //Only One Light Gun In the List
    if(numberLightGuns == 1 && lgNumber == 0)
    {
        delete p_lightGunList[lgNumber];
        p_lightGunList[numberLightGuns] = nullptr;
        numberLightGuns--;

        for(index = 0; index < MAXPLAYERLIGHTGUNS; index++)
        {
            playersLightGun[index] = UNASSIGN;
        }

    }
    else if((lgNumber+1) == numberLightGuns)
    {
        //Targeted Light Gun is the Last in the List. So Don't have to Move Light guns Around
        delete p_lightGunList[lgNumber];
        p_lightGunList[numberLightGuns] = nullptr;
        numberLightGuns--;

        for(index = 0; index < MAXPLAYERLIGHTGUNS; index++)
        {
            if(playersLightGun[index] == lgNumber)
                playersLightGun[index] = UNASSIGN;
        }
    }
    else if(lgNumber < numberLightGuns)
    {
        //Move Higher Light Guns Down, After the Deleted Targeted Light Gun
        for(index = lgNumber; index < (numberLightGuns-1); index++)
        {
            p_lightGunList[index]->CopyLightGun (*p_lightGunList[(index+1)]);
        }

        delete p_lightGunList[numberLightGuns];
        p_lightGunList[numberLightGuns] = nullptr;
        numberLightGuns--;

        for(index = 0; index < MAXPLAYERLIGHTGUNS; index++)
        {
            if(playersLightGun[index] == lgNumber)
                playersLightGun[index] = UNASSIGN;
            else if(playersLightGun[index] > lgNumber)
                playersLightGun[index]--;
        }
    }

}

//Delete a Certain COM Device in the List
void ComDeviceList::DeleteComDevice(quint8 cdNumber)
{
    quint8 index;
    quint8 openComPort;

    openComPort = p_comPortDeviceList[cdNumber]->GetComPortNumber ();
    availableComPorts[openComPort] = true;

    //Only One COM Device In the List
    if(numberComPortDevices == 1 && cdNumber == 0)
    {
        delete p_comPortDeviceList[cdNumber];
        p_comPortDeviceList[numberComPortDevices] = nullptr;
        numberComPortDevices--;
    }
    else if((cdNumber+1) == numberComPortDevices)
    {
        //Targeted COM Device is the Last in the List. So Don't have to Move COM Devices Around
        delete p_comPortDeviceList[cdNumber];
        p_comPortDeviceList[numberComPortDevices] = nullptr;
        numberComPortDevices--;
    }
    else if(cdNumber < numberComPortDevices)
    {
        //Move Higher COM Devices Down 1, After the Deleted Target COM Device
        for(index = cdNumber; index < (numberComPortDevices-1); index++)
        {
            p_comPortDeviceList[index]->CopyComDevice (*p_comPortDeviceList[(index+1)]);
        }

        delete p_comPortDeviceList[numberComPortDevices];
        p_comPortDeviceList[numberComPortDevices] = nullptr;
        numberComPortDevices--;
    }
}

//Players Light Gun Assignment Functions
bool ComDeviceList::AssignPlayerLightGun(quint8 playerNum, quint8 lgNum)
{
    quint8 i;
    quint8 count = 0;

    //Check if Player Number is Higher Than the Max Player
    if(playerNum >= MAXPLAYERLIGHTGUNS || lgNum == UNASSIGN)
        return false;

    //Check other Players to see if that Light Gun has Been Assign Already
    for(i = 0; i < MAXPLAYERLIGHTGUNS; i++)
    {
        if(i != playerNum)
        {
            if(playersLightGun[i] == lgNum)
            {
                if(count > 2)
                    return false;

                //Different Player Already Assign to that Light Gun. Make Old Player UNASSIGN.
                playersLightGun[i] = UNASSIGN;
                count++;
            }
        }
    }

    //Ran the Ganulet
    playersLightGun[playerNum] = lgNum;


    return true;

}

void ComDeviceList::DeassignPlayerLightGun(quint8 playerNum)
{
    playersLightGun[playerNum] = UNASSIGN;
}

quint8 ComDeviceList::GetPlayerLightGunAssignment(quint8 playerNum)
{
    if(playerNum < MAXPLAYERLIGHTGUNS)
    {
        return playersLightGun[playerNum];
    }

    return UNASSIGN;
}

//Save & Load Light guns from/to File
void ComDeviceList::SaveLightGunList()
{
    bool removedFile = true;
    bool openFile;
    quint8 i;
    QFile saveLGData(lightGunsSaveFile);

    //If Light Gun Number is Zero, then Erase Old Save File & Done
    if(numberLightGuns == 0)
    {
        if(saveLGData.exists ())
            removedFile = saveLGData.remove ();

        if(!removedFile)
        {
            QMessageBox::critical (nullptr, "File Error", "Can not remove old light gun save data file. Failed to remove. Please close program and solve file problem. Might be open or permissions changed.", QMessageBox::Ok);
            return;
        }

        return;
    }

    //Erase Old Save File, if it exisits
    if(saveLGData.exists ())
        removedFile = saveLGData.remove ();

    if(!removedFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not remove old light gun save data file. Failed to remove. Please close program and solve file problem. Might be open or permissions changed.", QMessageBox::Ok);
        return;
    }

    openFile = saveLGData.open(QIODeviceBase::WriteOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not create light gun save data file. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream out(&saveLGData);

    out << STARTLIGHTGUNSAVEFILE << "\n";
    out << numberLightGuns << "\n";


    for(i = 0; i < numberLightGuns; i++)
    {

        out << LIGHTGUNNUMBERFILE << i << "\n";

        //Light Gun Number
        out << p_lightGunList[i]->GetLightGunNumber()<< "\n";

        //Light Gun Name
        out << p_lightGunList[i]->GetLightGunName ()<< "\n";

        //Default Light Gun
        if(p_lightGunList[i]->GetDefaultLightGun())
        {
            out << "1\n";
            out << p_lightGunList[i]->GetDefaultLightGunNumber() << "\n";
        }
        else
        {
            out << "0\n";
            out << "0\n";
        }

        //COM Port Data
        out << p_lightGunList[i]->GetComPortNumber() << "\n";
        out << p_lightGunList[i]->GetComPortString() << "\n";
        out << p_lightGunList[i]->GetComPortBaud() << "\n";
        out << p_lightGunList[i]->GetComPortDataBits() << "\n";
        out << p_lightGunList[i]->GetComPortParity() << "\n";
        out << p_lightGunList[i]->GetComPortStopBits() << "\n";
        out << p_lightGunList[i]->GetComPortFlow() << "\n";

        if(p_lightGunList[i]->GetDefaultLightGun() && p_lightGunList[i]->GetDefaultLightGunNumber () == RS3_REAPER)
        {
            out << p_lightGunList[i]->GetMaxAmmo() << "\n";
            out << p_lightGunList[i]->GetReloadValue() << "\n";
        }
        else if(p_lightGunList[i]->GetDefaultLightGun() && p_lightGunList[i]->GetDefaultLightGunNumber () == MX24)
        {
            bool isDipSet;
            quint8 dipNumber = p_lightGunList[i]->GetDipSwitchPlayerNumber (isDipSet);

            if(isDipSet)
            {
                out << "1\n";
                out << dipNumber << "\n";
            }
            else
            {
                out << "0\n";
                out << "0\n";
            }
        }


    }

    out << PLAYERSASSIGNMENTS << "\n";

    for(i=0; i < MAXPLAYERLIGHTGUNS; i++)
    {
        out << playersLightGun[i] << "\n";
    }

    out << ENDOFFILE;


    //Close File
    saveLGData.close ();

}

void ComDeviceList::LoadLightGunList()
{
    bool fileExists;
    bool openFile;
    quint8 i;

    quint8 tempNumLightGuns;
    quint8 tenpLightGunNum;
    QString tempLightGunName;
    bool tempIsDefaultGun;
    quint8 tempDefaultGunNum;
    quint8 tempComPortNum;
    QString tempComPortName;
    QSerialPortInfo *p_tempComPortInfo;
    quint32 tempComPortBaud;
    quint16 tempComPortDataBits;
    quint16 tempComPortParity;
    quint16 tempComPortStopBits;
    quint16 tempComPortFlow;
    quint16 tempMaxAmmo;
    quint16 tempReloadValue;
    QString line, cmpLine;
    bool dipSet;
    quint8 dipNumber;

    QFile loadLGData(lightGunsSaveFile);

    //Check if the File Exists, as it might not be created yet. If no File, then exit out of member function
    if(loadLGData.exists() == false)
    {
        //QMessageBox::critical (nullptr, "File Error", "Can not open light gun save data file. It does not exists. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    openFile = loadLGData.open (QIODeviceBase::ReadOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not open light gun save data file to read. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream in(&loadLGData);

    //Check First Line for title
    line = in.readLine();


    if(line != STARTLIGHTGUNSAVEFILE)
    {
        //qDebug() << line;
        QMessageBox::critical (nullptr, "File Error", "Light gun save data file is corrupted. Please try to reload file, or re-enter the light guns again.", QMessageBox::Ok);
    }

    //Next Line is Number of Light Guns
    line = in.readLine();
    tempNumLightGuns = line.toUInt ();

    for(i = 0; i < tempNumLightGuns; i++)
    {
        //Get New Line From File
        line = in.readLine();

        //Line Should be "Light Gun #i"
        cmpLine = LIGHTGUNNUMBERFILE + QString::number (i);

        if(line != cmpLine)
        {
            //qDebug() << line;
            QMessageBox::critical (nullptr, "File Error", "Light gun save data file is corrupted. Please try to reload file, or re-enter the light guns again.", QMessageBox::Ok);
        }

        //Next Line is the Light Gun Number
        line = in.readLine();
        tenpLightGunNum = line.toUInt ();

        //Light Gun Name
        tempLightGunName = in.readLine();

        //Default Light Gun
        line = in.readLine();
        if(line == "0")
            tempIsDefaultGun = false;
        else
            tempIsDefaultGun = true;

        //Default Light Gun Number
        line = in.readLine();
        tempDefaultGunNum = line.toUInt ();

        //COM Port Number
        line = in.readLine();
        tempComPortNum = line.toUInt ();

        //COM Port Name
        tempComPortName = in.readLine();

        //COM Port Info
        p_tempComPortInfo = new QSerialPortInfo(tempComPortName);

        //COM Port BAUD
        line = in.readLine();
        tempComPortBaud = line.toUInt ();

        //COM Port Data Bits
        line = in.readLine();
        tempComPortDataBits = line.toUInt ();

        //COM Port Parity
        line = in.readLine();
        tempComPortParity = line.toUInt ();

        //COM Port Stop Bits
        line = in.readLine();
        tempComPortStopBits = line.toUInt ();

        //COM Port Flow
        line = in.readLine();
        tempComPortFlow = line.toUInt ();

        if(tempIsDefaultGun && tempDefaultGunNum==RS3_REAPER)
        {
            line = in.readLine();
            tempMaxAmmo = line.toUInt ();

            line = in.readLine();
            tempReloadValue = line.toUInt ();

            AddLightGun(tempIsDefaultGun, tempDefaultGunNum, tempLightGunName, tenpLightGunNum, tempComPortNum, tempComPortName, *p_tempComPortInfo, tempComPortBaud, tempComPortDataBits, tempComPortParity, tempComPortStopBits, tempComPortFlow, tempMaxAmmo, tempReloadValue);

        }
        else if(tempIsDefaultGun && tempDefaultGunNum==MX24)
        {
            line = in.readLine();
            if(line == "0")
                dipSet = false;
            else
                dipSet = true;

            line = in.readLine();
            dipNumber = line.toUInt ();

            AddLightGun(tempIsDefaultGun, tempDefaultGunNum, tempLightGunName, tenpLightGunNum, tempComPortNum, tempComPortName, *p_tempComPortInfo, tempComPortBaud, tempComPortDataBits, tempComPortParity, tempComPortStopBits, tempComPortFlow, dipSet, dipNumber);
        }
        else
        {
            AddLightGun(tempIsDefaultGun, tempDefaultGunNum, tempLightGunName, tenpLightGunNum, tempComPortNum, tempComPortName, *p_tempComPortInfo, tempComPortBaud, tempComPortDataBits, tempComPortParity, tempComPortStopBits, tempComPortFlow);
        }

    }

    //Next up is the players light gun assignments
    line = in.readLine();

    if(line != PLAYERSASSIGNMENTS)
    {
        //qDebug() << line;
        QMessageBox::critical (nullptr, "File Error", "Light gun save data file is corrupted. Player's light gun assignment failed to load. Please try to reload file, or re-enter the light guns again.", QMessageBox::Ok);
    }

    for(i=0; i < MAXPLAYERLIGHTGUNS; i++)
    {
        line = in.readLine();
        playersLightGun[i] = line.toUInt ();
    }


    //Last Line is the END_OF_FILE
    line = in.readLine();


    if(line != ENDOFFILE)
    {
        //qDebug() << line;
        QMessageBox::critical (nullptr, "File Error", "Light gun save data file is corrupted. The file did not end correctly. Please try to reload file, or re-enter the light guns again.", QMessageBox::Ok);
    }

    //Close the File
    loadLGData.close();

}


//Save & Load COM Devices from/to File
void ComDeviceList::SaveComDeviceList()
{
    bool removedFile = true;
    bool openFile;
    quint8 i;
    QFile saveCDData(comDevicesSaveFile);

    //If COM Device Number is Zero, then erase the old save file & done
    if(numberComPortDevices == 0)
    {
        if(saveCDData.exists ())
            saveCDData.remove ();
        return;
    }

    //Erase Old Save Data
    if(saveCDData.exists ())
        removedFile = saveCDData.remove ();

    if(!removedFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not remove old COM device save data file. Failed to remove. Please close program and solve file problem. Might be open or permissions changed.", QMessageBox::Ok);
        return;
    }

    openFile = saveCDData.open(QIODeviceBase::WriteOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not create COM device save data file. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream out(&saveCDData);

    out << STARTCOMDEVICESAVEFILE << "\n";
    out << numberComPortDevices << "\n";


    for(i = 0; i < numberComPortDevices; i++)
    {

        out << COMDEVICENUMBERFILE << i << "\n";

        //COM Device Number
        out << p_comPortDeviceList[i]->GetComPortDeviceNumber()<< "\n";

        //Light Gun Name
        out << p_comPortDeviceList[i]->GetComPortDeviceName ()<< "\n";


        //COM Port Data
        out << p_comPortDeviceList[i]->GetComPortNumber() << "\n";
        out << p_comPortDeviceList[i]->GetComPortString() << "\n";
        out << p_comPortDeviceList[i]->GetComPortBaud() << "\n";
        out << p_comPortDeviceList[i]->GetComPortDataBits() << "\n";
        out << p_comPortDeviceList[i]->GetComPortParity() << "\n";
        out << p_comPortDeviceList[i]->GetComPortStopBits() << "\n";
        out << p_comPortDeviceList[i]->GetComPortFlow() << "\n";


    }

    out << ENDOFFILE;


    //Close File
    saveCDData.close ();

}


void ComDeviceList::LoadComDeviceList()
{
    bool fileExists;
    bool openFile;
    quint8 i;

    quint8 tempNumComDevices;
    quint8 tenpComDeviceNum;
    QString tempComDeviceName;

    quint8 tempComPortNum;
    QString tempComPortName;
    QSerialPortInfo *p_tempComPortInfo;
    quint32 tempComPortBaud;
    quint16 tempComPortDataBits;
    quint16 tempComPortParity;
    quint16 tempComPortStopBits;
    quint16 tempComPortFlow;

    QString line, cmpLine;

    QFile loadCDData(comDevicesSaveFile);

    //Check if the File Exists, as it might not be created yet. If no File, then exit out of member function
    if(loadCDData.exists() == false)
    {
        //QMessageBox::critical (nullptr, "File Error", "Can not open COM device save data file. It does not exists. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    openFile = loadCDData.open (QIODeviceBase::ReadOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not open COM device save data file to read. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream in(&loadCDData);

    //Check First Line for title
    line = in.readLine();


    if(line != STARTCOMDEVICESAVEFILE)
    {
        //qDebug() << line;
        QMessageBox::critical (nullptr, "File Error", "COM device save data file is corrupted. Please try to reload file, or re-enter the COM devices again.", QMessageBox::Ok);
    }

    //Next Line is Number of Com Devices
    line = in.readLine();
    tempNumComDevices = line.toUInt ();

    for(i = 0; i < tempNumComDevices; i++)
    {
        //Get New Line From File
        line = in.readLine();

        //Line Should be "Light Gun #i"
        cmpLine = COMDEVICENUMBERFILE + QString::number (i);

        if(line != cmpLine)
        {
            //qDebug() << line;
            QMessageBox::critical (nullptr, "File Error", "COM device save data file is corrupted. Please try to reload file, or re-enter the COM devices again.", QMessageBox::Ok);
        }

        //Next Line is the Light Gun Number
        line = in.readLine();
        tenpComDeviceNum = line.toUInt ();

        //Light Gun Name
        tempComDeviceName = in.readLine();


        //COM Port Number
        line = in.readLine();
        tempComPortNum = line.toUInt ();

        //COM Port Name
        tempComPortName = in.readLine();

        //COM Port Info
        p_tempComPortInfo = new QSerialPortInfo(tempComPortName);

        //COM Port BAUD
        line = in.readLine();
        tempComPortBaud = line.toUInt ();

        //COM Port Data Bits
        line = in.readLine();
        tempComPortDataBits = line.toUInt ();

        //COM Port Parity
        line = in.readLine();
        tempComPortParity = line.toUInt ();

        //COM Port Stop Bits
        line = in.readLine();
        tempComPortStopBits = line.toUInt ();

        //COM Port Flow
        line = in.readLine();
        tempComPortFlow = line.toUInt ();


        AddComPortDevice(tempComDeviceName, tenpComDeviceNum, tempComPortNum, tempComPortName, *p_tempComPortInfo, tempComPortBaud, tempComPortDataBits, tempComPortParity, tempComPortStopBits, tempComPortFlow);


    }


    //Last Line is the END_OF_FILE
    line = in.readLine();


    if(line != ENDOFFILE)
    {
        //qDebug() << line;
        QMessageBox::critical (nullptr, "File Error", "COM device save data file is corrupted. The file did not end correctly. Please try to reload file, or re-enter the COM devices again.", QMessageBox::Ok);
    }

    //Close the File
    loadCDData.close();

}







//Save & Load Settings from/to File
void ComDeviceList::SaveSettings()
{
    QString rtDisplay;
    bool removedFile = true;
    bool openFile;
    quint8 i;
    QFile saveSetData(settingsSaveFile);


    //Erase Old Save Data
    if(saveSetData.exists ())
        removedFile = saveSetData.remove ();

    if(!removedFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not remove old settings save data file. Failed to remove. Please close program and solve file problem. Might be open or permissions changed.", QMessageBox::Ok);
        return;
    }

    openFile = saveSetData.open(QIODeviceBase::WriteOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not create settings save data file. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream out(&saveSetData);

    out << STARTSETTINGSFILE << "\n";

    if(useDefaultLGFirst)
        out << "1\n";
    else
        out << "0\n";

    if(useMultiThreading)
        out << "1\n";
    else
        out << "0\n";

    //Output the Refresh Time of the Display
    rtDisplay = QString::number(refreshTimeDisplay)+"\n";
    out << rtDisplay;


    out << ENDOFFILE;


    //Close File
    saveSetData.close ();

}


void ComDeviceList::LoadSettings()
{
    QString line;
    bool openFile;
    bool isNumber;
    quint8 i;
    QFile loadSetData(settingsSaveFile);

    //Check if the File Exists, as it might not be created yet. If no File, then exit out of member function
    if(loadSetData.exists() == false)
    {
        //QMessageBox::critical (nullptr, "File Error", "Can not open COM device save data file. It does not exists. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }


    openFile = loadSetData.open(QIODeviceBase::ReadOnly | QIODevice::Text);

    if(!openFile)
    {
        QMessageBox::critical (nullptr, "File Error", "Can not create settings save data file. Please close program and solve file problem. Might be permissions problem.", QMessageBox::Ok);
        return;
    }

    //Create a Text Stream, to Stream in the Data Easier
    QTextStream in(&loadSetData);

    //Check First Line for title
    line = in.readLine();


    if(!line.startsWith (STARTSETTINGSFILE))
    {
        QMessageBox::critical (nullptr, "File Error", "Settings save data file is corrupted. Please close program and solve file problem.", QMessageBox::Ok);
        return;
    }

    //Next Line is Use Default Light gun First
    line = in.readLine();

    if(line.startsWith ("1"))
    {
        useDefaultLGFirst = true;
    }
    else if(line.startsWith ("0"))
    {
        useDefaultLGFirst = false;
    }
    else
    {
        QMessageBox::critical (nullptr, "File Error", "Settings save data file is corrupted at first setting. Please close program and solve file problem.", QMessageBox::Ok);
        return;
    }


    //Next Line is Use Multi-Threading
    line = in.readLine();

    if(line.startsWith ("1"))
    {
        useMultiThreading = true;
    }
    else if(line.startsWith ("0"))
    {
        useMultiThreading = false;
    }
    else
    {
        QMessageBox::critical (nullptr, "File Error", "Settings save data file is corrupted at second setting. Please close program and solve file problem.", QMessageBox::Ok);
        return;
    }

    //Next Line is the Refresh Time for the Display
    line = in.readLine();

    refreshTimeDisplay = line.toUInt (&isNumber);

    if(!isNumber)
        refreshTimeDisplay = DEFAULTREFRESHDISPLAY;

    //Next Line is End of File
    line = in.readLine();

    if(!line.startsWith (ENDOFFILE))
    {
        QMessageBox::critical (nullptr, "File Error", "Settings save data file is corrupted at the end. Please close program and solve file problem.", QMessageBox::Ok);
        return;
    }



}

//Get & Set of the Settings
bool ComDeviceList::GetUseDefaultLGFirst()
{
    return useDefaultLGFirst;
}

void ComDeviceList::SetUseDefaultLGFirst(bool udlgFirst)
{
    useDefaultLGFirst = udlgFirst;
}


bool ComDeviceList::GetUseMultiThreading()
{
    return useMultiThreading;
}

void ComDeviceList::SetUseMultiThreading(bool umThreading)
{
    useMultiThreading = umThreading;
}

quint32 ComDeviceList::GetRefreshTimeDisplay()
{
    return refreshTimeDisplay;
}

void ComDeviceList::SetRefreshTimeDisplay(quint32 rtDisplay)
{
    refreshTimeDisplay = rtDisplay;
}
















































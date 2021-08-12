/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */


#include "messages.h"
#include "core.h"

/****************************** Messages - SCPI ******************************/

void Msg_Idn::on_dataRx()
{
    qInfo() << "IDN: " << m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (tokens.size() != 4)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->name = tokens[1];
    core->getDevInfo()->fw = tokens[3];

    QStringList tokens_ver1 = core->getDevInfo()->fw.split(" ", QString::SkipEmptyParts);

    if (tokens_ver1.size() < 2)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    QStringList tokens_ver2 = tokens_ver1[0].split(".", QString::SkipEmptyParts);

    if (tokens_ver2.size() != 3)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    int fw_major = tokens_ver2[0].toInt();
    int fw_minor = tokens_ver2[1].toInt();
    int fw_rev = tokens_ver2[2].toInt();

    QStringList tokens_req = QString(MIN_FW_VER).split(".", QString::SkipEmptyParts);

    int req_major = tokens_req[0].toInt();
    int req_minor = tokens_req[1].toInt();
    int req_rev = tokens_req[2].toInt();

    if ((fw_major < req_major) ||
        (fw_major == req_major && fw_minor < req_minor) ||
        (fw_major == req_major && fw_minor == req_minor && fw_rev < req_rev))
    {
        core->err("Firmware version " + tokens_ver1[0] + " is not supported with this application! Please upgrade.", true);
        return;
    }
}

void Msg_Rst::on_dataRx()
{
    qInfo() << "RST: " << m_rxData;
    auto core = Core::getInstance(this);

    if (!m_rxData.contains(EMBO_OK))
        core->err("Reset failed! " + m_rxData, false);
}


void Msg_Stb::on_dataRx()
{
    qInfo() << "STB: " <<  m_rxData;
    auto core = Core::getInstance(this);

    if (m_rxData.isEmpty())
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }
}

void Msg_Cls::on_dataRx()
{
}

/****************************** Messages - SYS ******************************/

void Msg_SYS_Lims::on_dataRx()
{
    qInfo() << "SYS:LIM: " <<  m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (tokens.size() != 17 || tokens[6].size() < 2 || tokens[16].size() != 4)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    auto devInfo = core->getDevInfo();

    devInfo->adc_fs_12b = tokens[0].toInt();
    devInfo->adc_fs_8b = tokens[1].toInt();
    devInfo->mem = tokens[2].toInt();
    devInfo->la_fs = tokens[3].toInt();
    devInfo->pwm_fs = tokens[4].toInt();
    devInfo->pwm2 = tokens[5] == '1';
    devInfo->daq_ch = (tokens[6])[0].digitValue();
    devInfo->adc_num = (tokens[6])[1].digitValue();
    devInfo->adc_dualmode = tokens[6].contains('D');
    devInfo->adc_interleaved = tokens[6].contains('I');
    devInfo->adc_bit8 = tokens[7] == '1';
    devInfo->dac = tokens[8].toInt();
    devInfo->vm_fs = tokens[9].toInt();
    devInfo->vm_mem = tokens[10].toInt();
    devInfo->cntr_timeout = tokens[11].toInt();
    devInfo->sgen_maxf = tokens[12].toInt();
    devInfo->sgen_maxmem = tokens[13].toInt();
    devInfo->cntr_maxf = tokens[14].toInt();
    devInfo->daq_reserve = tokens[15].toInt();
    devInfo->la_ch1_pin = tokens[16][0].toLatin1() - '0';
    devInfo->la_ch2_pin = tokens[16][1].toLatin1() - '0';
    devInfo->la_ch3_pin = tokens[16][2].toLatin1() - '0';
    devInfo->la_ch4_pin = tokens[16][3].toLatin1() - '0';
}


void Msg_SYS_Info::on_dataRx()
{
    qInfo() << "SYS:INFO: " <<  m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (tokens.size() != 10)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    auto devInfo = core->getDevInfo();

    devInfo->rtos = tokens[0];
    devInfo->ll = tokens[1];
    devInfo->comm = tokens[2];
    devInfo->fcpu = tokens[3];
    devInfo->ref_mv = tokens[4].toInt();
    devInfo->pins_scope_vm = tokens[5];
    devInfo->pins_la = tokens[6];
    devInfo->pins_cntr = tokens[7];
    devInfo->pins_pwm = tokens[8];
    devInfo->pins_sgen = tokens[9];
}

void Msg_SYS_Mode::on_dataRx()
{
    qInfo() << "SYS:MODE: " <<  m_rxData;
    auto core = Core::getInstance(this);

    if (getIsQuery())
    {
        if (m_rxData.contains("SCOPE"))
            core->setMode(SCOPE, true);
        else if (m_rxData.contains("VM"))
            core->setMode(VM, true);
        else if (m_rxData.contains("LA"))
            core->setMode(LA, true);
        else
            core->err(INVALID_MSG + m_rxData, true);
    }
    else
    {
        if (!m_rxData.contains(EMBO_OK))
            core->err("Mode set failed! " + m_rxData, true);
    }
}

void Msg_SYS_Uptime::on_dataRx()
{
    qInfo() << "SYS:UPT: " <<  m_rxData;
    auto core = Core::getInstance(this);

    if (m_rxData.size() < 10)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->setUptime(m_rxData);
}

void Msg_Dummy::on_dataRx()
{
    qInfo() << "STB: " <<  m_rxData;

    Core::getInstance()->openCommInit();
}

/***************************** Messages - VM ****************************/

void Msg_VM_Read::on_dataRx()
{
    qInfo() << "VM:READ: " <<  m_rxData;

    if (m_rxData.contains("Empty"))
        return;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (tokens.size() != 5)
    {
        emit err(INVALID_MSG + m_rxData, CRITICAL, true);
        return;
    }

    emit result(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}

/***************************** Messages - SCOP **************************/

void Msg_SCOP_Read::on_dataRx()
{
    qInfo() << "SCOP:READ: size: " <<  m_rxDataBin.size();
    //qInfo () << m_rxDataBin.toHex();

    emit result(m_rxDataBin);
}

void Msg_SCOP_Set::on_dataRx()
{
    qInfo() << "SCOP:SET: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

        if (tokens.size() != 12)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        DaqBits bits = B1;
        DaqTrigEdge edge = RISING;
        DaqTrigMode mode = DISABLED;

        if (tokens[0] == "8") bits = B8;
        else if (tokens[0] == "12") bits = B12;

        if (tokens[6] == "F") edge = FALLING;
        else if (tokens[6] == "B") edge = BOTH;

        if (tokens[7] == "A") mode = AUTO;
        else if (tokens[7] == "N") mode = NORMAL;
        else if (tokens[7] == "S") mode = SINGLE;

        double maxZ = tokens[9].toDouble();
        if (maxZ < 0)
            maxZ = 10;

        emit result(bits, tokens[1].toInt(), tokens[2].toInt(),
                    tokens[3][0] == '1', tokens[3][1] == '1', tokens[3][2] == '1', tokens[3][3] == '1',
                    tokens[4].toInt(), tokens[5].toInt(), edge, mode, tokens[8].toInt(),
                    maxZ, tokens[10].toDouble() / 1000000000.0, tokens[11].toDouble(), tokens[11]);
    }
    else
    {
        if (tokens.size() != 4 && !m_rxData.contains(EMBO_OK))
        {
            emit err("SCOPE set failed! " + m_rxData, CRITICAL, true);
            return;
        }

        double maxZ = tokens[1].toDouble();
        if (maxZ < 0)
            maxZ = 10;

        emit ok2(maxZ, tokens[2].toDouble() / 1000000000.0, tokens[3].toDouble(), tokens[3]);
    }
}

void Msg_SCOP_ForceTrig::on_dataRx()
{
    qInfo() << "SCOP:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    emit ok();
}

/***************************** Messages - LA ****************************/

void Msg_LA_Read::on_dataRx()
{
    qInfo() << "LA:READ: size: " <<  m_rxDataBin.size();
    //qInfo () << m_rxDataBin.toHex();

    emit result(m_rxDataBin);
}

void Msg_LA_Set::on_dataRx()
{
    qInfo() << "LA:SET: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

        if (tokens.size() != 7)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        DaqTrigEdge edge = RISING;
        DaqTrigMode mode = DISABLED;

        if (tokens[3] == "F") edge = FALLING;
        else if (tokens[6] == "B") edge = BOTH;

        if (tokens[4] == "A") mode = AUTO;
        else if (tokens[4] == "N") mode = NORMAL;
        else if (tokens[4] == "S") mode = SINGLE;

        emit result(tokens[0].toInt(), tokens[1].toInt(), tokens[2].toInt(),
                    edge, mode, tokens[5].toInt(), tokens[6].toDouble(), tokens[6]);
    }
    else
    {
        if (tokens.size() != 2 && !m_rxData.contains(EMBO_OK))
        {
            emit err("LA set failed! " + m_rxData, CRITICAL, true);
            return;
        }

        emit ok2(tokens[1].toDouble(), tokens[1]);
    }
}

void Msg_LA_ForceTrig::on_dataRx()
{
    qInfo() << "LA:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    emit ok();
}

/***************************** Messages - CNTR **************************/

void Msg_CNTR_Enable::on_dataRx()
{
    qInfo() << "CNTR:ENA: " <<  m_rxData;

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

        if (tokens.size() != 2)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        emit result(tokens[0].contains(EMBO_TRUE), tokens[1].contains(EMBO_TRUE));
    }
    else
    {
        if (m_rxData.contains(EMBO_OK))
            emit ok();
        else
            emit err("Counter enabling failed! " + m_rxData, CRITICAL, false);
    }
}

void Msg_CNTR_Read::on_dataRx()
{
    qInfo() << "CNTR:READ: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (tokens.size() == 0)
    {
        emit err(INVALID_MSG + m_rxData, CRITICAL, true);
        return;
    }

    emit result(tokens[0], tokens.size() > 1 ? tokens[1] : "");
}

/***************************** Messages - SGEN **************************/

void Msg_SGEN_Set::on_dataRx()
{
    qInfo() << "SGEN:SET: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

        if (tokens.size() != 8)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        emit result(tokens[0].toInt(), tokens[1].toInt(), tokens[2].toInt(), tokens[3].toInt(),
                    (SgenMode)tokens[4].toInt(), tokens[5] == "1", tokens[6], tokens[7]);
    }
    else
    {
        if (tokens.size() != 3 && !m_rxData.contains(EMBO_OK))
        {
            emit err("Signal Generator set failed! " + m_rxData, CRITICAL, true);
            return;
        }

        emit ok(tokens[1], tokens[2]);
    }
}

/***************************** Messages - PWM ***************************/

void Msg_PWM_Set::on_dataRx()
{
    qInfo() << "PWM:SET: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, QString::SkipEmptyParts);

        if (tokens.size() != 7)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        emit result(tokens[0].toInt(), tokens[1].toInt(), tokens[2].toInt(), tokens[3].toInt(),
                    tokens[4] == "1", tokens[5] == "1", tokens[6]);
    }
    else
    {
        if (tokens.size() != 2 && !m_rxData.contains(EMBO_OK))
        {
            emit err("PWM Generator set failed! " + m_rxData, CRITICAL, true);
            return;
        }

        emit ok(tokens[1]);
    }
}

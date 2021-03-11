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

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 4)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->name = tokens[1];
    core->getDevInfo()->fw = tokens[2];
}

void Msg_Rst::on_dataRx()
{
    qInfo() << "RST: " << m_rxData;
    auto core = Core::getInstance(this);

    if (!m_rxData.contains(EMBO_OK))
        core->err("Reset failed!", false);
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

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 13)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->adc_fs_12b = tokens[0].toInt();
    core->getDevInfo()->adc_fs_8b = tokens[1].toInt();
    core->getDevInfo()->mem = tokens[2].toInt();
    core->getDevInfo()->la_fs = tokens[3].toInt();
    core->getDevInfo()->pwm_fs = tokens[4].toInt();
    core->getDevInfo()->adc_num = (tokens[5])[0].digitValue();
    core->getDevInfo()->adc_dualmode = tokens[5].contains('D');
    core->getDevInfo()->adc_interleaved = tokens[5].contains('I');
    core->getDevInfo()->adc_bit8 = tokens[6] == '1';
    core->getDevInfo()->dac = tokens[7] == '1';
    core->getDevInfo()->vm_fs = tokens[8].toInt();
    core->getDevInfo()->vm_mem = tokens[9].toInt();
    core->getDevInfo()->cntr_timeout = tokens[10].toInt();
    core->getDevInfo()->sgen_maxf = tokens[11].toInt();
    core->getDevInfo()->sgen_maxmem = tokens[12].toInt();
}


void Msg_SYS_Info::on_dataRx()
{
    qInfo() << "SYS:INFO: " <<  m_rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 10)
    {
        core->err(INVALID_MSG + m_rxData, true);
        return;
    }

    core->getDevInfo()->rtos = tokens[0];
    core->getDevInfo()->ll = tokens[1];
    core->getDevInfo()->comm = tokens[2];
    core->getDevInfo()->fcpu = tokens[3];
    core->getDevInfo()->ref_mv = tokens[4];
    core->getDevInfo()->pins_scope_vm = tokens[5];
    core->getDevInfo()->pins_la = tokens[6];
    core->getDevInfo()->pins_cntr = tokens[7];
    core->getDevInfo()->pins_pwm = tokens[8];
    core->getDevInfo()->pins_sgen = tokens[9];
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
            core->err("Mode set failed!", true);
    }
}

void Msg_SYS_Uptime::on_dataRx()
{
    qInfo() << "SYS:UPT: " <<  m_rxData;
    auto core = Core::getInstance(this);

    if (m_rxData.size() != 12)
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

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (tokens.size() != 5)
    {
        emit err(INVALID_MSG + m_rxData, CRITICAL, true);
        return;
    }

    Core::getInstance()->getDevInfo()->ref_mv = tokens[4];

    emit result(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4]);
}

/***************************** Messages - SCOP **************************/

void Msg_SCOP_Read::on_dataRx()
{
    qInfo() << "SCOP:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_Set::on_dataRx()
{
    qInfo() << "SCOP:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_ForceTrig::on_dataRx()
{
    qInfo() << "SCOP:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_SCOP_Average::on_dataRx()
{
    qInfo() << "SCOP:AVER: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - LA ****************************/

void Msg_LA_Read::on_dataRx()
{
    qInfo() << "LA:READ: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_LA_Set::on_dataRx()
{
    qInfo() << "LA:SET: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

void Msg_LA_ForceTrig::on_dataRx()
{
    qInfo() << "LA:FORC: " <<  m_rxData;
    //auto core = Core::getInstance(this);

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);
    // TODO parse
}

/***************************** Messages - CNTR **************************/

void Msg_CNTR_Enable::on_dataRx()
{
    qInfo() << "CNTR:ENA: " <<  m_rxData;

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

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

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

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

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

        if (tokens.size() != 5)
        {
            emit err(INVALID_MSG + m_rxData, CRITICAL, true);
            return;
        }

        // TODO
        emit result(SgenMode::CONSTANT, tokens[1].toDouble(), tokens[2].toInt(), tokens[3].toInt(),
                    tokens[4] == "1");
    }
    else
    {
        if (m_rxData.contains(EMBO_OK))
            emit ok();
        else
            emit err("Signal generator set failed! " + m_rxData, CRITICAL, false);
    }
}

/***************************** Messages - PWM ***************************/

void Msg_PWM_Set::on_dataRx()
{
    qInfo() << "PWM:SET: " <<  m_rxData;

    QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    if (getIsQuery())
    {
        QStringList tokens = m_rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

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

#include "bassresponse_ba_zgb.h"
#include <cstdio>

BassResponse_BA_ZGB::BassResponse_BA_ZGB() :
    m_Value(0)
{

}

BassResponse_BA_ZGB::~BassResponse_BA_ZGB()
{

}

QStringList BassResponse_BA_ZGB::getMsgIDs()
{
    return QStringList() << "BA" << "ZGB";
}

QString BassResponse_BA_ZGB::getResponseID()
{
    return "BassResponse";
}

bool BassResponse_BA_ZGB::parseString(QString str)
{
    if (sscanf(str.toLatin1(), "BA%d", &m_Value) == 1)
    {
        m_Zone = ZoneMain;
        return true;
    }
    if (sscanf(str.toLatin1(), "ZGB%d", &m_Value) == 1)
    {
        m_Zone = Zone2;
        return true;
    }
    return false;
}

float BassResponse_BA_ZGB::GetdBValue()
{
    float volume_dB = 0;

    switch(m_Zone)
    {
    case ZoneMain:
        volume_dB = (double)(6 - m_Value);
        break;
    case Zone2:
        volume_dB = (double)(m_Value - 50);
        break;
    default:
        break;
    }

    return volume_dB;
}

QString BassResponse_BA_ZGB::GetAsString()
{
    QString str;
    float dBValue = GetdBValue();

    str = QString("%1dB").arg(dBValue);

    return str;
}

int BassResponse_BA_ZGB::GetValue()
{
    return m_Value;
}

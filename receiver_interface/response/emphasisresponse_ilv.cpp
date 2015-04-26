#include "emphasisresponse_ilv.h"

EmphasisResponse_ILV::EmphasisResponse_ILV()
{

}

EmphasisResponse_ILV::~EmphasisResponse_ILV()
{

}

QStringList EmphasisResponse_ILV::getMsgIDs()
{
    return QStringList() << "ILV";
}

QString EmphasisResponse_ILV::getResponseID()
{
    return "EmphasisResponse";
}

bool EmphasisResponse_ILV::parseString(QString str)
{
    if (str.startsWith("ILV"))
    {
        int count = (str.length() - 3) / 2;
        m_EmData.clear();

        for (int i = 0; i < count; i++)
        {
            int n = str.mid(3 + i * 2, 2).toInt();
            m_EmData.push_back(n);
        }
        return true;
    }
    return false;
}

const QVector<int> &EmphasisResponse_ILV::GetEmphasisData()
{
    return m_EmData;
}

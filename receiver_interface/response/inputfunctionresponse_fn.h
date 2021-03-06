#ifndef INPUTFUNCTIONRESPONSE_H
#define INPUTFUNCTIONRESPONSE_H

#include "receivedobjectbase.h"
#include <QString>
#include <QMap>

class InputFunctionResponse_FN : public ReceivedObjectBase
{
public:
    InputFunctionResponse_FN();
    ~InputFunctionResponse_FN();
    virtual QString getResponseID();
    virtual QStringList getMsgIDs();
    virtual bool parseString(QString str);
    int getNumber();
    QString getName();
    const QMap<int, QString> getInputList();

protected:
    int m_inputNumber;
    static QMap<int, QString>  m_VIDEO_INPUT;

    static QMap<int, QString> _initMap();
};

#endif // INPUTFUNCTIONRESPONSE_H

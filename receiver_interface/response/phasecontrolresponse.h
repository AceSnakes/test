#ifndef PHASECONTROLRESPONSE_H
#define PHASECONTROLRESPONSE_H

#include "receivedobjectbase.h"

class PhaseControlResponse : public ReceivedObjectBase
{
public:
    PhaseControlResponse();
    ~PhaseControlResponse();
    virtual QString getResponseID();
    virtual QStringList getMsgIDs();
    virtual bool parseString(QString str);
    bool    IsPhaseControlOn();
private:
    bool    m_PhaseControlOn;
};

#endif // PHASECONTROLRESPONSE_H

#pragma once
#include "Observer.h"
#include "ProtobufModule.h"
#include "generated/meshtastic/ews.pb.h"


class EwsModule : public ProtobufModule<meshtastic_Ews>,
                  public Observable<const meshtastic_Ews *>
{
public:
    EwsModule();

protected:
    virtual bool handleReceivedProtobuf(const meshtastic_MeshPacket &mp,
                                        meshtastic_Ews *msg) override;
};

extern EwsModule *ewsModule;
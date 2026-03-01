#include "EwsModule.h"
#include "MeshService.h"
#include "MessageStore.h"
#include "NodeDB.h"
#include "PowerFSM.h"
#include "buzz.h"
#include "configuration.h"
#include "graphics/Screen.h"
#include "graphics/SharedUIDisplay.h"
#include "graphics/draw/MessageRenderer.h"
#include "main.h"
EwsModule *ewsModule;

/*
    change an ews byte into a text
*/
char * decodeEwsPayload(const pb_byte_t * ews) {
    return "Ews message recived";
}

ProcessMessage EwsModule::handleReceived(const meshtastic_MeshPacket &mp)
{
#if defined(DEBUG_PORT) && !defined(DEBUG_MUTE)
    auto &p = mp.decoded;

    LOG_INFO("Received ews msg from=0x%0x, id=0x%x, msg=%.*s", mp.from, mp.id, p.payload.size, decodeEwsPayload(p.payload.bytes));
#endif
    // add packet ID to the rolling list of packets
    //textPacketList[textPacketListIndex] = mp.id;
    //textPacketListIndex = (textPacketListIndex + 1) % TEXT_PACKET_LIST_SIZE;

/*
    // We only store/display messages destined for us.
    devicestate.rx_text_message = mp;
    devicestate.has_rx_text_message = true;
    IF_SCREEN(
        // Guard against running in MeshtasticUI or with no screen
        if (config.display.displaymode != meshtastic_Config_DisplayConfig_DisplayMode_COLOR) {
            // Store in the central message history
            const StoredMessage &sm = messageStore.addFromPacket(mp);

            // Pass message to renderer (banner + thread switching + scroll reset)
            // Use the global Screen singleton to retrieve the current OLED display
            auto *display = screen ? screen->getDisplayDevice() : nullptr;
            graphics::MessageRenderer::handleNewMessage(display, sm, mp);
        })
    // Only trigger screen wake if configuration allows it
    if (shouldWakeOnReceivedMessage()) {
        powerFSM.trigger(EVENT_RECEIVED_MSG);
    }

    // Notify any observers (e.g. external modules that care about packets)*/
    notifyObservers(&mp);

    return ProcessMessage::CONTINUE; // Let others look at this message also if they want
}
/*
bool EwsModule::recentlySeen(uint32_t id)
{
    for (size_t i = 0; i < TEXT_PACKET_LIST_SIZE; i++) {
        if (textPacketList[i] != 0 && textPacketList[i] == id) {
            return true;
        }
    }
    return false;
}
    */
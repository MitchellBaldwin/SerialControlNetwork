namespace SerialControlNetwork
{
    internal enum MRSMessageType
    {
        // Message identification codes:

        MRSStatusPacket = 0x00,             // Top level MRS status packet

        DSMCUStatusPacket = 0x04,           // Drive System status packet

        MRSTextMessage = 0x0F,              // Text message


        // Command codes:

        // 0x10 - ox1F : Request report commands
        GetMRSStatus = 0x00,

        GetDSMCUStatus = 0x04,

        // 0x20 - 0x2F : Power System commands

        // 0x40 - ox4F : Drive Ssytem MCU commands
        DSMCUDriveSettings = 0x40,
        DSMCUDriveConfiguration = 0x41,






        // 0xF0 - oxFF : Diagnostic / test commands

        ToggleBuiltInLED = 0xF8,            // Debug / test: Toggle diagnostic LED ON/OFF
        TestPacketTransfer = 0xF9,          // Debug / test: Echo command package payload as an MRSStatusReport message
        GetTestTextMessage = 0xFA,          // Request a test text message from the remote system
        TestLocalDisplay = 0xFB,            // Execute demo / test of local display hardware
        TestMotors = 0xFC,                  // Execute motors test

    }
}


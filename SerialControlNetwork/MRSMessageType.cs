namespace SerialControlNetwork
{
    internal enum MRSMessageType
    {
        // Message identification codes:

        MRSTextMessage = 0x0F,              // Text message
        MRSStatusReport = 0x10,             // Top level MRS status report


        // Command codes:

        // Drive commands:



        // Utility commands:

        

        // Debug / test commands:

        ToggleBuiltInLED = 0xF8,            // Debug / test: Toggle diagnostic LED ON/OFF
        TestPacketTransfer = 0xF9,          // Debug / test: Echo command package payload as an MRSStatusReport message
        GetTestTextMessage = 0xFA,          // Request a test text message from the remote system
        TestLocalDisplay = 0xFB,            // Execute demo / test of local display hardware
        TestMotors = 0xFC,                  // Execute motors test

    }
}


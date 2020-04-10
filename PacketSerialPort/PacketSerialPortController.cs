using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace SerialControlNetwork
{
    public class PacketSerialPortController
    {
        private byte[] ComBuffer { get; set; }
        private byte[] EncodedPacketBuffer { get; set; }
        private byte[] PacketBuffer { get; set; }
        private byte[] PacketPayloadBuffer { get; set; }

        public int ComBufferSize { get => ComBuffer.Length; }
        public int EncodedPacketSize { get => EncodedPacketBuffer.Length; }
        public int PacketSize { get => PacketBuffer.Length; }
        public int PacketPayloadSize { get => PacketPayloadBuffer.Length; }

        public SerialPort RemoteSystemComPort { get; set; }

        public PacketSerialPortController(int comBufferSize = 0x10)
        {
            RemoteSystemComPort = new SerialPort();
            ComBuffer = new byte[comBufferSize];
            EncodedPacketBuffer = new byte[ComBuffer.Length - 1];
            PacketBuffer = new byte[EncodedPacketBuffer.Length - 1];
            PacketPayloadBuffer = new byte[PacketBuffer.Length - 1];
            
        }

        public string[] GetAvailableComPortNames()
        {
            return SerialPort.GetPortNames();
        }

        public void OpenRemoteSystemComPort(out string comPortStatusMessage)
        {
            comPortStatusMessage = $"Not connected";

            try
            {
                RemoteSystemComPort.Open();
                comPortStatusMessage = $"Port opened";
            }
            catch (IOException ioe)
            {
                comPortStatusMessage = ioe.Message;
            }
            catch (InvalidOperationException ioe)
            {
                comPortStatusMessage = ioe.Message;
            }
        }
        
        public void CloseRemoteSystemComPort()
        {
            RemoteSystemComPort.Close();
        }
        
        // Helper function to format and COBS encode the ComBuffer with a command, associated data packet
        //(contained in PacketPayloadPacket) and checksum, then finally send the message over the 
        //RemoteSystemComPort
        public void SendCommandMessage(byte command, out string returnStatusMessage)
        {
            byte checkSum = 0;
            //returnStatusMessage = "";

            // Build the command message:

            for (int i = 0; i < PacketSize; ++i)
            {
                PacketBuffer[i] = 0;
            }

            PacketBuffer[0] = command;
            for (int i = 0; i < PacketPayloadSize; ++i)
            {
                PacketBuffer[1 + i] = PacketPayloadBuffer[i];
            }

            checkSum = 0x00;
            for (int i = 0; i < PacketSize - 1; ++i)
            {
                checkSum += PacketBuffer[i];
            }
            PacketBuffer[PacketSize - 1] = checkSum;

            EncodedPacketBuffer = COBS.COBSCodec.encode(PacketBuffer);
            for (int i = 0; i < ComBufferSize - 1; ++i)
            {
                ComBuffer[i] = EncodedPacketBuffer[i];
            }
            ComBuffer[ComBufferSize - 1] = 0x00;

            
            // Send the message:

            try
            {
                RemoteSystemComPort.Write(ComBuffer, 0, ComBufferSize);
                returnStatusMessage = $"{PacketBuffer[0].ToString("X2")} sent";

            }
            catch (InvalidOperationException ioe)
            {
                returnStatusMessage = $"{ioe.Message}";
            }

        }

    }
}

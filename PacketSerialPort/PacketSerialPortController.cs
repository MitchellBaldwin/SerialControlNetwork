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

        public byte[] GetComBuffer()
        {
            return ComBuffer;
        }
        public byte[] GetEncodedPacketBuffer()
        {
            return EncodedPacketBuffer;
        }
        public byte[] GetPacketBuffer()
        {
            return PacketBuffer;
        }
        public byte[] GetPacketPayloadBuffer()
        {
            return PacketPayloadBuffer;
        }

        public int ComBufferSize { get => ComBuffer.Length; }
        public int EncodedPacketSize { get => EncodedPacketBuffer.Length; }
        public int PacketSize { get => PacketBuffer.Length; }
        public int PacketPayloadSize { get => PacketPayloadBuffer.Length; }

        private System.Windows.Forms.Control ParentControl { get; set; }

        public SerialPort RemoteSystemComPort { get; set; }

        public delegate void UpdateParentsHandler(byte[] buffer);
        public UpdateParentsHandler UpdateParents { get; set; }

        public PacketSerialPortController(System.Windows.Forms.Control parentControl, int comBufferSize = 0x10)
        {
            ParentControl = parentControl;
            RemoteSystemComPort = new SerialPort();
            ComBuffer = new byte[comBufferSize];
            EncodedPacketBuffer = new byte[ComBuffer.Length - 1];
            PacketBuffer = new byte[EncodedPacketBuffer.Length - 1];
            PacketPayloadBuffer = new byte[PacketBuffer.Length - 2];

            RemoteSystemComPort.DataReceived += new SerialDataReceivedEventHandler(RemoteSystemComPort_DataReceived);

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
        public void SendCommandMessage(byte command, byte[] buffer, out string returnStatusMessage)
        {

            // Build the command message:

            for (int i = 0; i < PacketPayloadSize; ++i)
            {
                if (i < buffer.Length)
                {
                    PacketPayloadBuffer[i] = buffer[i];
                }
                else
                {
                    PacketPayloadBuffer[i] = 0x00;
                }
                
            }

            PacketBuffer[0] = command;
            for (int i = 0; i < PacketPayloadSize; ++i)
            {
                PacketBuffer[1 + i] = PacketPayloadBuffer[i];
            }

            byte checkSum = 0x00;
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
                Console.WriteLine($"{PacketBuffer[0].ToString("X2")} sent");
            }
            catch (InvalidOperationException ioe)
            {
                returnStatusMessage = $"{ioe.Message}";
            }

        }

        private void RemoteSystemComPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string PSPCDRReport;

            if (RemoteSystemComPort.BytesToRead < ComBufferSize)
            {
                return;
            }
            try
            {
                int bytesReadCount = RemoteSystemComPort.Read(ComBuffer, 0, ComBufferSize);
                PSPCDRReport = $"Received {bytesReadCount} bytes";
                if (ComBuffer[ComBufferSize - 1] != 0x00)
                {
                    PSPCDRReport = $"Serial port framing error";
                    return;
                }
                for (int i = 0; i < EncodedPacketSize; ++i)
                {
                    EncodedPacketBuffer[i] = ComBuffer[i];
                }
                PacketBuffer = COBS.COBSCodec.decode(EncodedPacketBuffer);
                
                // Test checksum

                // Determine message type and invoke handlers accordingly

                if (PacketBuffer[0] == 0x10)
                {
                    PSPCDRReport = $"Received a status packet";
                }

                // Pass received data on to intended recipient(s):
                ParentControl.Invoke(UpdateParents, ComBuffer);
            }
            catch
            {

            }
        }


    }
}

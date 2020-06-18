using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SerialControlNetwork
{
    public partial class SerialControlView : Form
    {
        //PacketSerialPortController PSPC = new PacketSerialPortController();
        
        public SerialControlView()
        {
            InitializeComponent();
        }

        private void SerialControlView_Load(object sender, EventArgs e)
        {
            MRSPSP.SetComPortName(Properties.Settings.Default.LastMRSCOMPort);
            MRSPSP.SetConnectedDeviceName("MRS1");
            MRSPSP.UpdateParents += UpdateDisplays;

            MRSRCPSP.SetComPortName(Properties.Settings.Default.LastMRSRCComPort);
            MRSRCPSP.SetConnectedDeviceName("MRS Remote Controller");
            
            Console.WriteLine(MRSPSP.PSPC.ComBufferSize);
            Console.WriteLine(MRSPSP.PSPC.EncodedPacketSize);
            Console.WriteLine(MRSPSP.PSPC.PacketSize);
            Console.WriteLine(MRSPSP.PSPC.PacketPayloadSize);

        }

        
        // MRS Controls *******************************************************************************************************
        private void TestMRSComsButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x55 };
            MRSPSP.SendCommandMessage((byte)MRSMessageType.ToggleBuiltInLED, dummy);
        }

        private void GetMRSStatusButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };
            MRSPSP.SendCommandMessage((byte)MRSMessageType.TestPacketTransfer, dummy);
        }

        private void GetMRSTestTextMessageButton_Click(object sender, EventArgs e)
        {
            // Send a text message to be locally logged / displayed and request the MRS sends a test text message back:

            string testMessage = "Test MSG";
            byte[] dummy = ASCIIEncoding.ASCII.GetBytes(testMessage);
            MRSPSP.SendCommandMessage((byte)MRSMessageType.MRSTextMessage, dummy);
            MRSPSP.SendCommandMessage((byte)MRSMessageType.GetTestTextMessage, dummy);
        }

        private void MRSSYSDiagnosticsButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x00 };
            MRSPSP.SendCommandMessage((byte)MRSMessageType.TestLocalDisplay, dummy);
        }


        // MRS Remote Controller Controls *************************************************************************************
        private void TestMRSRCComsButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0xAA };
            //PSPPanel.PSPC.SendCommandMessage(0xF8, out string mesg);
            MRSRCPSP.SendCommandMessage((byte)MRSMessageType.ToggleBuiltInLED, dummy);
        }

        private void GetMRSRCStatusButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D };
            MRSRCPSP.SendCommandMessage((byte)MRSMessageType.TestPacketTransfer, dummy);
        }

        private void SerialControlView_FormClosing(object sender, FormClosingEventArgs e)
        {
            Properties.Settings.Default.LastMRSCOMPort = MRSPSP.GetComPortName();
            Properties.Settings.Default.LastMRSRCComPort = MRSRCPSP.GetComPortName();
            Properties.Settings.Default.Save();
        }

        public void UpdateDisplays(byte[] buffer)
        {
            StatusDisplayLabel.Text = buffer[buffer.Length-1].ToString("X2");

            if (buffer[0] == (byte)MRSMessageType.MRSTextMessage)
            {
                char[] msg = new char[MRSPSP.PSPC.PacketPayloadSize];
                for (int i = 1; i < MRSPSP.PSPC.PacketPayloadSize; ++i)
                {
                    msg[i - 1] = (char)buffer[i];
                }
                MessageTextBox.AppendText(new string(msg));
            }
        }
    }
}

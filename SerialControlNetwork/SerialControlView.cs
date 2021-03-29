using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace SerialControlNetwork
{
    public partial class SerialControlView : Form
    {
        //PacketSerialPortController PSPC = new PacketSerialPortController();
        private DSMCUCommand LastCommandedMotorSettings = new DSMCUCommand
        {
            Speed = 0x0000,
            TurnRate = 0x0000,
            STThetaXY = 1571,   // 90° in mrad
            STThetaZX = 1571    // 90° in mrad
        };
        private DSMCUCommand MinimumCommandedMotorSettings = new DSMCUCommand
        {
            Speed = -127,
            TurnRate = -1571,   // -90°/s in mrad/s
            STThetaXY = 0x0000, // 0° in mrad
            STThetaZX = 0x0000  // 0° in mrad
        };
        private DSMCUCommand MaximumCommandedMotorSettings = new DSMCUCommand
        {
            Speed = 127,
            TurnRate = 1571,    // 90°/s in mrad/s
            STThetaXY = 3142,   // 180° in mrad
            STThetaZX = 3142    // 180° in mrad
        };

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

        private void SerialControlView_FormClosing(object sender, FormClosingEventArgs e)
        {
            Properties.Settings.Default.LastMRSCOMPort = MRSPSP.GetComPortName();
            Properties.Settings.Default.LastMRSRCComPort = MRSRCPSP.GetComPortName();
            Properties.Settings.Default.Save();
        }

        public void UpdateDisplays(byte[] buffer)
        {
            StatusDisplayLabel.Text = buffer[buffer.Length-1].ToString("X2");

            byte commandByte = buffer[0];
            byte[] packetPayload = new byte[MRSPSP.PSPC.PacketPayloadSize];
            for (int i=1; i< MRSPSP.PSPC.PacketPayloadSize; ++i)
            {
                packetPayload[i-1] = buffer[i];
            }

            if (commandByte == (byte)MRSMessageType.MRSTextMessage)
            {
                char[] msg = new char[MRSPSP.PSPC.PacketPayloadSize];
                for (int i = 1; i < MRSPSP.PSPC.PacketPayloadSize; ++i)
                {
                    msg[i - 1] = (char)buffer[i];
                }
                if (MessageTextBox.Lines.Length > 0)
                {
                    MessageTextBox.AppendText(Environment.NewLine + new string(msg));
                }
                else
                {
                    MessageTextBox.AppendText(new string(msg));
                }

            }
            else if (commandByte == (byte)MRSMessageType.DSMCUStatusPacket)
            {
                DSMCUStatus dSMCUStatus = StructByteConverter.StructByteConverter.fromBytes<DSMCUStatus>(packetPayload);
                VBatt5DisplayLabel.Text = dSMCUStatus.VSupply.ToString("0000");
            }
        }

        #region MRS control handlers
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
            System.Threading.Thread.Sleep(500);
            MRSPSP.SendCommandMessage((byte)MRSMessageType.GetTestTextMessage, dummy);
        }

        private void MRSSYSDiagnosticsButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x00 };
            MRSPSP.SendCommandMessage((byte)MRSMessageType.RunSystemDiagnostics, dummy);
        }

        private void MRSTestMotorsButton_Click(object sender, EventArgs e)
        {
            byte[] dummy = { 0x00 };
            MRSPSP.SendCommandMessage((byte)MRSMessageType.TestMotors, dummy);
        }

        #endregion

        #region MRS Remote Controller control handlers
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

        #endregion

        private void ForwardButton_Click(object sender, EventArgs e)
        {
            short speedDelta = (short)SpeedDeltaNumericUpDown.Value;

            short speed = LastCommandedMotorSettings.Speed += speedDelta;
            if (speed > MaximumCommandedMotorSettings.Speed)
            {
                speed = MaximumCommandedMotorSettings.Speed;
            }

            DSMCUCommand command = new DSMCUCommand
            {
                Speed = speed,
                TurnRate = LastCommandedMotorSettings.TurnRate,
                STThetaXY = LastCommandedMotorSettings.STThetaXY,
                STThetaZX = LastCommandedMotorSettings.STThetaZX
            };
            byte[] payloadByteArray = StructByteConverter.StructByteConverter.getByteArray(command);
            MRSPSP.SendCommandMessage(command: (byte)MRSMessageType.DSMCUSetMotors, buffer: payloadByteArray);

            LastCommandedMotorSettings = command;

            // Test conversion back to DSMCUCommand struct:
            //DSMCUCommand testCommand = StructByteConverter.StructByteConverter.fromBytes<DSMCUCommand>(payloadByteArray);
        }

        private void BackwardButton_Click(object sender, EventArgs e)
        {
            short speedDelta = (short)SpeedDeltaNumericUpDown.Value;

            short speed = LastCommandedMotorSettings.Speed -= speedDelta;
            if (speed < MinimumCommandedMotorSettings.Speed)
            {
                speed = MinimumCommandedMotorSettings.Speed;
            }

            DSMCUCommand command = new DSMCUCommand
            {
                Speed = speed,
                TurnRate = LastCommandedMotorSettings.TurnRate,
                STThetaXY = LastCommandedMotorSettings.STThetaXY,
                STThetaZX = LastCommandedMotorSettings.STThetaZX
            };
            byte[] payloadByteArray = StructByteConverter.StructByteConverter.getByteArray(command);
            MRSPSP.SendCommandMessage(command: (byte)MRSMessageType.DSMCUSetMotors, buffer: payloadByteArray);

            LastCommandedMotorSettings = command;
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            DSMCUCommand command = new DSMCUCommand
            {
                Speed = 0x0000,
                TurnRate = 0x0000,
                STThetaXY = LastCommandedMotorSettings.STThetaXY,
                STThetaZX = LastCommandedMotorSettings.STThetaZX
            };
            byte[] payloadByteArray = StructByteConverter.StructByteConverter.getByteArray(command);
            MRSPSP.SendCommandMessage(command: (byte)MRSMessageType.DSMCUSetMotors, buffer: payloadByteArray);

            LastCommandedMotorSettings = command;
        }

        private void LeftButton_Click(object sender, EventArgs e)
        {
            // Left turn is positive if x-axis is straight ahead and y-axis is directed to the left of the MRS chassis
            short turnRateDelta = (short)TurnRateDeltaNumericUpDown.Value;

            short turnRate = LastCommandedMotorSettings.TurnRate += turnRateDelta;
            if (turnRate > MaximumCommandedMotorSettings.TurnRate)
            {
                turnRate = MaximumCommandedMotorSettings.TurnRate;
            }

            DSMCUCommand command = LastCommandedMotorSettings;
            command.TurnRate = turnRate;

            byte[] payloadByteArray = StructByteConverter.StructByteConverter.getByteArray(command);
            MRSPSP.SendCommandMessage(command: (byte)MRSMessageType.DSMCUSetMotors, buffer: payloadByteArray);

            LastCommandedMotorSettings = command;
        }

        private void RightButton_Click(object sender, EventArgs e)
        {
            // Right turn is negative if x-axis is straight ahead and y-axis is directed to the left of the MRS chassis
            short turnRateDelta = (short)TurnRateDeltaNumericUpDown.Value;

            short turnRate = LastCommandedMotorSettings.TurnRate -= turnRateDelta;
            if (turnRate < MinimumCommandedMotorSettings.TurnRate)
            {
                turnRate = MinimumCommandedMotorSettings.TurnRate;
            }

            DSMCUCommand command = LastCommandedMotorSettings;
            command.TurnRate = turnRate;

            byte[] payloadByteArray = StructByteConverter.StructByteConverter.getByteArray(command);
            MRSPSP.SendCommandMessage(command: (byte)MRSMessageType.DSMCUSetMotors, buffer: payloadByteArray);

            LastCommandedMotorSettings = command;
        }
    }
}

using System.ComponentModel;
using System.Text;
using System.Windows.Forms;
using SerialControlNetwork;

namespace SerialControlNetwork
{
    public partial class PacketSerialPortPanel : UserControl
    {

        //public PacketSerialPortController PSPC { get; set; }
        public PacketSerialPortController PSPC;
        private string connectedDeviceName = "<Connected Device>";
        public string GetConnectedDeviceName()
        {
            return connectedDeviceName;
        }
        public void SetConnectedDeviceName(string value)
        {
            connectedDeviceName = value;
            ConnectedDeviceDisplayLabel.Text = connectedDeviceName;
        }

        //// Use UserControl.Parent instead?
        //private System.Windows.Forms.Control ParentControl { get; set; }

        // Delegate to update parent displays when new data is received (from another thread, such as SerialPort.OnDataReceived):
        public delegate void UpdateParentsHandler(byte[] buffer);
        public UpdateParentsHandler UpdateParents { get; set; }


        public PacketSerialPortPanel()
        {
            InitializeComponent();

            //// If PSPC is a property, then:
            //// Creating an instance of PacketSerialPortController here overwrites the one created when the user control is added to a host form
            //// We need an instance here so we can access its GetAvailableComPorts method; an alternative might be to use the static
            ////SerialPort.GetPortNames() method
            //// If PSPC is left as a field, then VS does NOT create an instance of PacketSerialPortController
            
            PSPC = new PacketSerialPortController(this, 0x20);
            PSPC.UpdateParents += new PacketSerialPortController.UpdateParentsHandler(UpdateBufferDisplays);

            PSPCMessageLabel.Text = PSPC.ToString();
            ComPortNamesComboBox.Items.AddRange(PSPC.GetAvailableComPortNames());

            // Load last COM port used from settings (if possible for a custom User Control),
            //or displlay the first listed available COM port:
            if (ComPortNamesComboBox.Items.Count > 0)
            {
                ComPortNamesComboBox.Text = ComPortNamesComboBox.Items[0].ToString();
            }

            InitializeSerialPort(ComPortNamesComboBox.Text, GetConnectedDeviceName());

            StringBuilder sb = new StringBuilder("POS :");
            for (int i=0; i < PSPC.ComBufferSize; ++i)
            {
                sb.Append($" { i.ToString("X2") }");
            }
            BytePositionLabel.Text = sb.ToString();

        }

        private void InitializeSerialPort(string comPortName, string connectedDeviceName)
        {
            ConnectedDeviceDisplayLabel.Text = connectedDeviceName;

            PSPC.RemoteSystemComPort.PortName = comPortName;
            PSPC.RemoteSystemComPort.BaudRate = int.Parse(BaudRateDisplayLabel.Text);
            PSPC.RemoteSystemComPort.DataBits = int.Parse(DataBitsDisplayLabel.Text);

            PSPC.RemoteSystemComPort.Parity = System.IO.Ports.Parity.None;

            PSPC.RemoteSystemComPort.StopBits = System.IO.Ports.StopBits.One;

        }

        private void ComPortNamesComboBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            InitializeSerialPort(ComPortNamesComboBox.Text, GetConnectedDeviceName());
        }

        private void ConnectButton_Click(object sender, System.EventArgs e)
        {
            if (PSPC.RemoteSystemComPort.IsOpen)
            {
                PSPC.CloseRemoteSystemComPort();
                ComStatusDisplayLabel.Text = $"Disconnected";
                PSPCMessageLabel.Text = $"Port closed";
                ConnectButton.Text = $"Connect";
            }
            else
            {
                PSPC.OpenRemoteSystemComPort(out string comPortStatus);
                ComStatusDisplayLabel.Text = $"Connected";
                PSPCMessageLabel.Text = comPortStatus;
                ConnectButton.Text = $"Disconnect";
            }

        }

        public void SendCommandMessage(byte command, byte[] buffer)
        {
            PSPC.SendCommandMessage(command, buffer, out string statusMessage);

            PSPCMessageLabel.Text = statusMessage;

            byte[] comBuffer = PSPC.GetComBuffer();

            // Display the contents of the encoded outgoing buffer:
            StringBuilder sb = new StringBuilder("BOUT:");
            for (int i = 0; i < PSPC.ComBufferSize; ++i)
            {
                sb.Append($" { comBuffer[i].ToString("X2") }");
            }
            OutBufferDisplayLabel.Text = sb.ToString();

            byte[] packetBuffer = PSPC.GetPacketBuffer();

            sb.Clear();
            sb.Append("POUT:");
            for (int i = 0; i < PSPC.PacketSize; ++i)
            {
                sb.Append($" { packetBuffer[i].ToString("X2") }");
            }
            OutPacketDisplayLabel.Text = sb.ToString();

        }

        public void UpdateBufferDisplays(byte[] buffer)
        {
            // Display the contents of the incomming encoded buffer:
            StringBuilder sb = new StringBuilder("BIN :");
            for (int i = 0; i < PSPC.ComBufferSize; ++i)
            {
                sb.Append($" { buffer[i].ToString("X2") }");
            }
            InBufferDisplayLabel.Text = sb.ToString();
            System.Console.WriteLine($"Packet received");

            byte[] packetBuffer = PSPC.GetPacketBuffer();

            sb.Clear();
            sb.Append("PIN :");
            for (int i = 0; i < PSPC.PacketSize; ++i)
            {
                sb.Append($" { packetBuffer[i].ToString("X2") }");
            }
            InPacketDisplayLabel.Text = sb.ToString();

            // Casscade to the Parent of this Control:
            Parent.Invoke(UpdateParents, packetBuffer);
        }

        public string GetComPortName()
        {
            return PSPC.RemoteSystemComPort.PortName;
        }

        public void SetComPortName(string comPortName)
        {
            ComPortNamesComboBox.Text = "";
            foreach (string portName in ComPortNamesComboBox.Items)
            {
                if (portName == comPortName)
                {
                    ComPortNamesComboBox.Text = comPortName;
                }
            }
        }
    }
}

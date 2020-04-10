using System.Text;
using System.Windows.Forms;
using SerialControlNetwork;

namespace PacketSerialPort
{
    public partial class PacketSerialPortPanel : UserControl
    {

        //public PacketSerialPortController PSPC { get; set; }
        public PacketSerialPortController PSPC;

        public PacketSerialPortPanel()
        {
            InitializeComponent();

            //// If PSPC is a property, then:
            //// Creating an instance of PacketSerialPortController here overwrites the one created when the user control is added to a host form
            //// We need an instance here so we can access its GetAvailableComPorts method; an alternative might be to use the static
            ////SerialPort.GetPortNames() method
            //// If PSPC is left as a field, then VS does NOT create an instance of PacketSerialPortController
            
            //ComPortNamesComboBox.Items.AddRange(System.IO.Ports.SerialPort.GetPortNames());

            PSPC = new PacketSerialPortController(0x10);
            PSPCMessageLabel.Text = PSPC.ToString();
            ComPortNamesComboBox.Items.AddRange(PSPC.GetAvailableComPortNames());

            // Load last COM port used from settings (if possible for a custom User Control),
            //or displlay the first listed available COM port:
            if (ComPortNamesComboBox.Items.Count > 0)
            {
                ComPortNamesComboBox.Text = ComPortNamesComboBox.Items[0].ToString();
            }

            InitializeSerialPort(ComPortNamesComboBox.Text);

            StringBuilder sb = new StringBuilder("POS:");
            for (int i=0; i < PSPC.ComBufferSize; ++i)
            {
                sb.Append($" { i.ToString("X2") }");
            }
            BytePositionLabel.Text = sb.ToString();

        }

        private void InitializeSerialPort(string comPortName)
        {
            PSPC.RemoteSystemComPort.PortName = comPortName;
            PSPC.RemoteSystemComPort.BaudRate = int.Parse(BaudRateDisplayLabel.Text);
            PSPC.RemoteSystemComPort.DataBits = int.Parse(DataBitsDisplayLabel.Text);

            PSPC.RemoteSystemComPort.Parity = System.IO.Ports.Parity.None;

            PSPC.RemoteSystemComPort.StopBits = System.IO.Ports.StopBits.One;

        }

        private void ComPortNamesComboBox_SelectedIndexChanged(object sender, System.EventArgs e)
        {
            InitializeSerialPort(ComPortNamesComboBox.Text);
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

        public void SendCommandMessage(byte command)
        {
            PSPC.SendCommandMessage(command, out string statusMessage);
            PSPCMessageLabel.Text = statusMessage;
        }
    }
}

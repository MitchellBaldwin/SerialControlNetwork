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
            Console.WriteLine(PSPPanel.PSPC.ComBufferSize);
            Console.WriteLine(PSPPanel.PSPC.EncodedPacketSize);
            Console.WriteLine(PSPPanel.PSPC.PacketSize);
            Console.WriteLine(PSPPanel.PSPC.PacketPayloadSize);

        }

        private void TestButton_Click(object sender, EventArgs e)
        {
            //PSPPanel.PSPC.SendCommandMessage(0xF8, out string mesg);
            PSPPanel.SendCommandMessage(0xF8);
        }
    }
}

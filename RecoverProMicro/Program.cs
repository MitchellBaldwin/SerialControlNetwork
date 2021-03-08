using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Reflection;
using System.Diagnostics;
using ArduinoUploader;


namespace RecoverProMicro
{
    class Program
    {
        static void Main(string[] args)
        {
            System.IO.Ports.SerialPort ProMicroUSBSerial = new System.IO.Ports.SerialPort("COM5", 115200, System.IO.Ports.Parity.None, 8, System.IO.Ports.StopBits.One);
            String HexFilePath = Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location);
            String HexFileNameWithFullPath = HexFilePath + "\\Rov5ArdumotoPacketSerial.hex";
            Console.WriteLine($"Load {HexFileNameWithFullPath} to {ProMicroUSBSerial.PortName}");
            Console.WriteLine("Reset Pro Micro then press any key...");
            Console.ReadKey();

            //ProMicroUSBSerial.Open();
            var uploader = new ArduinoSketchUploader(
            new ArduinoSketchUploaderOptions()
            {
                FileName = HexFileNameWithFullPath,
                PortName = ProMicroUSBSerial.PortName,
                ArduinoModel = ArduinoUploader.Hardware.ArduinoModel.Leonardo
            });

            try
            {
                uploader.UploadSketch();
                string successString = string.Format(format: "Successfully Pro Micro firmware from file: {0}", arg0: HexFileNameWithFullPath);
                Console.WriteLine(successString);
            }
            catch (Exception ex)
            {
                string errorString = "Programming FAILED: cycle power to Pro Micro device and try again\n\n" + ex.Message;
                Console.WriteLine(errorString);
            }

            Console.WriteLine("Press any key to quit...");
            Console.ReadKey();
        }
    }
}

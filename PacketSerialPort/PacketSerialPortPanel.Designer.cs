namespace SerialControlNetwork
{
    partial class PacketSerialPortPanel
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.SystemPanel = new System.Windows.Forms.Panel();
            this.InPacketDisplayLabel = new System.Windows.Forms.Label();
            this.OutPacketDisplayLabel = new System.Windows.Forms.Label();
            this.InBufferDisplayLabel = new System.Windows.Forms.Label();
            this.PSPCMessageLabel = new System.Windows.Forms.Label();
            this.ConnectButton = new System.Windows.Forms.Button();
            this.ComPortNamesComboBox = new System.Windows.Forms.ComboBox();
            this.StopBitsDisplayLabel = new System.Windows.Forms.Label();
            this.ComStatusDisplayLabel = new System.Windows.Forms.Label();
            this.BytePositionLabel = new System.Windows.Forms.Label();
            this.OutBufferDisplayLabel = new System.Windows.Forms.Label();
            this.DataBitsDisplayLabel = new System.Windows.Forms.Label();
            this.ParityDisplayLabel = new System.Windows.Forms.Label();
            this.BaudRateDisplayLabel = new System.Windows.Forms.Label();
            this.PortLabel = new System.Windows.Forms.Label();
            this.ConnectedDeviceDisplayLabel = new System.Windows.Forms.Label();
            this.SystemPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // SystemPanel
            // 
            this.SystemPanel.Controls.Add(this.ConnectedDeviceDisplayLabel);
            this.SystemPanel.Controls.Add(this.InPacketDisplayLabel);
            this.SystemPanel.Controls.Add(this.OutPacketDisplayLabel);
            this.SystemPanel.Controls.Add(this.InBufferDisplayLabel);
            this.SystemPanel.Controls.Add(this.PSPCMessageLabel);
            this.SystemPanel.Controls.Add(this.ConnectButton);
            this.SystemPanel.Controls.Add(this.ComPortNamesComboBox);
            this.SystemPanel.Controls.Add(this.StopBitsDisplayLabel);
            this.SystemPanel.Controls.Add(this.ComStatusDisplayLabel);
            this.SystemPanel.Controls.Add(this.BytePositionLabel);
            this.SystemPanel.Controls.Add(this.OutBufferDisplayLabel);
            this.SystemPanel.Controls.Add(this.DataBitsDisplayLabel);
            this.SystemPanel.Controls.Add(this.ParityDisplayLabel);
            this.SystemPanel.Controls.Add(this.BaudRateDisplayLabel);
            this.SystemPanel.Controls.Add(this.PortLabel);
            this.SystemPanel.Dock = System.Windows.Forms.DockStyle.Fill;
            this.SystemPanel.Location = new System.Drawing.Point(0, 0);
            this.SystemPanel.Name = "SystemPanel";
            this.SystemPanel.Size = new System.Drawing.Size(800, 142);
            this.SystemPanel.TabIndex = 77;
            // 
            // InPacketDisplayLabel
            // 
            this.InPacketDisplayLabel.AutoSize = true;
            this.InPacketDisplayLabel.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InPacketDisplayLabel.Location = new System.Drawing.Point(9, 92);
            this.InPacketDisplayLabel.Name = "InPacketDisplayLabel";
            this.InPacketDisplayLabel.Size = new System.Drawing.Size(48, 16);
            this.InPacketDisplayLabel.TabIndex = 116;
            this.InPacketDisplayLabel.Text = "PIN: ";
            // 
            // OutPacketDisplayLabel
            // 
            this.OutPacketDisplayLabel.AutoSize = true;
            this.OutPacketDisplayLabel.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutPacketDisplayLabel.Location = new System.Drawing.Point(9, 76);
            this.OutPacketDisplayLabel.Name = "OutPacketDisplayLabel";
            this.OutPacketDisplayLabel.Size = new System.Drawing.Size(56, 16);
            this.OutPacketDisplayLabel.TabIndex = 115;
            this.OutPacketDisplayLabel.Text = "POUT: ";
            // 
            // InBufferDisplayLabel
            // 
            this.InBufferDisplayLabel.AutoSize = true;
            this.InBufferDisplayLabel.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.InBufferDisplayLabel.Location = new System.Drawing.Point(9, 60);
            this.InBufferDisplayLabel.Name = "InBufferDisplayLabel";
            this.InBufferDisplayLabel.Size = new System.Drawing.Size(48, 16);
            this.InBufferDisplayLabel.TabIndex = 114;
            this.InBufferDisplayLabel.Text = "BIN: ";
            // 
            // PSPCMessageLabel
            // 
            this.PSPCMessageLabel.Location = new System.Drawing.Point(458, 9);
            this.PSPCMessageLabel.Name = "PSPCMessageLabel";
            this.PSPCMessageLabel.Size = new System.Drawing.Size(200, 13);
            this.PSPCMessageLabel.TabIndex = 113;
            this.PSPCMessageLabel.Text = "<PSP Controller message>";
            // 
            // ConnectButton
            // 
            this.ConnectButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ConnectButton.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(37)))), ((int)(((byte)(104)))), ((int)(((byte)(119)))));
            this.ConnectButton.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ConnectButton.ForeColor = System.Drawing.Color.White;
            this.ConnectButton.Location = new System.Drawing.Point(693, 4);
            this.ConnectButton.Name = "ConnectButton";
            this.ConnectButton.Size = new System.Drawing.Size(104, 23);
            this.ConnectButton.TabIndex = 112;
            this.ConnectButton.Text = "Connect";
            this.ConnectButton.UseVisualStyleBackColor = false;
            this.ConnectButton.Click += new System.EventHandler(this.ConnectButton_Click);
            // 
            // ComPortNamesComboBox
            // 
            this.ComPortNamesComboBox.FormattingEnabled = true;
            this.ComPortNamesComboBox.Location = new System.Drawing.Point(44, 6);
            this.ComPortNamesComboBox.Name = "ComPortNamesComboBox";
            this.ComPortNamesComboBox.Size = new System.Drawing.Size(78, 21);
            this.ComPortNamesComboBox.TabIndex = 111;
            this.ComPortNamesComboBox.SelectedIndexChanged += new System.EventHandler(this.ComPortNamesComboBox_SelectedIndexChanged);
            // 
            // StopBitsDisplayLabel
            // 
            this.StopBitsDisplayLabel.Location = new System.Drawing.Point(259, 9);
            this.StopBitsDisplayLabel.Name = "StopBitsDisplayLabel";
            this.StopBitsDisplayLabel.Size = new System.Drawing.Size(37, 13);
            this.StopBitsDisplayLabel.TabIndex = 45;
            this.StopBitsDisplayLabel.Text = "One";
            this.StopBitsDisplayLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ComStatusDisplayLabel
            // 
            this.ComStatusDisplayLabel.Location = new System.Drawing.Point(302, 9);
            this.ComStatusDisplayLabel.Name = "ComStatusDisplayLabel";
            this.ComStatusDisplayLabel.Size = new System.Drawing.Size(150, 13);
            this.ComStatusDisplayLabel.TabIndex = 44;
            this.ComStatusDisplayLabel.Text = "Not connected";
            // 
            // BytePositionLabel
            // 
            this.BytePositionLabel.AutoSize = true;
            this.BytePositionLabel.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.BytePositionLabel.Location = new System.Drawing.Point(9, 29);
            this.BytePositionLabel.Name = "BytePositionLabel";
            this.BytePositionLabel.Size = new System.Drawing.Size(432, 16);
            this.BytePositionLabel.TabIndex = 42;
            this.BytePositionLabel.Text = "POS:  00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F";
            // 
            // OutBufferDisplayLabel
            // 
            this.OutBufferDisplayLabel.AutoSize = true;
            this.OutBufferDisplayLabel.Font = new System.Drawing.Font("Courier New", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.OutBufferDisplayLabel.Location = new System.Drawing.Point(9, 44);
            this.OutBufferDisplayLabel.Name = "OutBufferDisplayLabel";
            this.OutBufferDisplayLabel.Size = new System.Drawing.Size(56, 16);
            this.OutBufferDisplayLabel.TabIndex = 40;
            this.OutBufferDisplayLabel.Text = "BOUT: ";
            // 
            // DataBitsDisplayLabel
            // 
            this.DataBitsDisplayLabel.Location = new System.Drawing.Point(182, 9);
            this.DataBitsDisplayLabel.Name = "DataBitsDisplayLabel";
            this.DataBitsDisplayLabel.Size = new System.Drawing.Size(26, 13);
            this.DataBitsDisplayLabel.TabIndex = 37;
            this.DataBitsDisplayLabel.Text = "8";
            this.DataBitsDisplayLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // ParityDisplayLabel
            // 
            this.ParityDisplayLabel.Location = new System.Drawing.Point(214, 9);
            this.ParityDisplayLabel.Name = "ParityDisplayLabel";
            this.ParityDisplayLabel.Size = new System.Drawing.Size(39, 13);
            this.ParityDisplayLabel.TabIndex = 36;
            this.ParityDisplayLabel.Text = "None";
            this.ParityDisplayLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // BaudRateDisplayLabel
            // 
            this.BaudRateDisplayLabel.Location = new System.Drawing.Point(128, 9);
            this.BaudRateDisplayLabel.Name = "BaudRateDisplayLabel";
            this.BaudRateDisplayLabel.Size = new System.Drawing.Size(48, 13);
            this.BaudRateDisplayLabel.TabIndex = 35;
            this.BaudRateDisplayLabel.Text = "115200";
            this.BaudRateDisplayLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // PortLabel
            // 
            this.PortLabel.AutoSize = true;
            this.PortLabel.Location = new System.Drawing.Point(9, 9);
            this.PortLabel.Name = "PortLabel";
            this.PortLabel.Size = new System.Drawing.Size(29, 13);
            this.PortLabel.TabIndex = 33;
            this.PortLabel.Text = "Port:";
            // 
            // ConnectedDeviceDisplayLabel
            // 
            this.ConnectedDeviceDisplayLabel.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.ConnectedDeviceDisplayLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ConnectedDeviceDisplayLabel.Location = new System.Drawing.Point(693, 32);
            this.ConnectedDeviceDisplayLabel.Name = "ConnectedDeviceDisplayLabel";
            this.ConnectedDeviceDisplayLabel.Size = new System.Drawing.Size(104, 28);
            this.ConnectedDeviceDisplayLabel.TabIndex = 117;
            this.ConnectedDeviceDisplayLabel.Text = "<Connected Device>";
            this.ConnectedDeviceDisplayLabel.TextAlign = System.Drawing.ContentAlignment.MiddleCenter;
            // 
            // PacketSerialPortPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.SystemPanel);
            this.Name = "PacketSerialPortPanel";
            this.Size = new System.Drawing.Size(800, 142);
            this.SystemPanel.ResumeLayout(false);
            this.SystemPanel.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Panel SystemPanel;
        private System.Windows.Forms.Button ConnectButton;
        private System.Windows.Forms.ComboBox ComPortNamesComboBox;
        private System.Windows.Forms.Label StopBitsDisplayLabel;
        private System.Windows.Forms.Label ComStatusDisplayLabel;
        private System.Windows.Forms.Label BytePositionLabel;
        private System.Windows.Forms.Label OutBufferDisplayLabel;
        private System.Windows.Forms.Label DataBitsDisplayLabel;
        private System.Windows.Forms.Label ParityDisplayLabel;
        private System.Windows.Forms.Label BaudRateDisplayLabel;
        private System.Windows.Forms.Label PortLabel;
        private System.Windows.Forms.Label PSPCMessageLabel;
        private System.Windows.Forms.Label InPacketDisplayLabel;
        private System.Windows.Forms.Label OutPacketDisplayLabel;
        private System.Windows.Forms.Label InBufferDisplayLabel;
        private System.Windows.Forms.Label ConnectedDeviceDisplayLabel;
    }
}

namespace SerialControlNetwork
{
    partial class SerialControlView
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.PSPPanel = new PacketSerialPort.PacketSerialPortPanel();
            this.TestButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // PSPPanel
            // 
            this.PSPPanel.Dock = System.Windows.Forms.DockStyle.Bottom;
            this.PSPPanel.Location = new System.Drawing.Point(0, 370);
            this.PSPPanel.Name = "PSPPanel";
            this.PSPPanel.Size = new System.Drawing.Size(800, 80);
            this.PSPPanel.TabIndex = 0;
            // 
            // TestButton
            // 
            this.TestButton.Location = new System.Drawing.Point(12, 12);
            this.TestButton.Name = "TestButton";
            this.TestButton.Size = new System.Drawing.Size(75, 23);
            this.TestButton.TabIndex = 1;
            this.TestButton.Text = "Test";
            this.TestButton.UseVisualStyleBackColor = true;
            this.TestButton.Click += new System.EventHandler(this.TestButton_Click);
            // 
            // SerialControlView
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.TestButton);
            this.Controls.Add(this.PSPPanel);
            this.Name = "SerialControlView";
            this.Text = "Serial Control";
            this.Load += new System.EventHandler(this.SerialControlView_Load);
            this.ResumeLayout(false);

        }

        #endregion

        private PacketSerialPort.PacketSerialPortPanel PSPPanel;
        private System.Windows.Forms.Button TestButton;
    }
}


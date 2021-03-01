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
      this.SystemsTabControl = new System.Windows.Forms.TabControl();
      this.SerialComsTabPage = new System.Windows.Forms.TabPage();
      this.MRSSYSDiagnosticsButton = new System.Windows.Forms.Button();
      this.GetMRSTestTextMessageButton = new System.Windows.Forms.Button();
      this.GetMRSRCStatusButton = new System.Windows.Forms.Button();
      this.TestMRSRCComsButton = new System.Windows.Forms.Button();
      this.GetMRSStatusButton = new System.Windows.Forms.Button();
      this.TestMRSComsButton = new System.Windows.Forms.Button();
      this.MRSRCPSP = new SerialControlNetwork.PacketSerialPortPanel();
      this.MRSPSP = new SerialControlNetwork.PacketSerialPortPanel();
      this.DiagnosticsTabPage = new System.Windows.Forms.TabPage();
      this.MRSGroupBox = new System.Windows.Forms.GroupBox();
      this.MessageTextBox = new System.Windows.Forms.TextBox();
      this.StatusDisplayLabel = new System.Windows.Forms.Label();
      this.STatusLabel = new System.Windows.Forms.Label();
      this.MRSRCGroupBox = new System.Windows.Forms.GroupBox();
      this.SystemsTabControl.SuspendLayout();
      this.SerialComsTabPage.SuspendLayout();
      this.MRSGroupBox.SuspendLayout();
      this.SuspendLayout();
      // 
      // SystemsTabControl
      // 
      this.SystemsTabControl.Controls.Add(this.SerialComsTabPage);
      this.SystemsTabControl.Controls.Add(this.DiagnosticsTabPage);
      this.SystemsTabControl.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.SystemsTabControl.Location = new System.Drawing.Point(0, 265);
      this.SystemsTabControl.Name = "SystemsTabControl";
      this.SystemsTabControl.SelectedIndex = 0;
      this.SystemsTabControl.Size = new System.Drawing.Size(1064, 336);
      this.SystemsTabControl.TabIndex = 4;
      // 
      // SerialComsTabPage
      // 
      this.SerialComsTabPage.Controls.Add(this.MRSSYSDiagnosticsButton);
      this.SerialComsTabPage.Controls.Add(this.GetMRSTestTextMessageButton);
      this.SerialComsTabPage.Controls.Add(this.GetMRSRCStatusButton);
      this.SerialComsTabPage.Controls.Add(this.TestMRSRCComsButton);
      this.SerialComsTabPage.Controls.Add(this.GetMRSStatusButton);
      this.SerialComsTabPage.Controls.Add(this.TestMRSComsButton);
      this.SerialComsTabPage.Controls.Add(this.MRSRCPSP);
      this.SerialComsTabPage.Controls.Add(this.MRSPSP);
      this.SerialComsTabPage.Location = new System.Drawing.Point(4, 22);
      this.SerialComsTabPage.Name = "SerialComsTabPage";
      this.SerialComsTabPage.Padding = new System.Windows.Forms.Padding(3);
      this.SerialComsTabPage.Size = new System.Drawing.Size(1056, 310);
      this.SerialComsTabPage.TabIndex = 0;
      this.SerialComsTabPage.Text = "Coms";
      this.SerialComsTabPage.UseVisualStyleBackColor = true;
      // 
      // MRSSYSDiagnosticsButton
      // 
      this.MRSSYSDiagnosticsButton.Location = new System.Drawing.Point(146, 35);
      this.MRSSYSDiagnosticsButton.Name = "MRSSYSDiagnosticsButton";
      this.MRSSYSDiagnosticsButton.Size = new System.Drawing.Size(132, 23);
      this.MRSSYSDiagnosticsButton.TabIndex = 10;
      this.MRSSYSDiagnosticsButton.Text = "SYS Diagnostics";
      this.MRSSYSDiagnosticsButton.UseVisualStyleBackColor = true;
      this.MRSSYSDiagnosticsButton.Click += new System.EventHandler(this.MRSSYSDiagnosticsButton_Click);
      // 
      // GetMRSTestTextMessageButton
      // 
      this.GetMRSTestTextMessageButton.Location = new System.Drawing.Point(146, 6);
      this.GetMRSTestTextMessageButton.Name = "GetMRSTestTextMessageButton";
      this.GetMRSTestTextMessageButton.Size = new System.Drawing.Size(132, 23);
      this.GetMRSTestTextMessageButton.TabIndex = 9;
      this.GetMRSTestTextMessageButton.Text = "Get Test Text";
      this.GetMRSTestTextMessageButton.UseVisualStyleBackColor = true;
      this.GetMRSTestTextMessageButton.Click += new System.EventHandler(this.GetMRSTestTextMessageButton_Click);
      // 
      // GetMRSRCStatusButton
      // 
      this.GetMRSRCStatusButton.Location = new System.Drawing.Point(572, 35);
      this.GetMRSRCStatusButton.Name = "GetMRSRCStatusButton";
      this.GetMRSRCStatusButton.Size = new System.Drawing.Size(132, 23);
      this.GetMRSRCStatusButton.TabIndex = 8;
      this.GetMRSRCStatusButton.Text = "Get MRS RC status";
      this.GetMRSRCStatusButton.UseVisualStyleBackColor = true;
      this.GetMRSRCStatusButton.Click += new System.EventHandler(this.GetMRSRCStatusButton_Click);
      // 
      // TestMRSRCComsButton
      // 
      this.TestMRSRCComsButton.Location = new System.Drawing.Point(572, 6);
      this.TestMRSRCComsButton.Name = "TestMRSRCComsButton";
      this.TestMRSRCComsButton.Size = new System.Drawing.Size(132, 23);
      this.TestMRSRCComsButton.TabIndex = 7;
      this.TestMRSRCComsButton.Text = "Test MRS RC Coms";
      this.TestMRSRCComsButton.UseVisualStyleBackColor = true;
      this.TestMRSRCComsButton.Click += new System.EventHandler(this.TestMRSRCComsButton_Click);
      // 
      // GetMRSStatusButton
      // 
      this.GetMRSStatusButton.Location = new System.Drawing.Point(8, 35);
      this.GetMRSStatusButton.Name = "GetMRSStatusButton";
      this.GetMRSStatusButton.Size = new System.Drawing.Size(132, 23);
      this.GetMRSStatusButton.TabIndex = 6;
      this.GetMRSStatusButton.Text = "Get MRS status";
      this.GetMRSStatusButton.UseVisualStyleBackColor = true;
      this.GetMRSStatusButton.Click += new System.EventHandler(this.GetMRSStatusButton_Click);
      // 
      // TestMRSComsButton
      // 
      this.TestMRSComsButton.Location = new System.Drawing.Point(8, 6);
      this.TestMRSComsButton.Name = "TestMRSComsButton";
      this.TestMRSComsButton.Size = new System.Drawing.Size(132, 23);
      this.TestMRSComsButton.TabIndex = 5;
      this.TestMRSComsButton.Text = "Test MRS Coms";
      this.TestMRSComsButton.UseVisualStyleBackColor = true;
      this.TestMRSComsButton.Click += new System.EventHandler(this.TestMRSComsButton_Click);
      // 
      // MRSRCPSP
      // 
      this.MRSRCPSP.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.MRSRCPSP.Location = new System.Drawing.Point(3, 87);
      this.MRSRCPSP.Name = "MRSRCPSP";
      this.MRSRCPSP.Size = new System.Drawing.Size(1050, 112);
      this.MRSRCPSP.TabIndex = 4;
      this.MRSRCPSP.UpdateParents = null;
      // 
      // MRSPSP
      // 
      this.MRSPSP.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.MRSPSP.Location = new System.Drawing.Point(3, 199);
      this.MRSPSP.Name = "MRSPSP";
      this.MRSPSP.Size = new System.Drawing.Size(1050, 108);
      this.MRSPSP.TabIndex = 1;
      this.MRSPSP.UpdateParents = null;
      // 
      // DiagnosticsTabPage
      // 
      this.DiagnosticsTabPage.Location = new System.Drawing.Point(4, 22);
      this.DiagnosticsTabPage.Name = "DiagnosticsTabPage";
      this.DiagnosticsTabPage.Padding = new System.Windows.Forms.Padding(3);
      this.DiagnosticsTabPage.Size = new System.Drawing.Size(1056, 310);
      this.DiagnosticsTabPage.TabIndex = 1;
      this.DiagnosticsTabPage.Text = "Diagnostics";
      this.DiagnosticsTabPage.UseVisualStyleBackColor = true;
      // 
      // MRSGroupBox
      // 
      this.MRSGroupBox.Controls.Add(this.MessageTextBox);
      this.MRSGroupBox.Controls.Add(this.StatusDisplayLabel);
      this.MRSGroupBox.Controls.Add(this.STatusLabel);
      this.MRSGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
      this.MRSGroupBox.Location = new System.Drawing.Point(0, 0);
      this.MRSGroupBox.Name = "MRSGroupBox";
      this.MRSGroupBox.Size = new System.Drawing.Size(530, 265);
      this.MRSGroupBox.TabIndex = 5;
      this.MRSGroupBox.TabStop = false;
      this.MRSGroupBox.Text = "Mobile System";
      // 
      // MessageTextBox
      // 
      this.MessageTextBox.Dock = System.Windows.Forms.DockStyle.Bottom;
      this.MessageTextBox.Location = new System.Drawing.Point(3, 201);
      this.MessageTextBox.Multiline = true;
      this.MessageTextBox.Name = "MessageTextBox";
      this.MessageTextBox.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
      this.MessageTextBox.Size = new System.Drawing.Size(524, 61);
      this.MessageTextBox.TabIndex = 2;
      // 
      // StatusDisplayLabel
      // 
      this.StatusDisplayLabel.AutoSize = true;
      this.StatusDisplayLabel.Location = new System.Drawing.Point(58, 16);
      this.StatusDisplayLabel.Name = "StatusDisplayLabel";
      this.StatusDisplayLabel.Size = new System.Drawing.Size(58, 13);
      this.StatusDisplayLabel.TabIndex = 1;
      this.StatusDisplayLabel.Text = "<not read>";
      // 
      // STatusLabel
      // 
      this.STatusLabel.AutoSize = true;
      this.STatusLabel.Location = new System.Drawing.Point(12, 16);
      this.STatusLabel.Name = "STatusLabel";
      this.STatusLabel.Size = new System.Drawing.Size(40, 13);
      this.STatusLabel.TabIndex = 0;
      this.STatusLabel.Text = "Status:";
      // 
      // MRSRCGroupBox
      // 
      this.MRSRCGroupBox.Dock = System.Windows.Forms.DockStyle.Fill;
      this.MRSRCGroupBox.Location = new System.Drawing.Point(530, 0);
      this.MRSRCGroupBox.Name = "MRSRCGroupBox";
      this.MRSRCGroupBox.Size = new System.Drawing.Size(534, 265);
      this.MRSRCGroupBox.TabIndex = 6;
      this.MRSRCGroupBox.TabStop = false;
      this.MRSRCGroupBox.Text = "Remote Controller";
      // 
      // SerialControlView
      // 
      this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
      this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
      this.ClientSize = new System.Drawing.Size(1064, 601);
      this.Controls.Add(this.MRSRCGroupBox);
      this.Controls.Add(this.MRSGroupBox);
      this.Controls.Add(this.SystemsTabControl);
      this.Name = "SerialControlView";
      this.Text = "Serial Control";
      this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.SerialControlView_FormClosing);
      this.Load += new System.EventHandler(this.SerialControlView_Load);
      this.SystemsTabControl.ResumeLayout(false);
      this.SerialComsTabPage.ResumeLayout(false);
      this.MRSGroupBox.ResumeLayout(false);
      this.MRSGroupBox.PerformLayout();
      this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.TabControl SystemsTabControl;
        private System.Windows.Forms.TabPage SerialComsTabPage;
        private System.Windows.Forms.TabPage DiagnosticsTabPage;
        private System.Windows.Forms.Button GetMRSStatusButton;
        private System.Windows.Forms.Button TestMRSComsButton;
        private PacketSerialPortPanel MRSRCPSP;
        private PacketSerialPortPanel MRSPSP;
        private System.Windows.Forms.Button GetMRSRCStatusButton;
        private System.Windows.Forms.Button TestMRSRCComsButton;
        private System.Windows.Forms.GroupBox MRSGroupBox;
        private System.Windows.Forms.GroupBox MRSRCGroupBox;
        private System.Windows.Forms.Label StatusDisplayLabel;
        private System.Windows.Forms.Label STatusLabel;
        private System.Windows.Forms.Button GetMRSTestTextMessageButton;
        private System.Windows.Forms.TextBox MessageTextBox;
        private System.Windows.Forms.Button MRSSYSDiagnosticsButton;
    }
}


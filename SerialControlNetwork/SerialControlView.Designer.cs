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
            this.GetMRSRCStatusButton = new System.Windows.Forms.Button();
            this.TestMRSRCComsButton = new System.Windows.Forms.Button();
            this.GetMRSStatusButton = new System.Windows.Forms.Button();
            this.TestMRSComsButton = new System.Windows.Forms.Button();
            this.MRSRCPSP = new SerialControlNetwork.PacketSerialPortPanel();
            this.MRSPSP = new SerialControlNetwork.PacketSerialPortPanel();
            this.DiagnosticsTabPage = new System.Windows.Forms.TabPage();
            this.MRSSYSDiagnosticsButton = new System.Windows.Forms.Button();
            this.GetMRSTestTextMessageButton = new System.Windows.Forms.Button();
            this.MRSTestMotorsButton = new System.Windows.Forms.Button();
            this.MRSGroupBox = new System.Windows.Forms.GroupBox();
            this.VBatt5DisplayLabel = new System.Windows.Forms.Label();
            this.VBatt5Label = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.TurnRateDeltaNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.SpeedDeltaUnitsLabel = new System.Windows.Forms.Label();
            this.SpeedDeltaNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.RightButton = new System.Windows.Forms.Button();
            this.LeftButton = new System.Windows.Forms.Button();
            this.StopButton = new System.Windows.Forms.Button();
            this.BackwardButton = new System.Windows.Forms.Button();
            this.ForwardButton = new System.Windows.Forms.Button();
            this.MessageTextBox = new System.Windows.Forms.TextBox();
            this.LastPacketTypeReceivedDisplayLabel = new System.Windows.Forms.Label();
            this.LastPacketTypeReceivedLabel = new System.Windows.Forms.Label();
            this.MRSRCGroupBox = new System.Windows.Forms.GroupBox();
            this.SystemsTabControl.SuspendLayout();
            this.SerialComsTabPage.SuspendLayout();
            this.DiagnosticsTabPage.SuspendLayout();
            this.MRSGroupBox.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TurnRateDeltaNumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedDeltaNumericUpDown)).BeginInit();
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
            // GetMRSRCStatusButton
            // 
            this.GetMRSRCStatusButton.Location = new System.Drawing.Point(526, 35);
            this.GetMRSRCStatusButton.Name = "GetMRSRCStatusButton";
            this.GetMRSRCStatusButton.Size = new System.Drawing.Size(132, 23);
            this.GetMRSRCStatusButton.TabIndex = 16;
            this.GetMRSRCStatusButton.Text = "Get MRS RC status";
            this.GetMRSRCStatusButton.UseVisualStyleBackColor = true;
            this.GetMRSRCStatusButton.Click += new System.EventHandler(this.GetMRSRCStatusButton_Click);
            // 
            // TestMRSRCComsButton
            // 
            this.TestMRSRCComsButton.Location = new System.Drawing.Point(526, 6);
            this.TestMRSRCComsButton.Name = "TestMRSRCComsButton";
            this.TestMRSRCComsButton.Size = new System.Drawing.Size(132, 23);
            this.TestMRSRCComsButton.TabIndex = 15;
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
            this.DiagnosticsTabPage.Controls.Add(this.MRSSYSDiagnosticsButton);
            this.DiagnosticsTabPage.Controls.Add(this.GetMRSTestTextMessageButton);
            this.DiagnosticsTabPage.Controls.Add(this.MRSTestMotorsButton);
            this.DiagnosticsTabPage.Location = new System.Drawing.Point(4, 22);
            this.DiagnosticsTabPage.Name = "DiagnosticsTabPage";
            this.DiagnosticsTabPage.Padding = new System.Windows.Forms.Padding(3);
            this.DiagnosticsTabPage.Size = new System.Drawing.Size(1056, 310);
            this.DiagnosticsTabPage.TabIndex = 1;
            this.DiagnosticsTabPage.Text = "Diagnostics";
            this.DiagnosticsTabPage.UseVisualStyleBackColor = true;
            // 
            // MRSSYSDiagnosticsButton
            // 
            this.MRSSYSDiagnosticsButton.Location = new System.Drawing.Point(8, 35);
            this.MRSSYSDiagnosticsButton.Name = "MRSSYSDiagnosticsButton";
            this.MRSSYSDiagnosticsButton.Size = new System.Drawing.Size(132, 23);
            this.MRSSYSDiagnosticsButton.TabIndex = 16;
            this.MRSSYSDiagnosticsButton.Text = "SYS Diagnostics";
            this.MRSSYSDiagnosticsButton.UseVisualStyleBackColor = true;
            this.MRSSYSDiagnosticsButton.Click += new System.EventHandler(this.MRSSYSDiagnosticsButton_Click);
            // 
            // GetMRSTestTextMessageButton
            // 
            this.GetMRSTestTextMessageButton.Location = new System.Drawing.Point(8, 6);
            this.GetMRSTestTextMessageButton.Name = "GetMRSTestTextMessageButton";
            this.GetMRSTestTextMessageButton.Size = new System.Drawing.Size(132, 23);
            this.GetMRSTestTextMessageButton.TabIndex = 15;
            this.GetMRSTestTextMessageButton.Text = "Get Test Text";
            this.GetMRSTestTextMessageButton.UseVisualStyleBackColor = true;
            this.GetMRSTestTextMessageButton.Click += new System.EventHandler(this.GetMRSTestTextMessageButton_Click);
            // 
            // MRSTestMotorsButton
            // 
            this.MRSTestMotorsButton.Location = new System.Drawing.Point(8, 64);
            this.MRSTestMotorsButton.Name = "MRSTestMotorsButton";
            this.MRSTestMotorsButton.Size = new System.Drawing.Size(132, 23);
            this.MRSTestMotorsButton.TabIndex = 12;
            this.MRSTestMotorsButton.Text = "Test Motors";
            this.MRSTestMotorsButton.UseVisualStyleBackColor = true;
            this.MRSTestMotorsButton.Click += new System.EventHandler(this.MRSTestMotorsButton_Click);
            // 
            // MRSGroupBox
            // 
            this.MRSGroupBox.Controls.Add(this.VBatt5DisplayLabel);
            this.MRSGroupBox.Controls.Add(this.VBatt5Label);
            this.MRSGroupBox.Controls.Add(this.label1);
            this.MRSGroupBox.Controls.Add(this.TurnRateDeltaNumericUpDown);
            this.MRSGroupBox.Controls.Add(this.SpeedDeltaUnitsLabel);
            this.MRSGroupBox.Controls.Add(this.SpeedDeltaNumericUpDown);
            this.MRSGroupBox.Controls.Add(this.RightButton);
            this.MRSGroupBox.Controls.Add(this.LeftButton);
            this.MRSGroupBox.Controls.Add(this.StopButton);
            this.MRSGroupBox.Controls.Add(this.BackwardButton);
            this.MRSGroupBox.Controls.Add(this.ForwardButton);
            this.MRSGroupBox.Controls.Add(this.MessageTextBox);
            this.MRSGroupBox.Controls.Add(this.LastPacketTypeReceivedDisplayLabel);
            this.MRSGroupBox.Controls.Add(this.LastPacketTypeReceivedLabel);
            this.MRSGroupBox.Dock = System.Windows.Forms.DockStyle.Left;
            this.MRSGroupBox.Location = new System.Drawing.Point(0, 0);
            this.MRSGroupBox.Name = "MRSGroupBox";
            this.MRSGroupBox.Size = new System.Drawing.Size(530, 265);
            this.MRSGroupBox.TabIndex = 5;
            this.MRSGroupBox.TabStop = false;
            this.MRSGroupBox.Text = "Mobile System";
            // 
            // VBatt5DisplayLabel
            // 
            this.VBatt5DisplayLabel.AutoSize = true;
            this.VBatt5DisplayLabel.Location = new System.Drawing.Point(431, 138);
            this.VBatt5DisplayLabel.Name = "VBatt5DisplayLabel";
            this.VBatt5DisplayLabel.Size = new System.Drawing.Size(58, 13);
            this.VBatt5DisplayLabel.TabIndex = 13;
            this.VBatt5DisplayLabel.Text = "<not read>";
            // 
            // VBatt5Label
            // 
            this.VBatt5Label.AutoSize = true;
            this.VBatt5Label.Location = new System.Drawing.Point(385, 138);
            this.VBatt5Label.Name = "VBatt5Label";
            this.VBatt5Label.Size = new System.Drawing.Size(42, 13);
            this.VBatt5Label.TabIndex = 12;
            this.VBatt5Label.Text = "VBatt5:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(446, 117);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(40, 13);
            this.label1.TabIndex = 11;
            this.label1.Text = "mrad/s";
            // 
            // TurnRateDeltaNumericUpDown
            // 
            this.TurnRateDeltaNumericUpDown.Increment = new decimal(new int[] {
            175,
            0,
            0,
            0});
            this.TurnRateDeltaNumericUpDown.Location = new System.Drawing.Point(388, 115);
            this.TurnRateDeltaNumericUpDown.Maximum = new decimal(new int[] {
            1571,
            0,
            0,
            0});
            this.TurnRateDeltaNumericUpDown.Minimum = new decimal(new int[] {
            1571,
            0,
            0,
            -2147483648});
            this.TurnRateDeltaNumericUpDown.Name = "TurnRateDeltaNumericUpDown";
            this.TurnRateDeltaNumericUpDown.Size = new System.Drawing.Size(55, 20);
            this.TurnRateDeltaNumericUpDown.TabIndex = 10;
            this.TurnRateDeltaNumericUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            // 
            // SpeedDeltaUnitsLabel
            // 
            this.SpeedDeltaUnitsLabel.AutoSize = true;
            this.SpeedDeltaUnitsLabel.Location = new System.Drawing.Point(446, 91);
            this.SpeedDeltaUnitsLabel.Name = "SpeedDeltaUnitsLabel";
            this.SpeedDeltaUnitsLabel.Size = new System.Drawing.Size(33, 13);
            this.SpeedDeltaUnitsLabel.TabIndex = 9;
            this.SpeedDeltaUnitsLabel.Text = "mm/s";
            // 
            // SpeedDeltaNumericUpDown
            // 
            this.SpeedDeltaNumericUpDown.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.SpeedDeltaNumericUpDown.Location = new System.Drawing.Point(388, 89);
            this.SpeedDeltaNumericUpDown.Maximum = new decimal(new int[] {
            127,
            0,
            0,
            0});
            this.SpeedDeltaNumericUpDown.Minimum = new decimal(new int[] {
            127,
            0,
            0,
            -2147483648});
            this.SpeedDeltaNumericUpDown.Name = "SpeedDeltaNumericUpDown";
            this.SpeedDeltaNumericUpDown.Size = new System.Drawing.Size(55, 20);
            this.SpeedDeltaNumericUpDown.TabIndex = 8;
            this.SpeedDeltaNumericUpDown.TextAlign = System.Windows.Forms.HorizontalAlignment.Right;
            this.SpeedDeltaNumericUpDown.Value = new decimal(new int[] {
            100,
            0,
            0,
            0});
            // 
            // RightButton
            // 
            this.RightButton.BackgroundImage = global::SerialControlNetwork.Properties.Resources.RightArrowWHTonBLK;
            this.RightButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.RightButton.Location = new System.Drawing.Point(350, 83);
            this.RightButton.Name = "RightButton";
            this.RightButton.Size = new System.Drawing.Size(30, 30);
            this.RightButton.TabIndex = 7;
            this.RightButton.UseVisualStyleBackColor = true;
            this.RightButton.Click += new System.EventHandler(this.RightButton_Click);
            // 
            // LeftButton
            // 
            this.LeftButton.BackgroundImage = global::SerialControlNetwork.Properties.Resources.LeftArrowWHTonBLK;
            this.LeftButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.LeftButton.Location = new System.Drawing.Point(278, 83);
            this.LeftButton.Name = "LeftButton";
            this.LeftButton.Size = new System.Drawing.Size(30, 30);
            this.LeftButton.TabIndex = 6;
            this.LeftButton.UseVisualStyleBackColor = true;
            this.LeftButton.Click += new System.EventHandler(this.LeftButton_Click);
            // 
            // StopButton
            // 
            this.StopButton.BackgroundImage = global::SerialControlNetwork.Properties.Resources.StopArrowWHTonBLK;
            this.StopButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.StopButton.Location = new System.Drawing.Point(314, 83);
            this.StopButton.Name = "StopButton";
            this.StopButton.Size = new System.Drawing.Size(30, 30);
            this.StopButton.TabIndex = 5;
            this.StopButton.UseVisualStyleBackColor = true;
            this.StopButton.Click += new System.EventHandler(this.StopButton_Click);
            // 
            // BackwardButton
            // 
            this.BackwardButton.BackgroundImage = global::SerialControlNetwork.Properties.Resources.DownArrowWHTonBLK;
            this.BackwardButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.BackwardButton.Location = new System.Drawing.Point(314, 119);
            this.BackwardButton.Name = "BackwardButton";
            this.BackwardButton.Size = new System.Drawing.Size(30, 30);
            this.BackwardButton.TabIndex = 4;
            this.BackwardButton.UseVisualStyleBackColor = true;
            this.BackwardButton.Click += new System.EventHandler(this.BackwardButton_Click);
            // 
            // ForwardButton
            // 
            this.ForwardButton.BackgroundImage = global::SerialControlNetwork.Properties.Resources.UpArrowWHTonBLK;
            this.ForwardButton.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.ForwardButton.Location = new System.Drawing.Point(314, 47);
            this.ForwardButton.Name = "ForwardButton";
            this.ForwardButton.Size = new System.Drawing.Size(30, 30);
            this.ForwardButton.TabIndex = 3;
            this.ForwardButton.UseVisualStyleBackColor = true;
            this.ForwardButton.Click += new System.EventHandler(this.ForwardButton_Click);
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
            // LastPacketTypeReceivedDisplayLabel
            // 
            this.LastPacketTypeReceivedDisplayLabel.AutoSize = true;
            this.LastPacketTypeReceivedDisplayLabel.Location = new System.Drawing.Point(154, 16);
            this.LastPacketTypeReceivedDisplayLabel.Name = "LastPacketTypeReceivedDisplayLabel";
            this.LastPacketTypeReceivedDisplayLabel.Size = new System.Drawing.Size(58, 13);
            this.LastPacketTypeReceivedDisplayLabel.TabIndex = 1;
            this.LastPacketTypeReceivedDisplayLabel.Text = "<not read>";
            // 
            // LastPacketTypeReceivedLabel
            // 
            this.LastPacketTypeReceivedLabel.AutoSize = true;
            this.LastPacketTypeReceivedLabel.Location = new System.Drawing.Point(12, 16);
            this.LastPacketTypeReceivedLabel.Name = "LastPacketTypeReceivedLabel";
            this.LastPacketTypeReceivedLabel.Size = new System.Drawing.Size(133, 13);
            this.LastPacketTypeReceivedLabel.TabIndex = 0;
            this.LastPacketTypeReceivedLabel.Text = "Last packet type received:";
            this.LastPacketTypeReceivedLabel.TextAlign = System.Drawing.ContentAlignment.TopRight;
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
            this.DiagnosticsTabPage.ResumeLayout(false);
            this.MRSGroupBox.ResumeLayout(false);
            this.MRSGroupBox.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.TurnRateDeltaNumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.SpeedDeltaNumericUpDown)).EndInit();
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
        private System.Windows.Forms.GroupBox MRSGroupBox;
        private System.Windows.Forms.GroupBox MRSRCGroupBox;
        private System.Windows.Forms.Label LastPacketTypeReceivedDisplayLabel;
        private System.Windows.Forms.Label LastPacketTypeReceivedLabel;
        private System.Windows.Forms.TextBox MessageTextBox;
        private System.Windows.Forms.Button MRSTestMotorsButton;
        private System.Windows.Forms.Button MRSSYSDiagnosticsButton;
        private System.Windows.Forms.Button GetMRSTestTextMessageButton;
        private System.Windows.Forms.Button GetMRSRCStatusButton;
        private System.Windows.Forms.Button TestMRSRCComsButton;
        private System.Windows.Forms.Button ForwardButton;
        private System.Windows.Forms.Button BackwardButton;
        private System.Windows.Forms.Button StopButton;
        private System.Windows.Forms.Button RightButton;
        private System.Windows.Forms.Button LeftButton;
        private System.Windows.Forms.Label SpeedDeltaUnitsLabel;
        private System.Windows.Forms.NumericUpDown SpeedDeltaNumericUpDown;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.NumericUpDown TurnRateDeltaNumericUpDown;
        private System.Windows.Forms.Label VBatt5DisplayLabel;
        private System.Windows.Forms.Label VBatt5Label;
    }
}


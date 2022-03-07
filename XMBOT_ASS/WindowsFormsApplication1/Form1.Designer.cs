namespace WindowsFormsApplication1
{
    partial class xm_ass
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(xm_ass));
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.ReadWristxtBox = new System.Windows.Forms.Button();
            this.SetWristxtBox = new System.Windows.Forms.Button();
            this.SetWristText = new System.Windows.Forms.TextBox();
            this.SetArmtxtBox = new System.Windows.Forms.TextBox();
            this.ReadArmbtn = new System.Windows.Forms.Button();
            this.SetArmbtn = new System.Windows.Forms.Button();
            this.ReadPlatbtn = new System.Windows.Forms.Button();
            this.SetPlatbtn = new System.Windows.Forms.Button();
            this.SetPlatxtBox = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.SetSpeedtxtBox = new System.Windows.Forms.TextBox();
            this.ClearGlobalCoordinatebtn = new System.Windows.Forms.Button();
            this.ReadGlobalCoordinatebtn = new System.Windows.Forms.Button();
            this.ReadSpeedbtn = new System.Windows.Forms.Button();
            this.SetSpeedbtn = new System.Windows.Forms.Button();
            this.rcvtxtBox = new System.Windows.Forms.TextBox();
            this.srlboBox = new System.Windows.Forms.ComboBox();
            this.bdrtboBox = new System.Windows.Forms.ComboBox();
            this.srllabel = new System.Windows.Forms.Label();
            this.bdrtlabel = new System.Windows.Forms.Label();
            this.srlbtn = new System.Windows.Forms.Button();
            this.clrbtn = new System.Windows.Forms.Button();
            this.serialPort1 = new System.IO.Ports.SerialPort(this.components);
            this.ShakeHandsbtn = new System.Windows.Forms.Button();
            this.SendBuftxtBox = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.Claw_btn3 = new System.Windows.Forms.Button();
            this.Claw_btn2 = new System.Windows.Forms.Button();
            this.Claw_btn1 = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.BackColor = System.Drawing.Color.Transparent;
            this.groupBox1.Controls.Add(this.ReadWristxtBox);
            this.groupBox1.Controls.Add(this.SetWristxtBox);
            this.groupBox1.Controls.Add(this.SetWristText);
            this.groupBox1.Controls.Add(this.SetArmtxtBox);
            this.groupBox1.Controls.Add(this.ReadArmbtn);
            this.groupBox1.Controls.Add(this.SetArmbtn);
            this.groupBox1.Controls.Add(this.ReadPlatbtn);
            this.groupBox1.Controls.Add(this.SetPlatbtn);
            this.groupBox1.Controls.Add(this.SetPlatxtBox);
            this.groupBox1.ForeColor = System.Drawing.SystemColors.ControlText;
            this.groupBox1.Location = new System.Drawing.Point(448, 85);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(5);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(5);
            this.groupBox1.Size = new System.Drawing.Size(493, 327);
            this.groupBox1.TabIndex = 0;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "机械臂";
            // 
            // ReadWristxtBox
            // 
            this.ReadWristxtBox.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ReadWristxtBox.Location = new System.Drawing.Point(397, 21);
            this.ReadWristxtBox.Name = "ReadWristxtBox";
            this.ReadWristxtBox.Size = new System.Drawing.Size(89, 85);
            this.ReadWristxtBox.TabIndex = 12;
            this.ReadWristxtBox.Text = "读取腕部 (弧度)";
            this.ReadWristxtBox.UseVisualStyleBackColor = true;
            this.ReadWristxtBox.Click += new System.EventHandler(this.ReadWristxtBox_Click);
            // 
            // SetWristxtBox
            // 
            this.SetWristxtBox.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.SetWristxtBox.Location = new System.Drawing.Point(284, 21);
            this.SetWristxtBox.Name = "SetWristxtBox";
            this.SetWristxtBox.Size = new System.Drawing.Size(89, 85);
            this.SetWristxtBox.TabIndex = 11;
            this.SetWristxtBox.Text = "设置腕部 (弧度)";
            this.SetWristxtBox.UseVisualStyleBackColor = true;
            this.SetWristxtBox.Click += new System.EventHandler(this.SetWristxtBox_Click);
            // 
            // SetWristText
            // 
            this.SetWristText.Location = new System.Drawing.Point(42, 50);
            this.SetWristText.Name = "SetWristText";
            this.SetWristText.Size = new System.Drawing.Size(206, 29);
            this.SetWristText.TabIndex = 10;
            // 
            // SetArmtxtBox
            // 
            this.SetArmtxtBox.Location = new System.Drawing.Point(42, 154);
            this.SetArmtxtBox.Name = "SetArmtxtBox";
            this.SetArmtxtBox.Size = new System.Drawing.Size(206, 29);
            this.SetArmtxtBox.TabIndex = 9;
            // 
            // ReadArmbtn
            // 
            this.ReadArmbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ReadArmbtn.Location = new System.Drawing.Point(396, 125);
            this.ReadArmbtn.Name = "ReadArmbtn";
            this.ReadArmbtn.Size = new System.Drawing.Size(89, 85);
            this.ReadArmbtn.TabIndex = 8;
            this.ReadArmbtn.Text = "读取机械臂(弧度)";
            this.ReadArmbtn.UseVisualStyleBackColor = true;
            this.ReadArmbtn.Click += new System.EventHandler(this.ReadArmbtn_Click);
            // 
            // SetArmbtn
            // 
            this.SetArmbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.SetArmbtn.Location = new System.Drawing.Point(284, 125);
            this.SetArmbtn.Name = "SetArmbtn";
            this.SetArmbtn.Size = new System.Drawing.Size(89, 85);
            this.SetArmbtn.TabIndex = 7;
            this.SetArmbtn.Text = "设置机械臂(弧度)";
            this.SetArmbtn.UseVisualStyleBackColor = true;
            this.SetArmbtn.Click += new System.EventHandler(this.SetArmbtn_Click);
            // 
            // ReadPlatbtn
            // 
            this.ReadPlatbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ReadPlatbtn.Location = new System.Drawing.Point(397, 229);
            this.ReadPlatbtn.Name = "ReadPlatbtn";
            this.ReadPlatbtn.Size = new System.Drawing.Size(89, 85);
            this.ReadPlatbtn.TabIndex = 6;
            this.ReadPlatbtn.Text = "读取升降 (米制)";
            this.ReadPlatbtn.UseVisualStyleBackColor = true;
            this.ReadPlatbtn.Click += new System.EventHandler(this.ReadPlatbtn_Click);
            // 
            // SetPlatbtn
            // 
            this.SetPlatbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.SetPlatbtn.Location = new System.Drawing.Point(284, 229);
            this.SetPlatbtn.Name = "SetPlatbtn";
            this.SetPlatbtn.Size = new System.Drawing.Size(89, 85);
            this.SetPlatbtn.TabIndex = 5;
            this.SetPlatbtn.Text = "设置升降 (米制)";
            this.SetPlatbtn.UseVisualStyleBackColor = true;
            this.SetPlatbtn.Click += new System.EventHandler(this.SetPlatbtn_Click);
            // 
            // SetPlatxtBox
            // 
            this.SetPlatxtBox.Location = new System.Drawing.Point(42, 258);
            this.SetPlatxtBox.Name = "SetPlatxtBox";
            this.SetPlatxtBox.Size = new System.Drawing.Size(206, 29);
            this.SetPlatxtBox.TabIndex = 0;
            // 
            // groupBox2
            // 
            this.groupBox2.BackColor = System.Drawing.Color.Transparent;
            this.groupBox2.Controls.Add(this.SetSpeedtxtBox);
            this.groupBox2.Controls.Add(this.ClearGlobalCoordinatebtn);
            this.groupBox2.Controls.Add(this.ReadGlobalCoordinatebtn);
            this.groupBox2.Controls.Add(this.ReadSpeedbtn);
            this.groupBox2.Controls.Add(this.SetSpeedbtn);
            this.groupBox2.Location = new System.Drawing.Point(450, 425);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(493, 201);
            this.groupBox2.TabIndex = 0;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "底盘";
            // 
            // SetSpeedtxtBox
            // 
            this.SetSpeedtxtBox.Location = new System.Drawing.Point(40, 36);
            this.SetSpeedtxtBox.Name = "SetSpeedtxtBox";
            this.SetSpeedtxtBox.Size = new System.Drawing.Size(206, 29);
            this.SetSpeedtxtBox.TabIndex = 4;
            // 
            // ClearGlobalCoordinatebtn
            // 
            this.ClearGlobalCoordinatebtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ClearGlobalCoordinatebtn.Location = new System.Drawing.Point(402, 102);
            this.ClearGlobalCoordinatebtn.Name = "ClearGlobalCoordinatebtn";
            this.ClearGlobalCoordinatebtn.Size = new System.Drawing.Size(84, 84);
            this.ClearGlobalCoordinatebtn.TabIndex = 3;
            this.ClearGlobalCoordinatebtn.Text = "重置里程";
            this.ClearGlobalCoordinatebtn.UseVisualStyleBackColor = true;
            this.ClearGlobalCoordinatebtn.Click += new System.EventHandler(this.ClearGlobalCoordinatebtn_Click);
            // 
            // ReadGlobalCoordinatebtn
            // 
            this.ReadGlobalCoordinatebtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ReadGlobalCoordinatebtn.Location = new System.Drawing.Point(282, 102);
            this.ReadGlobalCoordinatebtn.Name = "ReadGlobalCoordinatebtn";
            this.ReadGlobalCoordinatebtn.Size = new System.Drawing.Size(89, 84);
            this.ReadGlobalCoordinatebtn.TabIndex = 2;
            this.ReadGlobalCoordinatebtn.Text = "读取里程";
            this.ReadGlobalCoordinatebtn.UseVisualStyleBackColor = true;
            this.ReadGlobalCoordinatebtn.Click += new System.EventHandler(this.ReadGlobalCoordinatebtn_Click);
            // 
            // ReadSpeedbtn
            // 
            this.ReadSpeedbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ReadSpeedbtn.Location = new System.Drawing.Point(402, 11);
            this.ReadSpeedbtn.Name = "ReadSpeedbtn";
            this.ReadSpeedbtn.Size = new System.Drawing.Size(84, 85);
            this.ReadSpeedbtn.TabIndex = 1;
            this.ReadSpeedbtn.Text = "读取速度 (米制)";
            this.ReadSpeedbtn.UseVisualStyleBackColor = true;
            this.ReadSpeedbtn.Click += new System.EventHandler(this.ReadSpeedbtn_Click);
            // 
            // SetSpeedbtn
            // 
            this.SetSpeedbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.SetSpeedbtn.Location = new System.Drawing.Point(282, 11);
            this.SetSpeedbtn.Name = "SetSpeedbtn";
            this.SetSpeedbtn.Size = new System.Drawing.Size(89, 85);
            this.SetSpeedbtn.TabIndex = 0;
            this.SetSpeedbtn.Text = "设置速度 (米制)";
            this.SetSpeedbtn.UseVisualStyleBackColor = true;
            this.SetSpeedbtn.Click += new System.EventHandler(this.SetSpeedbtn_Click);
            // 
            // rcvtxtBox
            // 
            this.rcvtxtBox.BackColor = System.Drawing.SystemColors.Window;
            this.rcvtxtBox.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.rcvtxtBox.Location = new System.Drawing.Point(12, 48);
            this.rcvtxtBox.Multiline = true;
            this.rcvtxtBox.Name = "rcvtxtBox";
            this.rcvtxtBox.Size = new System.Drawing.Size(430, 373);
            this.rcvtxtBox.TabIndex = 1;
            // 
            // srlboBox
            // 
            this.srlboBox.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.srlboBox.FormattingEnabled = true;
            this.srlboBox.Location = new System.Drawing.Point(91, 497);
            this.srlboBox.Name = "srlboBox";
            this.srlboBox.Size = new System.Drawing.Size(90, 25);
            this.srlboBox.TabIndex = 2;
            // 
            // bdrtboBox
            // 
            this.bdrtboBox.Font = new System.Drawing.Font("微软雅黑", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.bdrtboBox.FormattingEnabled = true;
            this.bdrtboBox.Location = new System.Drawing.Point(91, 566);
            this.bdrtboBox.Name = "bdrtboBox";
            this.bdrtboBox.Size = new System.Drawing.Size(90, 25);
            this.bdrtboBox.TabIndex = 3;
            // 
            // srllabel
            // 
            this.srllabel.AutoSize = true;
            this.srllabel.BackColor = System.Drawing.Color.Transparent;
            this.srllabel.Location = new System.Drawing.Point(12, 500);
            this.srllabel.Name = "srllabel";
            this.srllabel.Size = new System.Drawing.Size(58, 21);
            this.srllabel.TabIndex = 4;
            this.srllabel.Text = "串口号";
            // 
            // bdrtlabel
            // 
            this.bdrtlabel.AutoSize = true;
            this.bdrtlabel.BackColor = System.Drawing.Color.Transparent;
            this.bdrtlabel.Location = new System.Drawing.Point(12, 565);
            this.bdrtlabel.Name = "bdrtlabel";
            this.bdrtlabel.Size = new System.Drawing.Size(74, 21);
            this.bdrtlabel.TabIndex = 5;
            this.bdrtlabel.Text = "通讯模式";
            // 
            // srlbtn
            // 
            this.srlbtn.BackColor = System.Drawing.Color.Transparent;
            this.srlbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.srlbtn.Location = new System.Drawing.Point(198, 497);
            this.srlbtn.Name = "srlbtn";
            this.srlbtn.Size = new System.Drawing.Size(94, 44);
            this.srlbtn.TabIndex = 6;
            this.srlbtn.Text = "打开串口";
            this.srlbtn.UseVisualStyleBackColor = false;
            this.srlbtn.Click += new System.EventHandler(this.srlbtn_Click);
            // 
            // clrbtn
            // 
            this.clrbtn.BackColor = System.Drawing.Color.Transparent;
            this.clrbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.clrbtn.Location = new System.Drawing.Point(198, 554);
            this.clrbtn.Name = "clrbtn";
            this.clrbtn.Size = new System.Drawing.Size(94, 43);
            this.clrbtn.TabIndex = 7;
            this.clrbtn.Text = "清除数据";
            this.clrbtn.UseVisualStyleBackColor = false;
            this.clrbtn.Click += new System.EventHandler(this.clrbtn_Click);
            // 
            // serialPort1
            // 
            this.serialPort1.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort1_DataReceived);
            // 
            // ShakeHandsbtn
            // 
            this.ShakeHandsbtn.BackColor = System.Drawing.Color.Transparent;
            this.ShakeHandsbtn.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.ShakeHandsbtn.Font = new System.Drawing.Font("微软雅黑", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.ShakeHandsbtn.Location = new System.Drawing.Point(309, 497);
            this.ShakeHandsbtn.Name = "ShakeHandsbtn";
            this.ShakeHandsbtn.Size = new System.Drawing.Size(95, 100);
            this.ShakeHandsbtn.TabIndex = 8;
            this.ShakeHandsbtn.Text = "握手";
            this.ShakeHandsbtn.UseVisualStyleBackColor = false;
            this.ShakeHandsbtn.Click += new System.EventHandler(this.ShakeHandsbtn_Click);
            // 
            // SendBuftxtBox
            // 
            this.SendBuftxtBox.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.SendBuftxtBox.Location = new System.Drawing.Point(12, 449);
            this.SendBuftxtBox.Name = "SendBuftxtBox";
            this.SendBuftxtBox.ReadOnly = true;
            this.SendBuftxtBox.Size = new System.Drawing.Size(430, 21);
            this.SendBuftxtBox.TabIndex = 9;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.BackColor = System.Drawing.Color.Transparent;
            this.label1.Location = new System.Drawing.Point(12, 425);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(90, 21);
            this.label1.TabIndex = 10;
            this.label1.Text = "数据发送栏";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.BackColor = System.Drawing.Color.Transparent;
            this.label2.Location = new System.Drawing.Point(12, 24);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(90, 21);
            this.label2.TabIndex = 11;
            this.label2.Text = "数据接收栏";
            // 
            // groupBox3
            // 
            this.groupBox3.BackColor = System.Drawing.Color.Transparent;
            this.groupBox3.Controls.Add(this.Claw_btn3);
            this.groupBox3.Controls.Add(this.Claw_btn2);
            this.groupBox3.Controls.Add(this.Claw_btn1);
            this.groupBox3.Location = new System.Drawing.Point(448, 48);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(485, 41);
            this.groupBox3.TabIndex = 12;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "爪子";
            // 
            // Claw_btn3
            // 
            this.Claw_btn3.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Claw_btn3.Location = new System.Drawing.Point(284, 6);
            this.Claw_btn3.Name = "Claw_btn3";
            this.Claw_btn3.Size = new System.Drawing.Size(75, 35);
            this.Claw_btn3.TabIndex = 2;
            this.Claw_btn3.Text = "姿态3";
            this.Claw_btn3.UseVisualStyleBackColor = true;
            this.Claw_btn3.Click += new System.EventHandler(this.Claw_btn3_Click);
            // 
            // Claw_btn2
            // 
            this.Claw_btn2.BackColor = System.Drawing.Color.Transparent;
            this.Claw_btn2.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Claw_btn2.Location = new System.Drawing.Point(187, 6);
            this.Claw_btn2.Name = "Claw_btn2";
            this.Claw_btn2.Size = new System.Drawing.Size(75, 35);
            this.Claw_btn2.TabIndex = 1;
            this.Claw_btn2.Text = "姿态2";
            this.Claw_btn2.UseVisualStyleBackColor = false;
            this.Claw_btn2.Click += new System.EventHandler(this.Claw_btn2_Click);
            // 
            // Claw_btn1
            // 
            this.Claw_btn1.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.Claw_btn1.Location = new System.Drawing.Point(95, 6);
            this.Claw_btn1.Name = "Claw_btn1";
            this.Claw_btn1.Size = new System.Drawing.Size(75, 35);
            this.Claw_btn1.TabIndex = 0;
            this.Claw_btn1.Text = "姿态1";
            this.Claw_btn1.UseVisualStyleBackColor = true;
            this.Claw_btn1.Click += new System.EventHandler(this.Claw_btn1_Click);
            // 
            // xm_ass
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(10F, 21F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackgroundImage = ((System.Drawing.Image)(resources.GetObject("$this.BackgroundImage")));
            this.ClientSize = new System.Drawing.Size(955, 638);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.SendBuftxtBox);
            this.Controls.Add(this.ShakeHandsbtn);
            this.Controls.Add(this.clrbtn);
            this.Controls.Add(this.srlbtn);
            this.Controls.Add(this.bdrtlabel);
            this.Controls.Add(this.srllabel);
            this.Controls.Add(this.bdrtboBox);
            this.Controls.Add(this.srlboBox);
            this.Controls.Add(this.rcvtxtBox);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Font = new System.Drawing.Font("微软雅黑", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(5);
            this.MaximizeBox = false;
            this.Name = "xm_ass";
            this.Opacity = 0.98D;
            this.Text = "xm_ass";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox3.ResumeLayout(false);
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox rcvtxtBox;
        private System.Windows.Forms.ComboBox srlboBox;
        private System.Windows.Forms.ComboBox bdrtboBox;
        private System.Windows.Forms.Label srllabel;
        private System.Windows.Forms.Label bdrtlabel;
        private System.Windows.Forms.Button srlbtn;
        private System.Windows.Forms.Button clrbtn;
        private System.IO.Ports.SerialPort serialPort1;
        private System.Windows.Forms.Button ShakeHandsbtn;
        private System.Windows.Forms.TextBox SetSpeedtxtBox;
        private System.Windows.Forms.Button ClearGlobalCoordinatebtn;
        private System.Windows.Forms.Button ReadGlobalCoordinatebtn;
        private System.Windows.Forms.Button ReadSpeedbtn;
        private System.Windows.Forms.Button SetSpeedbtn;
        private System.Windows.Forms.TextBox SetArmtxtBox;
        private System.Windows.Forms.Button ReadArmbtn;
        private System.Windows.Forms.Button SetArmbtn;
        private System.Windows.Forms.Button ReadPlatbtn;
        private System.Windows.Forms.Button SetPlatbtn;
        private System.Windows.Forms.TextBox SetPlatxtBox;
        private System.Windows.Forms.Button ReadWristxtBox;
        private System.Windows.Forms.Button SetWristxtBox;
        private System.Windows.Forms.TextBox SetWristText;
        private System.Windows.Forms.TextBox SendBuftxtBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button Claw_btn3;
        private System.Windows.Forms.Button Claw_btn2;
        private System.Windows.Forms.Button Claw_btn1;
    }
}


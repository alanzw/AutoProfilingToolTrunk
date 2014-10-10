namespace AutoProfilingForm
{
    partial class MdiChildForAnalysis
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
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.winChartViewer1 = new ChartDirector.WinChartViewer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonChooseSingleInput = new System.Windows.Forms.Button();
            this.buttonChooseInputSet = new System.Windows.Forms.Button();
            this.textBoxSingleInput = new System.Windows.Forms.TextBox();
            this.textBoxInpuSet = new System.Windows.Forms.TextBox();
            this.panel3 = new System.Windows.Forms.Panel();
            this.checkBoxShowFps = new System.Windows.Forms.CheckBox();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.comboBoxShowOption = new System.Windows.Forms.ComboBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxGpuWindowSizeInSecond = new System.Windows.Forms.TextBox();
            this.textBoxCpuWindowInSecond = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.textBoxWindowSizeInFrame = new System.Windows.Forms.TextBox();
            this.textBoxCpWindowSizeInFrame = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.checkBoxShowGpu = new System.Windows.Forms.CheckBox();
            this.checkBoxShowCpu = new System.Windows.Forms.CheckBox();
            this.label6 = new System.Windows.Forms.Label();
            this.buttonSave = new System.Windows.Forms.Button();
            this.panel2 = new System.Windows.Forms.Panel();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).BeginInit();
            this.panel1.SuspendLayout();
            this.panel3.SuspendLayout();
            this.panel2.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 170F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.winChartViewer1, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel3, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.panel2, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Absolute, 140F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(983, 517);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // winChartViewer1
            // 
            this.winChartViewer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.winChartViewer1.Location = new System.Drawing.Point(173, 143);
            this.winChartViewer1.Name = "winChartViewer1";
            this.winChartViewer1.Size = new System.Drawing.Size(807, 371);
            this.winChartViewer1.TabIndex = 0;
            this.winChartViewer1.TabStop = false;
            this.winChartViewer1.MouseMovePlotArea += new System.Windows.Forms.MouseEventHandler(this.winChartViewer1_MouseMovePlotArea);
            this.winChartViewer1.ViewPortChanged += new ChartDirector.WinViewPortEventHandler(this.winChartViewer1_ViewPortChanged);
            this.winChartViewer1.MouseEnter += new System.EventHandler(this.winChartViewer1_MouseEnter);
            this.winChartViewer1.MouseLeave += new System.EventHandler(this.winChartViewer1_MouseLeave);
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.buttonStart);
            this.panel1.Controls.Add(this.buttonChooseSingleInput);
            this.panel1.Controls.Add(this.buttonChooseInputSet);
            this.panel1.Controls.Add(this.textBoxSingleInput);
            this.panel1.Controls.Add(this.textBoxInpuSet);
            this.panel1.Location = new System.Drawing.Point(173, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(807, 134);
            this.panel1.TabIndex = 1;
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(730, 104);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(61, 23);
            this.buttonStart.TabIndex = 4;
            this.buttonStart.Text = "Start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.buttonStart_Click);
            // 
            // buttonChooseSingleInput
            // 
            this.buttonChooseSingleInput.Location = new System.Drawing.Point(753, 73);
            this.buttonChooseSingleInput.Name = "buttonChooseSingleInput";
            this.buttonChooseSingleInput.Size = new System.Drawing.Size(38, 23);
            this.buttonChooseSingleInput.TabIndex = 3;
            this.buttonChooseSingleInput.Text = "...";
            this.buttonChooseSingleInput.UseVisualStyleBackColor = true;
            this.buttonChooseSingleInput.Click += new System.EventHandler(this.buttonChooseSingleInput_Click);
            // 
            // buttonChooseInputSet
            // 
            this.buttonChooseInputSet.Location = new System.Drawing.Point(753, 36);
            this.buttonChooseInputSet.Name = "buttonChooseInputSet";
            this.buttonChooseInputSet.Size = new System.Drawing.Size(38, 23);
            this.buttonChooseInputSet.TabIndex = 2;
            this.buttonChooseInputSet.Text = "...";
            this.buttonChooseInputSet.UseVisualStyleBackColor = true;
            this.buttonChooseInputSet.Click += new System.EventHandler(this.buttonChooseInputSet_Click);
            // 
            // textBoxSingleInput
            // 
            this.textBoxSingleInput.Location = new System.Drawing.Point(3, 75);
            this.textBoxSingleInput.Name = "textBoxSingleInput";
            this.textBoxSingleInput.Size = new System.Drawing.Size(744, 21);
            this.textBoxSingleInput.TabIndex = 1;
            // 
            // textBoxInpuSet
            // 
            this.textBoxInpuSet.Location = new System.Drawing.Point(3, 38);
            this.textBoxInpuSet.Name = "textBoxInpuSet";
            this.textBoxInpuSet.Size = new System.Drawing.Size(744, 21);
            this.textBoxInpuSet.TabIndex = 0;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.checkBoxShowFps);
            this.panel3.Controls.Add(this.radioButton2);
            this.panel3.Controls.Add(this.radioButton1);
            this.panel3.Controls.Add(this.comboBoxShowOption);
            this.panel3.Controls.Add(this.label11);
            this.panel3.Controls.Add(this.textBoxGpuWindowSizeInSecond);
            this.panel3.Controls.Add(this.textBoxCpuWindowInSecond);
            this.panel3.Controls.Add(this.label9);
            this.panel3.Controls.Add(this.label10);
            this.panel3.Controls.Add(this.textBoxWindowSizeInFrame);
            this.panel3.Controls.Add(this.textBoxCpWindowSizeInFrame);
            this.panel3.Controls.Add(this.label8);
            this.panel3.Controls.Add(this.label7);
            this.panel3.Controls.Add(this.checkBoxShowGpu);
            this.panel3.Controls.Add(this.checkBoxShowCpu);
            this.panel3.Controls.Add(this.label6);
            this.panel3.Controls.Add(this.buttonSave);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(3, 143);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(164, 371);
            this.panel3.TabIndex = 3;
            // 
            // checkBoxShowFps
            // 
            this.checkBoxShowFps.AutoSize = true;
            this.checkBoxShowFps.Checked = true;
            this.checkBoxShowFps.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxShowFps.Location = new System.Drawing.Point(17, 149);
            this.checkBoxShowFps.Name = "checkBoxShowFps";
            this.checkBoxShowFps.Size = new System.Drawing.Size(72, 16);
            this.checkBoxShowFps.TabIndex = 19;
            this.checkBoxShowFps.Text = "show fps";
            this.checkBoxShowFps.UseVisualStyleBackColor = true;
            this.checkBoxShowFps.CheckedChanged += new System.EventHandler(this.checkBoxShowFps_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(18, 83);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(107, 16);
            this.radioButton2.TabIndex = 18;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "show in second";
            this.radioButton2.UseVisualStyleBackColor = true;
            this.radioButton2.CheckedChanged += new System.EventHandler(this.radioButton2_CheckedChanged);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(18, 61);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(101, 16);
            this.radioButton1.TabIndex = 17;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "show in frame";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // comboBoxShowOption
            // 
            this.comboBoxShowOption.FormattingEnabled = true;
            this.comboBoxShowOption.Location = new System.Drawing.Point(17, 18);
            this.comboBoxShowOption.Name = "comboBoxShowOption";
            this.comboBoxShowOption.Size = new System.Drawing.Size(121, 20);
            this.comboBoxShowOption.TabIndex = 16;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(16, 3);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(89, 12);
            this.label11.TabIndex = 15;
            this.label11.Text = "Choose To See:";
            // 
            // textBoxGpuWindowSizeInSecond
            // 
            this.textBoxGpuWindowSizeInSecond.Location = new System.Drawing.Point(17, 310);
            this.textBoxGpuWindowSizeInSecond.Name = "textBoxGpuWindowSizeInSecond";
            this.textBoxGpuWindowSizeInSecond.Size = new System.Drawing.Size(130, 21);
            this.textBoxGpuWindowSizeInSecond.TabIndex = 13;
            // 
            // textBoxCpuWindowInSecond
            // 
            this.textBoxCpuWindowInSecond.Location = new System.Drawing.Point(17, 272);
            this.textBoxCpuWindowInSecond.Name = "textBoxCpuWindowInSecond";
            this.textBoxCpuWindowInSecond.Size = new System.Drawing.Size(130, 21);
            this.textBoxCpuWindowInSecond.TabIndex = 12;
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(15, 295);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(125, 12);
            this.label9.TabIndex = 11;
            this.label9.Text = "gpu window size: (s)";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(15, 257);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(125, 12);
            this.label10.TabIndex = 10;
            this.label10.Text = "cpu window size: (s)";
            // 
            // textBoxWindowSizeInFrame
            // 
            this.textBoxWindowSizeInFrame.Location = new System.Drawing.Point(17, 232);
            this.textBoxWindowSizeInFrame.Name = "textBoxWindowSizeInFrame";
            this.textBoxWindowSizeInFrame.Size = new System.Drawing.Size(130, 21);
            this.textBoxWindowSizeInFrame.TabIndex = 9;
            // 
            // textBoxCpWindowSizeInFrame
            // 
            this.textBoxCpWindowSizeInFrame.Location = new System.Drawing.Point(17, 191);
            this.textBoxCpWindowSizeInFrame.Name = "textBoxCpWindowSizeInFrame";
            this.textBoxCpWindowSizeInFrame.Size = new System.Drawing.Size(130, 21);
            this.textBoxCpWindowSizeInFrame.TabIndex = 8;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(15, 217);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(149, 12);
            this.label8.TabIndex = 7;
            this.label8.Text = "gpu window size: (frame)";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(15, 176);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(149, 12);
            this.label7.TabIndex = 6;
            this.label7.Text = "cpu window size: (frame)";
            // 
            // checkBoxShowGpu
            // 
            this.checkBoxShowGpu.AutoSize = true;
            this.checkBoxShowGpu.Checked = true;
            this.checkBoxShowGpu.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxShowGpu.Location = new System.Drawing.Point(17, 127);
            this.checkBoxShowGpu.Name = "checkBoxShowGpu";
            this.checkBoxShowGpu.Size = new System.Drawing.Size(72, 16);
            this.checkBoxShowGpu.TabIndex = 3;
            this.checkBoxShowGpu.Text = "show gpu";
            this.checkBoxShowGpu.UseVisualStyleBackColor = true;
            this.checkBoxShowGpu.CheckedChanged += new System.EventHandler(this.checkBoxShowGpu_CheckedChanged);
            // 
            // checkBoxShowCpu
            // 
            this.checkBoxShowCpu.AutoSize = true;
            this.checkBoxShowCpu.Checked = true;
            this.checkBoxShowCpu.CheckState = System.Windows.Forms.CheckState.Checked;
            this.checkBoxShowCpu.Location = new System.Drawing.Point(17, 104);
            this.checkBoxShowCpu.Name = "checkBoxShowCpu";
            this.checkBoxShowCpu.Size = new System.Drawing.Size(72, 16);
            this.checkBoxShowCpu.TabIndex = 2;
            this.checkBoxShowCpu.Text = "show cpu";
            this.checkBoxShowCpu.UseVisualStyleBackColor = true;
            this.checkBoxShowCpu.CheckedChanged += new System.EventHandler(this.checkBoxShowCpu_CheckedChanged);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(15, 46);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(101, 12);
            this.label6.TabIndex = 1;
            this.label6.Text = "Show Option: (s)";
            this.label6.Click += new System.EventHandler(this.label6_Click);
            // 
            // buttonSave
            // 
            this.buttonSave.Location = new System.Drawing.Point(72, 336);
            this.buttonSave.Name = "buttonSave";
            this.buttonSave.Size = new System.Drawing.Size(75, 23);
            this.buttonSave.TabIndex = 0;
            this.buttonSave.Text = "Save...";
            this.buttonSave.UseVisualStyleBackColor = true;
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.label5);
            this.panel2.Controls.Add(this.label4);
            this.panel2.Controls.Add(this.label3);
            this.panel2.Controls.Add(this.label2);
            this.panel2.Controls.Add(this.label1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(3, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(164, 134);
            this.panel2.TabIndex = 4;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(88, 61);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(17, 12);
            this.label5.TabIndex = 10;
            this.label5.Text = "or";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(54, 81);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(113, 12);
            this.label4.TabIndex = 9;
            this.label4.Text = "Single Input File:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(56, 41);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(95, 12);
            this.label3.TabIndex = 8;
            this.label3.Text = "Input Set File:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(15, 112);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(47, 12);
            this.label2.TabIndex = 7;
            this.label2.Text = "Result:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(15, 15);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(41, 12);
            this.label1.TabIndex = 6;
            this.label1.Text = "Input:";
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(0, 520);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(731, 17);
            this.hScrollBar1.TabIndex = 1;
            // 
            // MdiChildForAnalysis
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 541);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.Name = "MdiChildForAnalysis";
            this.Text = "Analysis The Window Size";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MdiChidForAnalysis_FormClosing);
            this.Load += new System.EventHandler(this.MdiChildForAnalysis_Load);
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private ChartDirector.WinChartViewer winChartViewer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonChooseSingleInput;
        private System.Windows.Forms.Button buttonChooseInputSet;
        private System.Windows.Forms.TextBox textBoxSingleInput;
        private System.Windows.Forms.TextBox textBoxInpuSet;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.CheckBox checkBoxShowGpu;
        private System.Windows.Forms.CheckBox checkBoxShowCpu;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Button buttonSave;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxWindowSizeInFrame;
        private System.Windows.Forms.TextBox textBoxCpWindowSizeInFrame;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxGpuWindowSizeInSecond;
        private System.Windows.Forms.TextBox textBoxCpuWindowInSecond;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.ComboBox comboBoxShowOption;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.CheckBox checkBoxShowFps;
    }
}
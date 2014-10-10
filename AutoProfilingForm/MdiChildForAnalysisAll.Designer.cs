namespace AutoProfilingForm
{
    partial class MdiChildForAnalysisAll
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
            this.panel1 = new System.Windows.Forms.Panel();
            this.buttonShowAll = new System.Windows.Forms.Button();
            this.buttonClear = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.checkBoxpShaderSize = new System.Windows.Forms.CheckBox();
            this.checkBoxpShaderCmd = new System.Windows.Forms.CheckBox();
            this.checkBoxVshaderConst = new System.Windows.Forms.CheckBox();
            this.checkBoxVshaderCmd = new System.Windows.Forms.CheckBox();
            this.checkBoxStateBlock = new System.Windows.Forms.CheckBox();
            this.checkBoxSetTex = new System.Windows.Forms.CheckBox();
            this.checkBoxTexSize = new System.Windows.Forms.CheckBox();
            this.checkBoxTexLock = new System.Windows.Forms.CheckBox();
            this.checkBoxSurSize = new System.Windows.Forms.CheckBox();
            this.checkBoxSurLock = new System.Windows.Forms.CheckBox();
            this.checkBoxVbSize = new System.Windows.Forms.CheckBox();
            this.checkBoxVbLock = new System.Windows.Forms.CheckBox();
            this.checkBoxIbSize = new System.Windows.Forms.CheckBox();
            this.checkBoxIbLock = new System.Windows.Forms.CheckBox();
            this.checkBoxData = new System.Windows.Forms.CheckBox();
            this.checkBoxDraw = new System.Windows.Forms.CheckBox();
            this.checkBoxTriangle = new System.Windows.Forms.CheckBox();
            this.checkBoxObj = new System.Windows.Forms.CheckBox();
            this.checkBoxRemoteParamSize = new System.Windows.Forms.CheckBox();
            this.checkBoxParamSize = new System.Windows.Forms.CheckBox();
            this.checkBoxFps = new System.Windows.Forms.CheckBox();
            this.checkBoxCmd = new System.Windows.Forms.CheckBox();
            this.checkBoxGpu = new System.Windows.Forms.CheckBox();
            this.checkBoxCpu = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.winChartViewer1 = new ChartDirector.WinChartViewer();
            this.panel2 = new System.Windows.Forms.Panel();
            this.buttonStart = new System.Windows.Forms.Button();
            this.buttonOpenInput = new System.Windows.Forms.Button();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.panel3 = new System.Windows.Forms.Panel();
            this.label2 = new System.Windows.Forms.Label();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.tableLayoutPanel1.SuspendLayout();
            this.panel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).BeginInit();
            this.panel2.SuspendLayout();
            this.panel3.SuspendLayout();
            this.SuspendLayout();
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Absolute, 160F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 100F));
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 1);
            this.tableLayoutPanel1.Controls.Add(this.winChartViewer1, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.panel2, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel3, 0, 0);
            this.tableLayoutPanel1.Location = new System.Drawing.Point(0, 0);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 2;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 7.948244F));
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 92.05176F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(984, 518);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.buttonShowAll);
            this.panel1.Controls.Add(this.buttonClear);
            this.panel1.Controls.Add(this.button1);
            this.panel1.Controls.Add(this.checkBoxpShaderSize);
            this.panel1.Controls.Add(this.checkBoxpShaderCmd);
            this.panel1.Controls.Add(this.checkBoxVshaderConst);
            this.panel1.Controls.Add(this.checkBoxVshaderCmd);
            this.panel1.Controls.Add(this.checkBoxStateBlock);
            this.panel1.Controls.Add(this.checkBoxSetTex);
            this.panel1.Controls.Add(this.checkBoxTexSize);
            this.panel1.Controls.Add(this.checkBoxTexLock);
            this.panel1.Controls.Add(this.checkBoxSurSize);
            this.panel1.Controls.Add(this.checkBoxSurLock);
            this.panel1.Controls.Add(this.checkBoxVbSize);
            this.panel1.Controls.Add(this.checkBoxVbLock);
            this.panel1.Controls.Add(this.checkBoxIbSize);
            this.panel1.Controls.Add(this.checkBoxIbLock);
            this.panel1.Controls.Add(this.checkBoxData);
            this.panel1.Controls.Add(this.checkBoxDraw);
            this.panel1.Controls.Add(this.checkBoxTriangle);
            this.panel1.Controls.Add(this.checkBoxObj);
            this.panel1.Controls.Add(this.checkBoxRemoteParamSize);
            this.panel1.Controls.Add(this.checkBoxParamSize);
            this.panel1.Controls.Add(this.checkBoxFps);
            this.panel1.Controls.Add(this.checkBoxCmd);
            this.panel1.Controls.Add(this.checkBoxGpu);
            this.panel1.Controls.Add(this.checkBoxCpu);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 44);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(154, 471);
            this.panel1.TabIndex = 0;
            // 
            // buttonShowAll
            // 
            this.buttonShowAll.Location = new System.Drawing.Point(85, 422);
            this.buttonShowAll.Name = "buttonShowAll";
            this.buttonShowAll.Size = new System.Drawing.Size(62, 23);
            this.buttonShowAll.TabIndex = 27;
            this.buttonShowAll.Text = "all";
            this.buttonShowAll.UseVisualStyleBackColor = true;
            this.buttonShowAll.Click += new System.EventHandler(this.buttonShowAll_Click);
            // 
            // buttonClear
            // 
            this.buttonClear.Location = new System.Drawing.Point(6, 422);
            this.buttonClear.Name = "buttonClear";
            this.buttonClear.Size = new System.Drawing.Size(62, 23);
            this.buttonClear.TabIndex = 26;
            this.buttonClear.Text = "clear";
            this.buttonClear.UseVisualStyleBackColor = true;
            this.buttonClear.Click += new System.EventHandler(this.buttonClear_Click);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 445);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(62, 23);
            this.button1.TabIndex = 25;
            this.button1.Text = "save ...";
            this.button1.UseVisualStyleBackColor = true;
            // 
            // checkBoxpShaderSize
            // 
            this.checkBoxpShaderSize.AutoSize = true;
            this.checkBoxpShaderSize.Location = new System.Drawing.Point(6, 400);
            this.checkBoxpShaderSize.Name = "checkBoxpShaderSize";
            this.checkBoxpShaderSize.Size = new System.Drawing.Size(102, 16);
            this.checkBoxpShaderSize.TabIndex = 24;
            this.checkBoxpShaderSize.Text = "pshader const";
            this.checkBoxpShaderSize.UseVisualStyleBackColor = true;
            this.checkBoxpShaderSize.CheckedChanged += new System.EventHandler(this.checkBoxpShaderSize_CheckedChanged);
            // 
            // checkBoxpShaderCmd
            // 
            this.checkBoxpShaderCmd.AutoSize = true;
            this.checkBoxpShaderCmd.Location = new System.Drawing.Point(6, 378);
            this.checkBoxpShaderCmd.Name = "checkBoxpShaderCmd";
            this.checkBoxpShaderCmd.Size = new System.Drawing.Size(90, 16);
            this.checkBoxpShaderCmd.TabIndex = 23;
            this.checkBoxpShaderCmd.Text = "pshader cmd";
            this.checkBoxpShaderCmd.UseVisualStyleBackColor = true;
            this.checkBoxpShaderCmd.CheckedChanged += new System.EventHandler(this.checkBoxpShaderCmd_CheckedChanged);
            // 
            // checkBoxVshaderConst
            // 
            this.checkBoxVshaderConst.AutoSize = true;
            this.checkBoxVshaderConst.Location = new System.Drawing.Point(6, 356);
            this.checkBoxVshaderConst.Name = "checkBoxVshaderConst";
            this.checkBoxVshaderConst.Size = new System.Drawing.Size(102, 16);
            this.checkBoxVshaderConst.TabIndex = 22;
            this.checkBoxVshaderConst.Text = "vshader const";
            this.checkBoxVshaderConst.UseVisualStyleBackColor = true;
            this.checkBoxVshaderConst.CheckedChanged += new System.EventHandler(this.checkBoxVshaderConst_CheckedChanged);
            // 
            // checkBoxVshaderCmd
            // 
            this.checkBoxVshaderCmd.AutoSize = true;
            this.checkBoxVshaderCmd.Location = new System.Drawing.Point(6, 334);
            this.checkBoxVshaderCmd.Name = "checkBoxVshaderCmd";
            this.checkBoxVshaderCmd.Size = new System.Drawing.Size(90, 16);
            this.checkBoxVshaderCmd.TabIndex = 21;
            this.checkBoxVshaderCmd.Text = "vshader cmd";
            this.checkBoxVshaderCmd.UseVisualStyleBackColor = true;
            this.checkBoxVshaderCmd.CheckedChanged += new System.EventHandler(this.checkBoxVshaderCmd_CheckedChanged);
            // 
            // checkBoxStateBlock
            // 
            this.checkBoxStateBlock.AutoSize = true;
            this.checkBoxStateBlock.Location = new System.Drawing.Point(6, 311);
            this.checkBoxStateBlock.Name = "checkBoxStateBlock";
            this.checkBoxStateBlock.Size = new System.Drawing.Size(90, 16);
            this.checkBoxStateBlock.TabIndex = 20;
            this.checkBoxStateBlock.Text = "state block";
            this.checkBoxStateBlock.UseVisualStyleBackColor = true;
            this.checkBoxStateBlock.CheckedChanged += new System.EventHandler(this.checkBoxStateBlock_CheckedChanged);
            // 
            // checkBoxSetTex
            // 
            this.checkBoxSetTex.AutoSize = true;
            this.checkBoxSetTex.Location = new System.Drawing.Point(6, 288);
            this.checkBoxSetTex.Name = "checkBoxSetTex";
            this.checkBoxSetTex.Size = new System.Drawing.Size(90, 16);
            this.checkBoxSetTex.TabIndex = 19;
            this.checkBoxSetTex.Text = "set texture";
            this.checkBoxSetTex.UseVisualStyleBackColor = true;
            this.checkBoxSetTex.CheckedChanged += new System.EventHandler(this.checkBoxSetTex_CheckedChanged);
            // 
            // checkBoxTexSize
            // 
            this.checkBoxTexSize.AutoSize = true;
            this.checkBoxTexSize.Location = new System.Drawing.Point(6, 265);
            this.checkBoxTexSize.Name = "checkBoxTexSize";
            this.checkBoxTexSize.Size = new System.Drawing.Size(72, 16);
            this.checkBoxTexSize.TabIndex = 18;
            this.checkBoxTexSize.Text = "tex size";
            this.checkBoxTexSize.UseVisualStyleBackColor = true;
            this.checkBoxTexSize.CheckedChanged += new System.EventHandler(this.checkBoxTexSize_CheckedChanged);
            // 
            // checkBoxTexLock
            // 
            this.checkBoxTexLock.AutoSize = true;
            this.checkBoxTexLock.Location = new System.Drawing.Point(6, 243);
            this.checkBoxTexLock.Name = "checkBoxTexLock";
            this.checkBoxTexLock.Size = new System.Drawing.Size(72, 16);
            this.checkBoxTexLock.TabIndex = 17;
            this.checkBoxTexLock.Text = "tex lock";
            this.checkBoxTexLock.UseVisualStyleBackColor = true;
            this.checkBoxTexLock.CheckedChanged += new System.EventHandler(this.checkBoxTexLock_CheckedChanged);
            // 
            // checkBoxSurSize
            // 
            this.checkBoxSurSize.AutoSize = true;
            this.checkBoxSurSize.Location = new System.Drawing.Point(6, 221);
            this.checkBoxSurSize.Name = "checkBoxSurSize";
            this.checkBoxSurSize.Size = new System.Drawing.Size(96, 16);
            this.checkBoxSurSize.TabIndex = 16;
            this.checkBoxSurSize.Text = "surface size";
            this.checkBoxSurSize.UseVisualStyleBackColor = true;
            this.checkBoxSurSize.CheckedChanged += new System.EventHandler(this.checkBoxSurSize_CheckedChanged);
            // 
            // checkBoxSurLock
            // 
            this.checkBoxSurLock.AutoSize = true;
            this.checkBoxSurLock.Location = new System.Drawing.Point(6, 199);
            this.checkBoxSurLock.Name = "checkBoxSurLock";
            this.checkBoxSurLock.Size = new System.Drawing.Size(96, 16);
            this.checkBoxSurLock.TabIndex = 15;
            this.checkBoxSurLock.Text = "surface lock";
            this.checkBoxSurLock.UseVisualStyleBackColor = true;
            this.checkBoxSurLock.CheckedChanged += new System.EventHandler(this.checkBoxSurLock_CheckedChanged);
            // 
            // checkBoxVbSize
            // 
            this.checkBoxVbSize.AutoSize = true;
            this.checkBoxVbSize.Location = new System.Drawing.Point(75, 132);
            this.checkBoxVbSize.Name = "checkBoxVbSize";
            this.checkBoxVbSize.Size = new System.Drawing.Size(66, 16);
            this.checkBoxVbSize.TabIndex = 14;
            this.checkBoxVbSize.Text = "vb size";
            this.checkBoxVbSize.UseVisualStyleBackColor = true;
            this.checkBoxVbSize.CheckedChanged += new System.EventHandler(this.checkBoxVbSize_CheckedChanged);
            // 
            // checkBoxVbLock
            // 
            this.checkBoxVbLock.AutoSize = true;
            this.checkBoxVbLock.Location = new System.Drawing.Point(6, 132);
            this.checkBoxVbLock.Name = "checkBoxVbLock";
            this.checkBoxVbLock.Size = new System.Drawing.Size(66, 16);
            this.checkBoxVbLock.TabIndex = 13;
            this.checkBoxVbLock.Text = "vb lock";
            this.checkBoxVbLock.UseVisualStyleBackColor = true;
            this.checkBoxVbLock.CheckedChanged += new System.EventHandler(this.checkBoxVbLock_CheckedChanged);
            // 
            // checkBoxIbSize
            // 
            this.checkBoxIbSize.AutoSize = true;
            this.checkBoxIbSize.Location = new System.Drawing.Point(75, 110);
            this.checkBoxIbSize.Name = "checkBoxIbSize";
            this.checkBoxIbSize.Size = new System.Drawing.Size(66, 16);
            this.checkBoxIbSize.TabIndex = 12;
            this.checkBoxIbSize.Text = "ib size";
            this.checkBoxIbSize.UseVisualStyleBackColor = true;
            this.checkBoxIbSize.CheckedChanged += new System.EventHandler(this.checkBoxIbSize_CheckedChanged);
            // 
            // checkBoxIbLock
            // 
            this.checkBoxIbLock.AutoSize = true;
            this.checkBoxIbLock.Location = new System.Drawing.Point(6, 110);
            this.checkBoxIbLock.Name = "checkBoxIbLock";
            this.checkBoxIbLock.Size = new System.Drawing.Size(66, 16);
            this.checkBoxIbLock.TabIndex = 11;
            this.checkBoxIbLock.Text = "ib lock";
            this.checkBoxIbLock.UseVisualStyleBackColor = true;
            this.checkBoxIbLock.CheckedChanged += new System.EventHandler(this.checkBoxIbLock_CheckedChanged);
            // 
            // checkBoxData
            // 
            this.checkBoxData.AutoSize = true;
            this.checkBoxData.Location = new System.Drawing.Point(75, 86);
            this.checkBoxData.Name = "checkBoxData";
            this.checkBoxData.Size = new System.Drawing.Size(48, 16);
            this.checkBoxData.TabIndex = 10;
            this.checkBoxData.Text = "data";
            this.checkBoxData.UseVisualStyleBackColor = true;
            this.checkBoxData.CheckedChanged += new System.EventHandler(this.checkBoxData_CheckedChanged);
            // 
            // checkBoxDraw
            // 
            this.checkBoxDraw.AutoSize = true;
            this.checkBoxDraw.Location = new System.Drawing.Point(6, 87);
            this.checkBoxDraw.Name = "checkBoxDraw";
            this.checkBoxDraw.Size = new System.Drawing.Size(48, 16);
            this.checkBoxDraw.TabIndex = 9;
            this.checkBoxDraw.Text = "draw";
            this.checkBoxDraw.UseVisualStyleBackColor = true;
            this.checkBoxDraw.CheckedChanged += new System.EventHandler(this.checkBoxDraw_CheckedChanged);
            // 
            // checkBoxTriangle
            // 
            this.checkBoxTriangle.AutoSize = true;
            this.checkBoxTriangle.Location = new System.Drawing.Point(75, 64);
            this.checkBoxTriangle.Name = "checkBoxTriangle";
            this.checkBoxTriangle.Size = new System.Drawing.Size(72, 16);
            this.checkBoxTriangle.TabIndex = 8;
            this.checkBoxTriangle.Text = "triangle";
            this.checkBoxTriangle.UseVisualStyleBackColor = true;
            this.checkBoxTriangle.CheckedChanged += new System.EventHandler(this.checkBoxTriangle_CheckedChanged);
            // 
            // checkBoxObj
            // 
            this.checkBoxObj.AutoSize = true;
            this.checkBoxObj.Location = new System.Drawing.Point(6, 64);
            this.checkBoxObj.Name = "checkBoxObj";
            this.checkBoxObj.Size = new System.Drawing.Size(60, 16);
            this.checkBoxObj.TabIndex = 7;
            this.checkBoxObj.Text = "object";
            this.checkBoxObj.UseVisualStyleBackColor = true;
            this.checkBoxObj.CheckedChanged += new System.EventHandler(this.checkBoxObj_CheckedChanged);
            // 
            // checkBoxRemoteParamSize
            // 
            this.checkBoxRemoteParamSize.AutoSize = true;
            this.checkBoxRemoteParamSize.Location = new System.Drawing.Point(6, 176);
            this.checkBoxRemoteParamSize.Name = "checkBoxRemoteParamSize";
            this.checkBoxRemoteParamSize.Size = new System.Drawing.Size(144, 16);
            this.checkBoxRemoteParamSize.TabIndex = 6;
            this.checkBoxRemoteParamSize.Text = "param size to remote";
            this.checkBoxRemoteParamSize.UseVisualStyleBackColor = true;
            this.checkBoxRemoteParamSize.CheckedChanged += new System.EventHandler(this.checkBoxRemoteParamSize_CheckedChanged);
            // 
            // checkBoxParamSize
            // 
            this.checkBoxParamSize.AutoSize = true;
            this.checkBoxParamSize.Location = new System.Drawing.Point(6, 154);
            this.checkBoxParamSize.Name = "checkBoxParamSize";
            this.checkBoxParamSize.Size = new System.Drawing.Size(108, 16);
            this.checkBoxParamSize.TabIndex = 5;
            this.checkBoxParamSize.Text = "parameter size";
            this.checkBoxParamSize.UseVisualStyleBackColor = true;
            this.checkBoxParamSize.CheckedChanged += new System.EventHandler(this.checkBoxParamSize_CheckedChanged);
            // 
            // checkBoxFps
            // 
            this.checkBoxFps.AutoSize = true;
            this.checkBoxFps.Location = new System.Drawing.Point(75, 42);
            this.checkBoxFps.Name = "checkBoxFps";
            this.checkBoxFps.Size = new System.Drawing.Size(42, 16);
            this.checkBoxFps.TabIndex = 4;
            this.checkBoxFps.Text = "fps";
            this.checkBoxFps.UseVisualStyleBackColor = true;
            this.checkBoxFps.CheckedChanged += new System.EventHandler(this.checkBoxFps_CheckedChanged);
            // 
            // checkBoxCmd
            // 
            this.checkBoxCmd.AutoSize = true;
            this.checkBoxCmd.Location = new System.Drawing.Point(6, 42);
            this.checkBoxCmd.Name = "checkBoxCmd";
            this.checkBoxCmd.Size = new System.Drawing.Size(42, 16);
            this.checkBoxCmd.TabIndex = 3;
            this.checkBoxCmd.Text = "cmd";
            this.checkBoxCmd.UseVisualStyleBackColor = true;
            this.checkBoxCmd.CheckedChanged += new System.EventHandler(this.checkBoxCmd_CheckedChanged);
            // 
            // checkBoxGpu
            // 
            this.checkBoxGpu.AutoSize = true;
            this.checkBoxGpu.Location = new System.Drawing.Point(75, 20);
            this.checkBoxGpu.Name = "checkBoxGpu";
            this.checkBoxGpu.Size = new System.Drawing.Size(42, 16);
            this.checkBoxGpu.TabIndex = 2;
            this.checkBoxGpu.Text = "gpu";
            this.checkBoxGpu.UseVisualStyleBackColor = true;
            this.checkBoxGpu.CheckedChanged += new System.EventHandler(this.checkBoxGpu_CheckedChanged_1);
            // 
            // checkBoxCpu
            // 
            this.checkBoxCpu.AutoSize = true;
            this.checkBoxCpu.Location = new System.Drawing.Point(6, 20);
            this.checkBoxCpu.Name = "checkBoxCpu";
            this.checkBoxCpu.Size = new System.Drawing.Size(42, 16);
            this.checkBoxCpu.TabIndex = 1;
            this.checkBoxCpu.Text = "cpu";
            this.checkBoxCpu.UseVisualStyleBackColor = true;
            this.checkBoxCpu.CheckedChanged += new System.EventHandler(this.checkBoxCpu_CheckedChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(4, 4);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 12);
            this.label1.TabIndex = 0;
            this.label1.Text = "Show Option:";
            // 
            // winChartViewer1
            // 
            this.winChartViewer1.Location = new System.Drawing.Point(163, 44);
            this.winChartViewer1.Name = "winChartViewer1";
            this.winChartViewer1.Size = new System.Drawing.Size(818, 471);
            this.winChartViewer1.TabIndex = 1;
            this.winChartViewer1.TabStop = false;
            this.winChartViewer1.MouseMovePlotArea += new System.Windows.Forms.MouseEventHandler(this.winChartViewer1_MouseMovePlotArea);
            this.winChartViewer1.ViewPortChanged += new ChartDirector.WinViewPortEventHandler(this.winChartViewer1_ViewPortChanged);
            this.winChartViewer1.MouseEnter += new System.EventHandler(this.winChartViewer1_MouseEnter);
            this.winChartViewer1.MouseLeave += new System.EventHandler(this.winChartViewer1_MouseLeave);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.buttonStart);
            this.panel2.Controls.Add(this.buttonOpenInput);
            this.panel2.Controls.Add(this.textBox1);
            this.panel2.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel2.Location = new System.Drawing.Point(163, 3);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(818, 35);
            this.panel2.TabIndex = 2;
            // 
            // buttonStart
            // 
            this.buttonStart.Location = new System.Drawing.Point(734, 7);
            this.buttonStart.Name = "buttonStart";
            this.buttonStart.Size = new System.Drawing.Size(75, 23);
            this.buttonStart.TabIndex = 2;
            this.buttonStart.Text = "start";
            this.buttonStart.UseVisualStyleBackColor = true;
            this.buttonStart.Click += new System.EventHandler(this.button4_Click);
            // 
            // buttonOpenInput
            // 
            this.buttonOpenInput.Location = new System.Drawing.Point(695, 7);
            this.buttonOpenInput.Name = "buttonOpenInput";
            this.buttonOpenInput.Size = new System.Drawing.Size(33, 23);
            this.buttonOpenInput.TabIndex = 1;
            this.buttonOpenInput.Text = "...";
            this.buttonOpenInput.UseVisualStyleBackColor = true;
            this.buttonOpenInput.Click += new System.EventHandler(this.buttonOpenInput_Click);
            // 
            // textBox1
            // 
            this.textBox1.Location = new System.Drawing.Point(3, 9);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(686, 21);
            this.textBox1.TabIndex = 0;
            // 
            // panel3
            // 
            this.panel3.Controls.Add(this.label2);
            this.panel3.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel3.Location = new System.Drawing.Point(3, 3);
            this.panel3.Name = "panel3";
            this.panel3.Size = new System.Drawing.Size(154, 35);
            this.panel3.TabIndex = 3;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(3, 14);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(119, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "Input File for All:";
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(8, 521);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(981, 23);
            this.hScrollBar1.TabIndex = 1;
            this.hScrollBar1.ValueChanged += new System.EventHandler(this.hScrollBar1_ValueChanged);
            // 
            // MdiChildForAnalysisAll
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(984, 541);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.tableLayoutPanel1);
            this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "MdiChildForAnalysisAll";
            this.Text = "Analysis All";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MdiChildForAnalysisAll_FormClosing);
            this.Load += new System.EventHandler(this.MdiChildForAnalysisAll_Load);
            this.ResizeBegin += new System.EventHandler(this.MdiChildForAnalysisAll_ResizeBegin);
            this.tableLayoutPanel1.ResumeLayout(false);
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).EndInit();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            this.panel3.ResumeLayout(false);
            this.panel3.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private System.Windows.Forms.Panel panel1;
        private ChartDirector.WinChartViewer winChartViewer1;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.Panel panel3;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.CheckBox checkBoxpShaderSize;
        private System.Windows.Forms.CheckBox checkBoxpShaderCmd;
        private System.Windows.Forms.CheckBox checkBoxVshaderConst;
        private System.Windows.Forms.CheckBox checkBoxVshaderCmd;
        private System.Windows.Forms.CheckBox checkBoxStateBlock;
        private System.Windows.Forms.CheckBox checkBoxSetTex;
        private System.Windows.Forms.CheckBox checkBoxTexSize;
        private System.Windows.Forms.CheckBox checkBoxTexLock;
        private System.Windows.Forms.CheckBox checkBoxSurSize;
        private System.Windows.Forms.CheckBox checkBoxSurLock;
        private System.Windows.Forms.CheckBox checkBoxVbSize;
        private System.Windows.Forms.CheckBox checkBoxVbLock;
        private System.Windows.Forms.CheckBox checkBoxIbSize;
        private System.Windows.Forms.CheckBox checkBoxIbLock;
        private System.Windows.Forms.CheckBox checkBoxData;
        private System.Windows.Forms.CheckBox checkBoxDraw;
        private System.Windows.Forms.CheckBox checkBoxTriangle;
        private System.Windows.Forms.CheckBox checkBoxObj;
        private System.Windows.Forms.CheckBox checkBoxRemoteParamSize;
        private System.Windows.Forms.CheckBox checkBoxParamSize;
        private System.Windows.Forms.CheckBox checkBoxFps;
        private System.Windows.Forms.CheckBox checkBoxCmd;
        private System.Windows.Forms.CheckBox checkBoxGpu;
        private System.Windows.Forms.CheckBox checkBoxCpu;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button buttonClear;
        private System.Windows.Forms.Button buttonStart;
        private System.Windows.Forms.Button buttonOpenInput;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.Button buttonShowAll;
    }
}
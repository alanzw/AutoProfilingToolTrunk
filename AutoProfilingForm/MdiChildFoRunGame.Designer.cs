namespace AutoProfilingForm
{
    partial class MdiChildFoRunGame
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
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MdiChildFoRunGame));
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle1 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle2 = new System.Windows.Forms.DataGridViewCellStyle();
            System.Windows.Forms.DataGridViewCellStyle dataGridViewCellStyle3 = new System.Windows.Forms.DataGridViewCellStyle();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPageNode = new System.Windows.Forms.TabPage();
            this.tabPageMonitor = new System.Windows.Forms.TabPage();
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.winChartViewer1 = new ChartDirector.WinChartViewer();
            this.panel1 = new System.Windows.Forms.Panel();
            this.checkBoxFps = new System.Windows.Forms.CheckBox();
            this.checkBoxShowGpu = new System.Windows.Forms.CheckBox();
            this.checkBoxShowCpu = new System.Windows.Forms.CheckBox();
            this.label1 = new System.Windows.Forms.Label();
            this.tabPageRunConfigure = new System.Windows.Forms.TabPage();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.consoleControl1 = new ConsoleControl.ConsoleControl();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.buttonChooseDBFile = new System.Windows.Forms.Button();
            this.buttonShowXml = new System.Windows.Forms.Button();
            this.textBoxDBFile = new System.Windows.Forms.TextBox();
            this.buttonSaveXmlDataSet = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.buttonAddConfigure = new System.Windows.Forms.Button();
            this.textBoxGameName = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.buttonChooseGameDirectory = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.textBoxSaveDirectory = new System.Windows.Forms.TextBox();
            this.buttonSaveResultDirectory = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBoxDllToUse = new System.Windows.Forms.ComboBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxSetName = new System.Windows.Forms.TextBox();
            this.textBoxSingleSetName = new System.Windows.Forms.TextBox();
            this.buttonRun = new System.Windows.Forms.Button();
            this.buttonSetFileName = new System.Windows.Forms.Button();
            this.label6 = new System.Windows.Forms.Label();
            this.button4 = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.radioButtonAll = new System.Windows.Forms.RadioButton();
            this.checkBoxLimitFps = new System.Windows.Forms.CheckBox();
            this.radioButtonSimple = new System.Windows.Forms.RadioButton();
            this.panel2 = new System.Windows.Forms.Panel();
            this.xmlBindingNavigate = new System.Windows.Forms.BindingNavigator(this.components);
            this.bindingNavigatorAddNewItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorCountItem = new System.Windows.Forms.ToolStripLabel();
            this.bindingNavigatorDeleteItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveFirstItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMovePreviousItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorPositionItem = new System.Windows.Forms.ToolStripTextBox();
            this.bindingNavigatorSeparator1 = new System.Windows.Forms.ToolStripSeparator();
            this.bindingNavigatorMoveNextItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorMoveLastItem = new System.Windows.Forms.ToolStripButton();
            this.bindingNavigatorSeparator2 = new System.Windows.Forms.ToolStripSeparator();
            this.dataGridView1 = new System.Windows.Forms.DataGridView();
            this.GameName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.GameDirectory = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SaveResultDirectory = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.SingleSetFileName = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.UseDll = new System.Windows.Forms.DataGridViewTextBoxColumn();
            this.tabPageGameConfigure = new System.Windows.Forms.TabPage();
            this.consoleControlConfig = new ConsoleControl.ConsoleControl();
            this.comboBoxCharactorFileFilter = new System.Windows.Forms.ComboBox();
            this.buttonUnselectOne = new System.Windows.Forms.Button();
            this.buttonSelectOne = new System.Windows.Forms.Button();
            this.buttonUnselectAll = new System.Windows.Forms.Button();
            this.buttonSelectAll = new System.Windows.Forms.Button();
            this.listBoxSelectedFiles = new System.Windows.Forms.ListBox();
            this.listBoxAllFiles = new System.Windows.Forms.ListBox();
            this.buttonStartGenerate = new System.Windows.Forms.Button();
            this.buttonSaveWeka = new System.Windows.Forms.Button();
            this.buttonChooseCharactorFile = new System.Windows.Forms.Button();
            this.textBoxSaveWekaFile = new System.Windows.Forms.TextBox();
            this.textBoxCharactorFileFolder = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.contextMenuStripForDataGrid = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.addColumnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteColumnToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.deleteRowToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.toRunToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.loadConfigureToRunToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.xmlBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.directoryEntry1 = new System.DirectoryServices.DirectoryEntry();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.textBoxCpuLabel = new System.Windows.Forms.TextBox();
            this.textBoxGpuLabel = new System.Windows.Forms.TextBox();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.textBoxGpuWindow = new System.Windows.Forms.TextBox();
            this.textBoxCpuWindow = new System.Windows.Forms.TextBox();
            this.textBoxGpuStepCount = new System.Windows.Forms.TextBox();
            this.textBoxCpuStepCount = new System.Windows.Forms.TextBox();
            this.label14 = new System.Windows.Forms.Label();
            this.label15 = new System.Windows.Forms.Label();
            this.radioButtonKeepOriginal = new System.Windows.Forms.RadioButton();
            this.radioButtonDiscretization = new System.Windows.Forms.RadioButton();
            this.tabControl1.SuspendLayout();
            this.tabPageMonitor.SuspendLayout();
            this.tableLayoutPanel1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).BeginInit();
            this.panel1.SuspendLayout();
            this.tabPageRunConfigure.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.panel2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.xmlBindingNavigate)).BeginInit();
            this.xmlBindingNavigate.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).BeginInit();
            this.tabPageGameConfigure.SuspendLayout();
            this.contextMenuStripForDataGrid.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.xmlBindingSource)).BeginInit();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPageNode);
            this.tabControl1.Controls.Add(this.tabPageMonitor);
            this.tabControl1.Controls.Add(this.tabPageRunConfigure);
            this.tabControl1.Controls.Add(this.tabPageGameConfigure);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(994, 551);
            this.tabControl1.TabIndex = 0;
            this.tabControl1.Selected += new System.Windows.Forms.TabControlEventHandler(this.tabControl1_Selected);
            // 
            // tabPageNode
            // 
            this.tabPageNode.Location = new System.Drawing.Point(4, 22);
            this.tabPageNode.Name = "tabPageNode";
            this.tabPageNode.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageNode.Size = new System.Drawing.Size(986, 525);
            this.tabPageNode.TabIndex = 0;
            this.tabPageNode.Text = "Node Allocation";
            this.tabPageNode.UseVisualStyleBackColor = true;
            // 
            // tabPageMonitor
            // 
            this.tabPageMonitor.Controls.Add(this.tableLayoutPanel1);
            this.tabPageMonitor.Location = new System.Drawing.Point(4, 22);
            this.tabPageMonitor.Name = "tabPageMonitor";
            this.tabPageMonitor.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageMonitor.Size = new System.Drawing.Size(986, 525);
            this.tabPageMonitor.TabIndex = 1;
            this.tabPageMonitor.Text = "Resource Monitor";
            this.tabPageMonitor.UseVisualStyleBackColor = true;
            // 
            // tableLayoutPanel1
            // 
            this.tableLayoutPanel1.ColumnCount = 2;
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 18.35616F));
            this.tableLayoutPanel1.ColumnStyles.Add(new System.Windows.Forms.ColumnStyle(System.Windows.Forms.SizeType.Percent, 81.64384F));
            this.tableLayoutPanel1.Controls.Add(this.winChartViewer1, 1, 0);
            this.tableLayoutPanel1.Controls.Add(this.panel1, 0, 0);
            this.tableLayoutPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tableLayoutPanel1.Location = new System.Drawing.Point(3, 3);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            this.tableLayoutPanel1.RowCount = 1;
            this.tableLayoutPanel1.RowStyles.Add(new System.Windows.Forms.RowStyle(System.Windows.Forms.SizeType.Percent, 50F));
            this.tableLayoutPanel1.Size = new System.Drawing.Size(980, 519);
            this.tableLayoutPanel1.TabIndex = 0;
            // 
            // winChartViewer1
            // 
            this.winChartViewer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.winChartViewer1.Location = new System.Drawing.Point(182, 3);
            this.winChartViewer1.Name = "winChartViewer1";
            this.winChartViewer1.Size = new System.Drawing.Size(795, 513);
            this.winChartViewer1.TabIndex = 0;
            this.winChartViewer1.TabStop = false;
            // 
            // panel1
            // 
            this.panel1.Controls.Add(this.checkBoxFps);
            this.panel1.Controls.Add(this.checkBoxShowGpu);
            this.panel1.Controls.Add(this.checkBoxShowCpu);
            this.panel1.Controls.Add(this.label1);
            this.panel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.panel1.Location = new System.Drawing.Point(3, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(173, 513);
            this.panel1.TabIndex = 1;
            // 
            // checkBoxFps
            // 
            this.checkBoxFps.AutoSize = true;
            this.checkBoxFps.Location = new System.Drawing.Point(6, 73);
            this.checkBoxFps.Name = "checkBoxFps";
            this.checkBoxFps.Size = new System.Drawing.Size(42, 16);
            this.checkBoxFps.TabIndex = 3;
            this.checkBoxFps.Text = "fps";
            this.checkBoxFps.UseVisualStyleBackColor = true;
            // 
            // checkBoxShowGpu
            // 
            this.checkBoxShowGpu.AutoSize = true;
            this.checkBoxShowGpu.Location = new System.Drawing.Point(6, 51);
            this.checkBoxShowGpu.Name = "checkBoxShowGpu";
            this.checkBoxShowGpu.Size = new System.Drawing.Size(42, 16);
            this.checkBoxShowGpu.TabIndex = 2;
            this.checkBoxShowGpu.Text = "gpu";
            this.checkBoxShowGpu.UseVisualStyleBackColor = true;
            // 
            // checkBoxShowCpu
            // 
            this.checkBoxShowCpu.AutoSize = true;
            this.checkBoxShowCpu.Location = new System.Drawing.Point(6, 29);
            this.checkBoxShowCpu.Name = "checkBoxShowCpu";
            this.checkBoxShowCpu.Size = new System.Drawing.Size(42, 16);
            this.checkBoxShowCpu.TabIndex = 1;
            this.checkBoxShowCpu.Text = "cpu";
            this.checkBoxShowCpu.UseVisualStyleBackColor = true;
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
            // tabPageRunConfigure
            // 
            this.tabPageRunConfigure.BackColor = System.Drawing.Color.White;
            this.tabPageRunConfigure.Controls.Add(this.groupBox4);
            this.tabPageRunConfigure.Controls.Add(this.groupBox3);
            this.tabPageRunConfigure.Controls.Add(this.groupBox2);
            this.tabPageRunConfigure.Controls.Add(this.groupBox1);
            this.tabPageRunConfigure.Controls.Add(this.panel2);
            this.tabPageRunConfigure.Location = new System.Drawing.Point(4, 22);
            this.tabPageRunConfigure.Name = "tabPageRunConfigure";
            this.tabPageRunConfigure.Size = new System.Drawing.Size(986, 525);
            this.tabPageRunConfigure.TabIndex = 2;
            this.tabPageRunConfigure.Text = "Run Configuration";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.consoleControl1);
            this.groupBox4.Location = new System.Drawing.Point(485, 3);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(493, 269);
            this.groupBox4.TabIndex = 39;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Console Window:";
            // 
            // consoleControl1
            // 
            this.consoleControl1.Font = new System.Drawing.Font("Consolas", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.consoleControl1.IsInputEnabled = true;
            this.consoleControl1.Location = new System.Drawing.Point(0, 15);
            this.consoleControl1.Name = "consoleControl1";
            this.consoleControl1.SendKeyboardCommandsToProcess = false;
            this.consoleControl1.ShowDiagnostics = false;
            this.consoleControl1.Size = new System.Drawing.Size(493, 254);
            this.consoleControl1.TabIndex = 27;
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.buttonChooseDBFile);
            this.groupBox3.Controls.Add(this.buttonShowXml);
            this.groupBox3.Controls.Add(this.textBoxDBFile);
            this.groupBox3.Controls.Add(this.buttonSaveXmlDataSet);
            this.groupBox3.Location = new System.Drawing.Point(8, 206);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Size = new System.Drawing.Size(471, 66);
            this.groupBox3.TabIndex = 38;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "Game DB:";
            // 
            // buttonChooseDBFile
            // 
            this.buttonChooseDBFile.Location = new System.Drawing.Point(318, 10);
            this.buttonChooseDBFile.Name = "buttonChooseDBFile";
            this.buttonChooseDBFile.Size = new System.Drawing.Size(40, 23);
            this.buttonChooseDBFile.TabIndex = 32;
            this.buttonChooseDBFile.Text = "...";
            this.buttonChooseDBFile.UseVisualStyleBackColor = true;
            this.buttonChooseDBFile.Click += new System.EventHandler(this.buttonChooseDBFile_Click);
            // 
            // buttonShowXml
            // 
            this.buttonShowXml.Location = new System.Drawing.Point(419, 10);
            this.buttonShowXml.Name = "buttonShowXml";
            this.buttonShowXml.Size = new System.Drawing.Size(47, 23);
            this.buttonShowXml.TabIndex = 30;
            this.buttonShowXml.Text = "show";
            this.buttonShowXml.UseVisualStyleBackColor = true;
            this.buttonShowXml.Click += new System.EventHandler(this.buttonSaveXml_Click);
            // 
            // textBoxDBFile
            // 
            this.textBoxDBFile.Location = new System.Drawing.Point(9, 38);
            this.textBoxDBFile.Name = "textBoxDBFile";
            this.textBoxDBFile.Size = new System.Drawing.Size(457, 21);
            this.textBoxDBFile.TabIndex = 31;
            // 
            // buttonSaveXmlDataSet
            // 
            this.buttonSaveXmlDataSet.Enabled = false;
            this.buttonSaveXmlDataSet.Location = new System.Drawing.Point(364, 10);
            this.buttonSaveXmlDataSet.Name = "buttonSaveXmlDataSet";
            this.buttonSaveXmlDataSet.Size = new System.Drawing.Size(49, 23);
            this.buttonSaveXmlDataSet.TabIndex = 33;
            this.buttonSaveXmlDataSet.Text = "save";
            this.buttonSaveXmlDataSet.UseVisualStyleBackColor = true;
            this.buttonSaveXmlDataSet.Click += new System.EventHandler(this.buttonSaveXmlDataSet_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.buttonAddConfigure);
            this.groupBox2.Controls.Add(this.textBoxGameName);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.buttonChooseGameDirectory);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.textBoxSaveDirectory);
            this.groupBox2.Controls.Add(this.buttonSaveResultDirectory);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.comboBoxDllToUse);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.textBoxSetName);
            this.groupBox2.Controls.Add(this.textBoxSingleSetName);
            this.groupBox2.Controls.Add(this.buttonRun);
            this.groupBox2.Controls.Add(this.buttonSetFileName);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.button4);
            this.groupBox2.Location = new System.Drawing.Point(8, 53);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(471, 147);
            this.groupBox2.TabIndex = 37;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Run Configuration:";
            // 
            // buttonAddConfigure
            // 
            this.buttonAddConfigure.Location = new System.Drawing.Point(364, 115);
            this.buttonAddConfigure.Name = "buttonAddConfigure";
            this.buttonAddConfigure.Size = new System.Drawing.Size(50, 23);
            this.buttonAddConfigure.TabIndex = 30;
            this.buttonAddConfigure.Text = "add";
            this.buttonAddConfigure.UseVisualStyleBackColor = true;
            // 
            // textBoxGameName
            // 
            this.textBoxGameName.Location = new System.Drawing.Point(109, 14);
            this.textBoxGameName.Name = "textBoxGameName";
            this.textBoxGameName.Size = new System.Drawing.Size(305, 21);
            this.textBoxGameName.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(8, 17);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(65, 12);
            this.label2.TabIndex = 0;
            this.label2.Text = "game file:";
            // 
            // buttonChooseGameDirectory
            // 
            this.buttonChooseGameDirectory.Location = new System.Drawing.Point(420, 12);
            this.buttonChooseGameDirectory.Name = "buttonChooseGameDirectory";
            this.buttonChooseGameDirectory.Size = new System.Drawing.Size(47, 23);
            this.buttonChooseGameDirectory.TabIndex = 2;
            this.buttonChooseGameDirectory.Text = "...";
            this.buttonChooseGameDirectory.UseVisualStyleBackColor = true;
            this.buttonChooseGameDirectory.Click += new System.EventHandler(this.buttonChooseGameDirectory_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(8, 43);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(95, 12);
            this.label3.TabIndex = 3;
            this.label3.Text = "save directory:";
            // 
            // textBoxSaveDirectory
            // 
            this.textBoxSaveDirectory.Location = new System.Drawing.Point(109, 40);
            this.textBoxSaveDirectory.Name = "textBoxSaveDirectory";
            this.textBoxSaveDirectory.Size = new System.Drawing.Size(305, 21);
            this.textBoxSaveDirectory.TabIndex = 4;
            // 
            // buttonSaveResultDirectory
            // 
            this.buttonSaveResultDirectory.Location = new System.Drawing.Point(420, 38);
            this.buttonSaveResultDirectory.Name = "buttonSaveResultDirectory";
            this.buttonSaveResultDirectory.Size = new System.Drawing.Size(47, 23);
            this.buttonSaveResultDirectory.TabIndex = 5;
            this.buttonSaveResultDirectory.Text = "...";
            this.buttonSaveResultDirectory.UseVisualStyleBackColor = true;
            this.buttonSaveResultDirectory.Click += new System.EventHandler(this.buttonSaveResultDirectory_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(8, 69);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(59, 12);
            this.label4.TabIndex = 6;
            this.label4.Text = "set name:";
            // 
            // comboBoxDllToUse
            // 
            this.comboBoxDllToUse.DisplayMember = "1";
            this.comboBoxDllToUse.FormattingEnabled = true;
            this.comboBoxDllToUse.Items.AddRange(new object[] {
            "HookD3D.dll",
            "HookD3DAll.dll"});
            this.comboBoxDllToUse.Location = new System.Drawing.Point(109, 117);
            this.comboBoxDllToUse.Name = "comboBoxDllToUse";
            this.comboBoxDllToUse.Size = new System.Drawing.Size(178, 20);
            this.comboBoxDllToUse.TabIndex = 29;
            this.comboBoxDllToUse.ValueMember = "1";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(8, 95);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(101, 12);
            this.label5.TabIndex = 7;
            this.label5.Text = "single set name:";
            // 
            // textBoxSetName
            // 
            this.textBoxSetName.Location = new System.Drawing.Point(109, 66);
            this.textBoxSetName.Name = "textBoxSetName";
            this.textBoxSetName.Size = new System.Drawing.Size(305, 21);
            this.textBoxSetName.TabIndex = 8;
            // 
            // textBoxSingleSetName
            // 
            this.textBoxSingleSetName.Location = new System.Drawing.Point(109, 92);
            this.textBoxSingleSetName.Name = "textBoxSingleSetName";
            this.textBoxSingleSetName.Size = new System.Drawing.Size(305, 21);
            this.textBoxSingleSetName.TabIndex = 9;
            // 
            // buttonRun
            // 
            this.buttonRun.Location = new System.Drawing.Point(420, 115);
            this.buttonRun.Name = "buttonRun";
            this.buttonRun.Size = new System.Drawing.Size(47, 23);
            this.buttonRun.TabIndex = 22;
            this.buttonRun.Text = "run";
            this.buttonRun.UseVisualStyleBackColor = true;
            this.buttonRun.Click += new System.EventHandler(this.buttonRun_Click);
            // 
            // buttonSetFileName
            // 
            this.buttonSetFileName.Location = new System.Drawing.Point(420, 64);
            this.buttonSetFileName.Name = "buttonSetFileName";
            this.buttonSetFileName.Size = new System.Drawing.Size(47, 23);
            this.buttonSetFileName.TabIndex = 10;
            this.buttonSetFileName.Text = "ok";
            this.buttonSetFileName.UseVisualStyleBackColor = true;
            this.buttonSetFileName.Click += new System.EventHandler(this.buttonSetFileName_Click);
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(8, 122);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(53, 12);
            this.label6.TabIndex = 12;
            this.label6.Text = "use dll:";
            // 
            // button4
            // 
            this.button4.Location = new System.Drawing.Point(420, 92);
            this.button4.Name = "button4";
            this.button4.Size = new System.Drawing.Size(47, 23);
            this.button4.TabIndex = 11;
            this.button4.Text = "ok";
            this.button4.UseVisualStyleBackColor = true;
            this.button4.Click += new System.EventHandler(this.button4_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioButtonAll);
            this.groupBox1.Controls.Add(this.checkBoxLimitFps);
            this.groupBox1.Controls.Add(this.radioButtonSimple);
            this.groupBox1.Location = new System.Drawing.Point(8, 3);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(471, 41);
            this.groupBox1.TabIndex = 36;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Global Options:";
            // 
            // radioButtonAll
            // 
            this.radioButtonAll.AutoSize = true;
            this.radioButtonAll.Checked = true;
            this.radioButtonAll.Location = new System.Drawing.Point(96, 20);
            this.radioButtonAll.Name = "radioButtonAll";
            this.radioButtonAll.Size = new System.Drawing.Size(41, 16);
            this.radioButtonAll.TabIndex = 20;
            this.radioButtonAll.TabStop = true;
            this.radioButtonAll.Text = "all";
            this.radioButtonAll.UseVisualStyleBackColor = true;
            this.radioButtonAll.CheckedChanged += new System.EventHandler(this.radioButtonAll_CheckedChanged);
            // 
            // checkBoxLimitFps
            // 
            this.checkBoxLimitFps.AutoSize = true;
            this.checkBoxLimitFps.Location = new System.Drawing.Point(6, 20);
            this.checkBoxLimitFps.Name = "checkBoxLimitFps";
            this.checkBoxLimitFps.Size = new System.Drawing.Size(84, 16);
            this.checkBoxLimitFps.TabIndex = 15;
            this.checkBoxLimitFps.Text = "limite fps";
            this.checkBoxLimitFps.UseVisualStyleBackColor = true;
            this.checkBoxLimitFps.CheckedChanged += new System.EventHandler(this.checkBoxLimitFps_CheckedChanged);
            // 
            // radioButtonSimple
            // 
            this.radioButtonSimple.AutoSize = true;
            this.radioButtonSimple.Location = new System.Drawing.Point(143, 19);
            this.radioButtonSimple.Name = "radioButtonSimple";
            this.radioButtonSimple.Size = new System.Drawing.Size(59, 16);
            this.radioButtonSimple.TabIndex = 21;
            this.radioButtonSimple.Text = "simple";
            this.radioButtonSimple.UseVisualStyleBackColor = true;
            this.radioButtonSimple.CheckedChanged += new System.EventHandler(this.radioButtonSimple_CheckedChanged);
            // 
            // panel2
            // 
            this.panel2.Controls.Add(this.xmlBindingNavigate);
            this.panel2.Controls.Add(this.dataGridView1);
            this.panel2.Location = new System.Drawing.Point(8, 271);
            this.panel2.Name = "panel2";
            this.panel2.Size = new System.Drawing.Size(970, 246);
            this.panel2.TabIndex = 34;
            // 
            // xmlBindingNavigate
            // 
            this.xmlBindingNavigate.AddNewItem = this.bindingNavigatorAddNewItem;
            this.xmlBindingNavigate.CountItem = this.bindingNavigatorCountItem;
            this.xmlBindingNavigate.DeleteItem = this.bindingNavigatorDeleteItem;
            this.xmlBindingNavigate.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bindingNavigatorMoveFirstItem,
            this.bindingNavigatorMovePreviousItem,
            this.bindingNavigatorSeparator,
            this.bindingNavigatorPositionItem,
            this.bindingNavigatorCountItem,
            this.bindingNavigatorSeparator1,
            this.bindingNavigatorMoveNextItem,
            this.bindingNavigatorMoveLastItem,
            this.bindingNavigatorSeparator2,
            this.bindingNavigatorAddNewItem,
            this.bindingNavigatorDeleteItem});
            this.xmlBindingNavigate.Location = new System.Drawing.Point(0, 0);
            this.xmlBindingNavigate.MoveFirstItem = this.bindingNavigatorMoveFirstItem;
            this.xmlBindingNavigate.MoveLastItem = this.bindingNavigatorMoveLastItem;
            this.xmlBindingNavigate.MoveNextItem = this.bindingNavigatorMoveNextItem;
            this.xmlBindingNavigate.MovePreviousItem = this.bindingNavigatorMovePreviousItem;
            this.xmlBindingNavigate.Name = "xmlBindingNavigate";
            this.xmlBindingNavigate.PositionItem = this.bindingNavigatorPositionItem;
            this.xmlBindingNavigate.Size = new System.Drawing.Size(970, 25);
            this.xmlBindingNavigate.TabIndex = 8;
            this.xmlBindingNavigate.Text = "bindingNavigator1";
            // 
            // bindingNavigatorAddNewItem
            // 
            this.bindingNavigatorAddNewItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorAddNewItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorAddNewItem.Image")));
            this.bindingNavigatorAddNewItem.Name = "bindingNavigatorAddNewItem";
            this.bindingNavigatorAddNewItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorAddNewItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorAddNewItem.Text = "新添";
            // 
            // bindingNavigatorCountItem
            // 
            this.bindingNavigatorCountItem.Name = "bindingNavigatorCountItem";
            this.bindingNavigatorCountItem.Size = new System.Drawing.Size(31, 22);
            this.bindingNavigatorCountItem.Text = "/ {0}";
            this.bindingNavigatorCountItem.ToolTipText = "总项数";
            // 
            // bindingNavigatorDeleteItem
            // 
            this.bindingNavigatorDeleteItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorDeleteItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorDeleteItem.Image")));
            this.bindingNavigatorDeleteItem.Name = "bindingNavigatorDeleteItem";
            this.bindingNavigatorDeleteItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorDeleteItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorDeleteItem.Text = "删除";
            // 
            // bindingNavigatorMoveFirstItem
            // 
            this.bindingNavigatorMoveFirstItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveFirstItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveFirstItem.Image")));
            this.bindingNavigatorMoveFirstItem.Name = "bindingNavigatorMoveFirstItem";
            this.bindingNavigatorMoveFirstItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveFirstItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveFirstItem.Text = "移到第一条记录";
            // 
            // bindingNavigatorMovePreviousItem
            // 
            this.bindingNavigatorMovePreviousItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMovePreviousItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMovePreviousItem.Image")));
            this.bindingNavigatorMovePreviousItem.Name = "bindingNavigatorMovePreviousItem";
            this.bindingNavigatorMovePreviousItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMovePreviousItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMovePreviousItem.Text = "移到上一条记录";
            // 
            // bindingNavigatorSeparator
            // 
            this.bindingNavigatorSeparator.Name = "bindingNavigatorSeparator";
            this.bindingNavigatorSeparator.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorPositionItem
            // 
            this.bindingNavigatorPositionItem.AccessibleName = "位置";
            this.bindingNavigatorPositionItem.AutoSize = false;
            this.bindingNavigatorPositionItem.Name = "bindingNavigatorPositionItem";
            this.bindingNavigatorPositionItem.Size = new System.Drawing.Size(50, 23);
            this.bindingNavigatorPositionItem.Text = "0";
            this.bindingNavigatorPositionItem.ToolTipText = "当前位置";
            // 
            // bindingNavigatorSeparator1
            // 
            this.bindingNavigatorSeparator1.Name = "bindingNavigatorSeparator1";
            this.bindingNavigatorSeparator1.Size = new System.Drawing.Size(6, 25);
            // 
            // bindingNavigatorMoveNextItem
            // 
            this.bindingNavigatorMoveNextItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveNextItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveNextItem.Image")));
            this.bindingNavigatorMoveNextItem.Name = "bindingNavigatorMoveNextItem";
            this.bindingNavigatorMoveNextItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveNextItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveNextItem.Text = "移到下一条记录";
            // 
            // bindingNavigatorMoveLastItem
            // 
            this.bindingNavigatorMoveLastItem.DisplayStyle = System.Windows.Forms.ToolStripItemDisplayStyle.Image;
            this.bindingNavigatorMoveLastItem.Image = ((System.Drawing.Image)(resources.GetObject("bindingNavigatorMoveLastItem.Image")));
            this.bindingNavigatorMoveLastItem.Name = "bindingNavigatorMoveLastItem";
            this.bindingNavigatorMoveLastItem.RightToLeftAutoMirrorImage = true;
            this.bindingNavigatorMoveLastItem.Size = new System.Drawing.Size(23, 22);
            this.bindingNavigatorMoveLastItem.Text = "移到最后一条记录";
            // 
            // bindingNavigatorSeparator2
            // 
            this.bindingNavigatorSeparator2.Name = "bindingNavigatorSeparator2";
            this.bindingNavigatorSeparator2.Size = new System.Drawing.Size(6, 25);
            // 
            // dataGridView1
            // 
            this.dataGridView1.AllowDrop = true;
            dataGridViewCellStyle1.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle1.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle1.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle1.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle1.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle1.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle1.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView1.ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
            this.dataGridView1.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dataGridView1.Columns.AddRange(new System.Windows.Forms.DataGridViewColumn[] {
            this.GameName,
            this.GameDirectory,
            this.SaveResultDirectory,
            this.SingleSetFileName,
            this.UseDll});
            dataGridViewCellStyle2.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle2.BackColor = System.Drawing.SystemColors.Window;
            dataGridViewCellStyle2.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle2.ForeColor = System.Drawing.SystemColors.ControlText;
            dataGridViewCellStyle2.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle2.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle2.WrapMode = System.Windows.Forms.DataGridViewTriState.False;
            this.dataGridView1.DefaultCellStyle = dataGridViewCellStyle2;
            this.dataGridView1.Location = new System.Drawing.Point(0, 28);
            this.dataGridView1.Name = "dataGridView1";
            dataGridViewCellStyle3.Alignment = System.Windows.Forms.DataGridViewContentAlignment.MiddleLeft;
            dataGridViewCellStyle3.BackColor = System.Drawing.SystemColors.Control;
            dataGridViewCellStyle3.Font = new System.Drawing.Font("宋体", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(134)));
            dataGridViewCellStyle3.ForeColor = System.Drawing.SystemColors.WindowText;
            dataGridViewCellStyle3.SelectionBackColor = System.Drawing.SystemColors.Highlight;
            dataGridViewCellStyle3.SelectionForeColor = System.Drawing.SystemColors.HighlightText;
            dataGridViewCellStyle3.WrapMode = System.Windows.Forms.DataGridViewTriState.True;
            this.dataGridView1.RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
            this.dataGridView1.RowTemplate.Height = 23;
            this.dataGridView1.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.dataGridView1.Size = new System.Drawing.Size(978, 218);
            this.dataGridView1.TabIndex = 0;
            this.dataGridView1.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView1_ColumnHeaderMouseClick);
            this.dataGridView1.RowHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.dataGridView1_RowHeaderMouseClick);
            // 
            // GameName
            // 
            this.GameName.DataPropertyName = "GameName";
            this.GameName.HeaderText = "Game Name";
            this.GameName.Name = "GameName";
            // 
            // GameDirectory
            // 
            this.GameDirectory.DataPropertyName = "GameDirectory";
            this.GameDirectory.HeaderText = "Game Directory";
            this.GameDirectory.Name = "GameDirectory";
            this.GameDirectory.Width = 200;
            // 
            // SaveResultDirectory
            // 
            this.SaveResultDirectory.DataPropertyName = "SaveResultDirectory";
            this.SaveResultDirectory.HeaderText = "Save Result Directory";
            this.SaveResultDirectory.Name = "SaveResultDirectory";
            this.SaveResultDirectory.Width = 200;
            // 
            // SingleSetFileName
            // 
            this.SingleSetFileName.DataPropertyName = "SingleSetFileName";
            this.SingleSetFileName.HeaderText = "Single Set File Name";
            this.SingleSetFileName.Name = "SingleSetFileName";
            this.SingleSetFileName.Width = 200;
            // 
            // UseDll
            // 
            this.UseDll.DataPropertyName = "UseDll";
            this.UseDll.HeaderText = "Use Dll";
            this.UseDll.Name = "UseDll";
            // 
            // tabPageGameConfigure
            // 
            this.tabPageGameConfigure.Controls.Add(this.radioButtonDiscretization);
            this.tabPageGameConfigure.Controls.Add(this.radioButtonKeepOriginal);
            this.tabPageGameConfigure.Controls.Add(this.textBoxGpuStepCount);
            this.tabPageGameConfigure.Controls.Add(this.textBoxCpuStepCount);
            this.tabPageGameConfigure.Controls.Add(this.label14);
            this.tabPageGameConfigure.Controls.Add(this.label15);
            this.tabPageGameConfigure.Controls.Add(this.textBoxGpuWindow);
            this.tabPageGameConfigure.Controls.Add(this.textBoxCpuWindow);
            this.tabPageGameConfigure.Controls.Add(this.label13);
            this.tabPageGameConfigure.Controls.Add(this.label12);
            this.tabPageGameConfigure.Controls.Add(this.textBoxGpuLabel);
            this.tabPageGameConfigure.Controls.Add(this.textBoxCpuLabel);
            this.tabPageGameConfigure.Controls.Add(this.label11);
            this.tabPageGameConfigure.Controls.Add(this.label10);
            this.tabPageGameConfigure.Controls.Add(this.label9);
            this.tabPageGameConfigure.Controls.Add(this.consoleControlConfig);
            this.tabPageGameConfigure.Controls.Add(this.comboBoxCharactorFileFilter);
            this.tabPageGameConfigure.Controls.Add(this.buttonUnselectOne);
            this.tabPageGameConfigure.Controls.Add(this.buttonSelectOne);
            this.tabPageGameConfigure.Controls.Add(this.buttonUnselectAll);
            this.tabPageGameConfigure.Controls.Add(this.buttonSelectAll);
            this.tabPageGameConfigure.Controls.Add(this.listBoxSelectedFiles);
            this.tabPageGameConfigure.Controls.Add(this.listBoxAllFiles);
            this.tabPageGameConfigure.Controls.Add(this.buttonStartGenerate);
            this.tabPageGameConfigure.Controls.Add(this.buttonSaveWeka);
            this.tabPageGameConfigure.Controls.Add(this.buttonChooseCharactorFile);
            this.tabPageGameConfigure.Controls.Add(this.textBoxSaveWekaFile);
            this.tabPageGameConfigure.Controls.Add(this.textBoxCharactorFileFolder);
            this.tabPageGameConfigure.Controls.Add(this.label8);
            this.tabPageGameConfigure.Controls.Add(this.label7);
            this.tabPageGameConfigure.Location = new System.Drawing.Point(4, 22);
            this.tabPageGameConfigure.Name = "tabPageGameConfigure";
            this.tabPageGameConfigure.Padding = new System.Windows.Forms.Padding(3);
            this.tabPageGameConfigure.Size = new System.Drawing.Size(986, 525);
            this.tabPageGameConfigure.TabIndex = 3;
            this.tabPageGameConfigure.Text = "Configure Game";
            this.tabPageGameConfigure.UseVisualStyleBackColor = true;
            this.tabPageGameConfigure.Click += new System.EventHandler(this.tabPageGameConfigure_Click);
            // 
            // consoleControlConfig
            // 
            this.consoleControlConfig.IsInputEnabled = true;
            this.consoleControlConfig.Location = new System.Drawing.Point(401, 58);
            this.consoleControlConfig.Name = "consoleControlConfig";
            this.consoleControlConfig.SendKeyboardCommandsToProcess = false;
            this.consoleControlConfig.ShowDiagnostics = false;
            this.consoleControlConfig.Size = new System.Drawing.Size(577, 461);
            this.consoleControlConfig.TabIndex = 18;
            // 
            // comboBoxCharactorFileFilter
            // 
            this.comboBoxCharactorFileFilter.FormattingEnabled = true;
            this.comboBoxCharactorFileFilter.Items.AddRange(new object[] {
            "*.second.log",
            "*.frame.log",
            "*.single.set",
            "*.single.log"});
            this.comboBoxCharactorFileFilter.Location = new System.Drawing.Point(829, 31);
            this.comboBoxCharactorFileFilter.Name = "comboBoxCharactorFileFilter";
            this.comboBoxCharactorFileFilter.Size = new System.Drawing.Size(149, 20);
            this.comboBoxCharactorFileFilter.TabIndex = 17;
            this.comboBoxCharactorFileFilter.Text = "*.second.log";
            // 
            // buttonUnselectOne
            // 
            this.buttonUnselectOne.Location = new System.Drawing.Point(169, 211);
            this.buttonUnselectOne.Name = "buttonUnselectOne";
            this.buttonUnselectOne.Size = new System.Drawing.Size(75, 23);
            this.buttonUnselectOne.TabIndex = 16;
            this.buttonUnselectOne.Text = "<<";
            this.buttonUnselectOne.UseVisualStyleBackColor = true;
            this.buttonUnselectOne.Click += new System.EventHandler(this.buttonUnselectOne_Click);
            // 
            // buttonSelectOne
            // 
            this.buttonSelectOne.Location = new System.Drawing.Point(169, 182);
            this.buttonSelectOne.Name = "buttonSelectOne";
            this.buttonSelectOne.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectOne.TabIndex = 15;
            this.buttonSelectOne.Text = ">>";
            this.buttonSelectOne.UseVisualStyleBackColor = true;
            this.buttonSelectOne.Click += new System.EventHandler(this.buttonSelectOne_Click);
            // 
            // buttonUnselectAll
            // 
            this.buttonUnselectAll.Location = new System.Drawing.Point(169, 109);
            this.buttonUnselectAll.Name = "buttonUnselectAll";
            this.buttonUnselectAll.Size = new System.Drawing.Size(75, 23);
            this.buttonUnselectAll.TabIndex = 14;
            this.buttonUnselectAll.Text = "All<<";
            this.buttonUnselectAll.UseVisualStyleBackColor = true;
            this.buttonUnselectAll.Click += new System.EventHandler(this.buttonUnselectAll_Click);
            // 
            // buttonSelectAll
            // 
            this.buttonSelectAll.Location = new System.Drawing.Point(169, 80);
            this.buttonSelectAll.Name = "buttonSelectAll";
            this.buttonSelectAll.Size = new System.Drawing.Size(75, 23);
            this.buttonSelectAll.TabIndex = 13;
            this.buttonSelectAll.Text = "All>>";
            this.buttonSelectAll.UseVisualStyleBackColor = true;
            this.buttonSelectAll.Click += new System.EventHandler(this.buttonSelectAll_Click);
            // 
            // listBoxSelectedFiles
            // 
            this.listBoxSelectedFiles.FormattingEnabled = true;
            this.listBoxSelectedFiles.HorizontalScrollbar = true;
            this.listBoxSelectedFiles.ItemHeight = 12;
            this.listBoxSelectedFiles.Location = new System.Drawing.Point(275, 58);
            this.listBoxSelectedFiles.Name = "listBoxSelectedFiles";
            this.listBoxSelectedFiles.Size = new System.Drawing.Size(120, 196);
            this.listBoxSelectedFiles.TabIndex = 12;
            // 
            // listBoxAllFiles
            // 
            this.listBoxAllFiles.FormattingEnabled = true;
            this.listBoxAllFiles.HorizontalScrollbar = true;
            this.listBoxAllFiles.ItemHeight = 12;
            this.listBoxAllFiles.Location = new System.Drawing.Point(10, 58);
            this.listBoxAllFiles.Name = "listBoxAllFiles";
            this.listBoxAllFiles.Size = new System.Drawing.Size(120, 196);
            this.listBoxAllFiles.TabIndex = 11;
            // 
            // buttonStartGenerate
            // 
            this.buttonStartGenerate.Location = new System.Drawing.Point(320, 494);
            this.buttonStartGenerate.Name = "buttonStartGenerate";
            this.buttonStartGenerate.Size = new System.Drawing.Size(75, 23);
            this.buttonStartGenerate.TabIndex = 10;
            this.buttonStartGenerate.Text = "start";
            this.buttonStartGenerate.UseVisualStyleBackColor = true;
            this.buttonStartGenerate.Click += new System.EventHandler(this.buttonStartGenerate_Click);
            // 
            // buttonSaveWeka
            // 
            this.buttonSaveWeka.Location = new System.Drawing.Point(354, 465);
            this.buttonSaveWeka.Name = "buttonSaveWeka";
            this.buttonSaveWeka.Size = new System.Drawing.Size(41, 23);
            this.buttonSaveWeka.TabIndex = 9;
            this.buttonSaveWeka.Text = "...";
            this.buttonSaveWeka.UseVisualStyleBackColor = true;
            this.buttonSaveWeka.Click += new System.EventHandler(this.buttonSaveWeka_Click);
            // 
            // buttonChooseCharactorFile
            // 
            this.buttonChooseCharactorFile.Location = new System.Drawing.Point(748, 29);
            this.buttonChooseCharactorFile.Name = "buttonChooseCharactorFile";
            this.buttonChooseCharactorFile.Size = new System.Drawing.Size(75, 23);
            this.buttonChooseCharactorFile.TabIndex = 8;
            this.buttonChooseCharactorFile.Text = "...";
            this.buttonChooseCharactorFile.UseVisualStyleBackColor = true;
            this.buttonChooseCharactorFile.Click += new System.EventHandler(this.buttonChooseCharactorFile_Click);
            // 
            // textBoxSaveWekaFile
            // 
            this.textBoxSaveWekaFile.Location = new System.Drawing.Point(10, 465);
            this.textBoxSaveWekaFile.Name = "textBoxSaveWekaFile";
            this.textBoxSaveWekaFile.Size = new System.Drawing.Size(338, 21);
            this.textBoxSaveWekaFile.TabIndex = 7;
            // 
            // textBoxCharactorFileFolder
            // 
            this.textBoxCharactorFileFolder.Location = new System.Drawing.Point(169, 31);
            this.textBoxCharactorFileFolder.Name = "textBoxCharactorFileFolder";
            this.textBoxCharactorFileFolder.Size = new System.Drawing.Size(573, 21);
            this.textBoxCharactorFileFolder.TabIndex = 6;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(8, 450);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(53, 12);
            this.label8.TabIndex = 5;
            this.label8.Text = "Save to:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(8, 34);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(155, 12);
            this.label7.TabIndex = 4;
            this.label7.Text = "Charactor File Directory:";
            // 
            // contextMenuStripForDataGrid
            // 
            this.contextMenuStripForDataGrid.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.addColumnToolStripMenuItem,
            this.deleteColumnToolStripMenuItem,
            this.deleteRowToolStripMenuItem,
            this.toRunToolStripMenuItem,
            this.loadConfigureToRunToolStripMenuItem});
            this.contextMenuStripForDataGrid.Name = "contextMenuStripForDataGrid";
            this.contextMenuStripForDataGrid.Size = new System.Drawing.Size(210, 114);
            // 
            // addColumnToolStripMenuItem
            // 
            this.addColumnToolStripMenuItem.Name = "addColumnToolStripMenuItem";
            this.addColumnToolStripMenuItem.Size = new System.Drawing.Size(209, 22);
            this.addColumnToolStripMenuItem.Text = "Add Column";
            this.addColumnToolStripMenuItem.Click += new System.EventHandler(this.addColumnToolStripMenuItem_Click);
            // 
            // deleteColumnToolStripMenuItem
            // 
            this.deleteColumnToolStripMenuItem.Name = "deleteColumnToolStripMenuItem";
            this.deleteColumnToolStripMenuItem.Size = new System.Drawing.Size(209, 22);
            this.deleteColumnToolStripMenuItem.Text = "Delete Column";
            this.deleteColumnToolStripMenuItem.Click += new System.EventHandler(this.deleteColumnToolStripMenuItem_Click);
            // 
            // deleteRowToolStripMenuItem
            // 
            this.deleteRowToolStripMenuItem.Name = "deleteRowToolStripMenuItem";
            this.deleteRowToolStripMenuItem.Size = new System.Drawing.Size(209, 22);
            this.deleteRowToolStripMenuItem.Text = "Delete Row";
            this.deleteRowToolStripMenuItem.Click += new System.EventHandler(this.deleteRowToolStripMenuItem_Click);
            // 
            // toRunToolStripMenuItem
            // 
            this.toRunToolStripMenuItem.Name = "toRunToolStripMenuItem";
            this.toRunToolStripMenuItem.Size = new System.Drawing.Size(209, 22);
            this.toRunToolStripMenuItem.Text = "To Run";
            this.toRunToolStripMenuItem.Click += new System.EventHandler(this.toRunToolStripMenuItem_Click);
            // 
            // loadConfigureToRunToolStripMenuItem
            // 
            this.loadConfigureToRunToolStripMenuItem.Name = "loadConfigureToRunToolStripMenuItem";
            this.loadConfigureToRunToolStripMenuItem.Size = new System.Drawing.Size(209, 22);
            this.loadConfigureToRunToolStripMenuItem.Text = "Load Configure To Run";
            this.loadConfigureToRunToolStripMenuItem.Click += new System.EventHandler(this.loadConfigureToRunToolStripMenuItem_Click);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(6, 262);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(95, 12);
            this.label9.TabIndex = 19;
            this.label9.Text = "Discretization:";
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(10, 287);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(65, 12);
            this.label10.TabIndex = 20;
            this.label10.Text = "CPU label:";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(10, 317);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(65, 12);
            this.label11.TabIndex = 21;
            this.label11.Text = "GPU label:";
            // 
            // textBoxCpuLabel
            // 
            this.textBoxCpuLabel.Location = new System.Drawing.Point(72, 284);
            this.textBoxCpuLabel.Name = "textBoxCpuLabel";
            this.textBoxCpuLabel.Size = new System.Drawing.Size(58, 21);
            this.textBoxCpuLabel.TabIndex = 22;
            this.textBoxCpuLabel.Text = "C";
            // 
            // textBoxGpuLabel
            // 
            this.textBoxGpuLabel.Location = new System.Drawing.Point(72, 314);
            this.textBoxGpuLabel.Name = "textBoxGpuLabel";
            this.textBoxGpuLabel.Size = new System.Drawing.Size(58, 21);
            this.textBoxGpuLabel.TabIndex = 23;
            this.textBoxGpuLabel.Text = "G";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Location = new System.Drawing.Point(152, 287);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(71, 12);
            this.label12.TabIndex = 24;
            this.label12.Text = "CPU window:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(152, 317);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(71, 12);
            this.label13.TabIndex = 25;
            this.label13.Text = "GPU window:";
            // 
            // textBoxGpuWindow
            // 
            this.textBoxGpuWindow.Location = new System.Drawing.Point(226, 314);
            this.textBoxGpuWindow.Name = "textBoxGpuWindow";
            this.textBoxGpuWindow.Size = new System.Drawing.Size(54, 21);
            this.textBoxGpuWindow.TabIndex = 27;
            this.textBoxGpuWindow.Text = "1";
            // 
            // textBoxCpuWindow
            // 
            this.textBoxCpuWindow.Location = new System.Drawing.Point(226, 284);
            this.textBoxCpuWindow.Name = "textBoxCpuWindow";
            this.textBoxCpuWindow.Size = new System.Drawing.Size(54, 21);
            this.textBoxCpuWindow.TabIndex = 26;
            this.textBoxCpuWindow.Text = "1";
            // 
            // textBoxGpuStepCount
            // 
            this.textBoxGpuStepCount.Enabled = false;
            this.textBoxGpuStepCount.Location = new System.Drawing.Point(348, 314);
            this.textBoxGpuStepCount.Name = "textBoxGpuStepCount";
            this.textBoxGpuStepCount.Size = new System.Drawing.Size(47, 21);
            this.textBoxGpuStepCount.TabIndex = 31;
            // 
            // textBoxCpuStepCount
            // 
            this.textBoxCpuStepCount.Enabled = false;
            this.textBoxCpuStepCount.Location = new System.Drawing.Point(348, 284);
            this.textBoxCpuStepCount.Name = "textBoxCpuStepCount";
            this.textBoxCpuStepCount.Size = new System.Drawing.Size(47, 21);
            this.textBoxCpuStepCount.TabIndex = 30;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(301, 317);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(41, 12);
            this.label14.TabIndex = 29;
            this.label14.Text = "Count:";
            // 
            // label15
            // 
            this.label15.AutoSize = true;
            this.label15.Location = new System.Drawing.Point(301, 287);
            this.label15.Name = "label15";
            this.label15.Size = new System.Drawing.Size(41, 12);
            this.label15.TabIndex = 28;
            this.label15.Text = "Count:";
            // 
            // radioButtonKeepOriginal
            // 
            this.radioButtonKeepOriginal.AutoSize = true;
            this.radioButtonKeepOriginal.Location = new System.Drawing.Point(119, 262);
            this.radioButtonKeepOriginal.Name = "radioButtonKeepOriginal";
            this.radioButtonKeepOriginal.Size = new System.Drawing.Size(101, 16);
            this.radioButtonKeepOriginal.TabIndex = 32;
            this.radioButtonKeepOriginal.Text = "keep original";
            this.radioButtonKeepOriginal.UseVisualStyleBackColor = true;
            // 
            // radioButtonDiscretization
            // 
            this.radioButtonDiscretization.AutoSize = true;
            this.radioButtonDiscretization.Checked = true;
            this.radioButtonDiscretization.Location = new System.Drawing.Point(226, 260);
            this.radioButtonDiscretization.Name = "radioButtonDiscretization";
            this.radioButtonDiscretization.Size = new System.Drawing.Size(107, 16);
            this.radioButtonDiscretization.TabIndex = 33;
            this.radioButtonDiscretization.TabStop = true;
            this.radioButtonDiscretization.Text = "discretization";
            this.radioButtonDiscretization.UseVisualStyleBackColor = true;
            // 
            // MdiChildFoRunGame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 551);
            this.Controls.Add(this.tabControl1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow;
            this.MinimizeBox = false;
            this.Name = "MdiChildFoRunGame";
            this.Text = "Run Game";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.MdiChildFoRunGame_FormClosing);
            this.Load += new System.EventHandler(this.MdiChildFoRunGame_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPageMonitor.ResumeLayout(false);
            this.tableLayoutPanel1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.winChartViewer1)).EndInit();
            this.panel1.ResumeLayout(false);
            this.panel1.PerformLayout();
            this.tabPageRunConfigure.ResumeLayout(false);
            this.groupBox4.ResumeLayout(false);
            this.groupBox3.ResumeLayout(false);
            this.groupBox3.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.panel2.ResumeLayout(false);
            this.panel2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.xmlBindingNavigate)).EndInit();
            this.xmlBindingNavigate.ResumeLayout(false);
            this.xmlBindingNavigate.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.dataGridView1)).EndInit();
            this.tabPageGameConfigure.ResumeLayout(false);
            this.tabPageGameConfigure.PerformLayout();
            this.contextMenuStripForDataGrid.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.xmlBindingSource)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPageNode;
        private System.Windows.Forms.TabPage tabPageMonitor;
        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private ChartDirector.WinChartViewer winChartViewer1;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.CheckBox checkBoxFps;
        private System.Windows.Forms.CheckBox checkBoxShowGpu;
        private System.Windows.Forms.CheckBox checkBoxShowCpu;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TabPage tabPageRunConfigure;
        private System.Windows.Forms.TextBox textBoxGameName;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Button button4;
        private System.Windows.Forms.Button buttonSetFileName;
        private System.Windows.Forms.TextBox textBoxSingleSetName;
        private System.Windows.Forms.TextBox textBoxSetName;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Button buttonSaveResultDirectory;
        private System.Windows.Forms.TextBox textBoxSaveDirectory;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Button buttonChooseGameDirectory;
        private System.Windows.Forms.Button buttonRun;
        private System.Windows.Forms.RadioButton radioButtonSimple;
        private System.Windows.Forms.RadioButton radioButtonAll;
        private System.Windows.Forms.CheckBox checkBoxLimitFps;
        private System.Windows.Forms.Label label6;
        private ConsoleControl.ConsoleControl consoleControl1;
        private System.Windows.Forms.ComboBox comboBoxDllToUse;
        private System.Windows.Forms.TabPage tabPageGameConfigure;
        private System.Windows.Forms.ContextMenuStrip contextMenuStripForDataGrid;
        private System.Windows.Forms.ToolStripMenuItem addColumnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteColumnToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem deleteRowToolStripMenuItem;
        private System.Windows.Forms.BindingSource xmlBindingSource;
        private System.Windows.Forms.Panel panel2;
        private System.Windows.Forms.BindingNavigator xmlBindingNavigate;
        private System.Windows.Forms.ToolStripButton bindingNavigatorAddNewItem;
        private System.Windows.Forms.ToolStripLabel bindingNavigatorCountItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorDeleteItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveFirstItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMovePreviousItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator;
        private System.Windows.Forms.ToolStripTextBox bindingNavigatorPositionItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator1;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveNextItem;
        private System.Windows.Forms.ToolStripButton bindingNavigatorMoveLastItem;
        private System.Windows.Forms.ToolStripSeparator bindingNavigatorSeparator2;
        private System.Windows.Forms.DataGridView dataGridView1;
        private System.Windows.Forms.Button buttonSaveXmlDataSet;
        private System.Windows.Forms.Button buttonChooseDBFile;
        private System.Windows.Forms.TextBox textBoxDBFile;
        private System.Windows.Forms.Button buttonShowXml;
        private System.Windows.Forms.ToolStripMenuItem toRunToolStripMenuItem;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.ToolStripMenuItem loadConfigureToRunToolStripMenuItem;
        private System.Windows.Forms.Button buttonAddConfigure;
        private System.Windows.Forms.DataGridViewTextBoxColumn GameName;
        private System.Windows.Forms.DataGridViewTextBoxColumn GameDirectory;
        private System.Windows.Forms.DataGridViewTextBoxColumn SaveResultDirectory;
        private System.Windows.Forms.DataGridViewTextBoxColumn SingleSetFileName;
        private System.Windows.Forms.DataGridViewTextBoxColumn UseDll;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.TextBox textBoxSaveWekaFile;
        private System.Windows.Forms.TextBox textBoxCharactorFileFolder;
        private System.Windows.Forms.Button buttonSaveWeka;
        private System.Windows.Forms.Button buttonChooseCharactorFile;
        private System.Windows.Forms.Button buttonStartGenerate;
        private System.DirectoryServices.DirectoryEntry directoryEntry1;
        private System.Windows.Forms.Button buttonUnselectOne;
        private System.Windows.Forms.Button buttonSelectOne;
        private System.Windows.Forms.Button buttonUnselectAll;
        private System.Windows.Forms.Button buttonSelectAll;
        private System.Windows.Forms.ListBox listBoxSelectedFiles;
        private System.Windows.Forms.ListBox listBoxAllFiles;
        private System.Windows.Forms.ComboBox comboBoxCharactorFileFilter;
        private ConsoleControl.ConsoleControl consoleControlConfig;
        private System.Windows.Forms.TextBox textBoxGpuStepCount;
        private System.Windows.Forms.TextBox textBoxCpuStepCount;
        private System.Windows.Forms.Label label14;
        private System.Windows.Forms.Label label15;
        private System.Windows.Forms.TextBox textBoxGpuWindow;
        private System.Windows.Forms.TextBox textBoxCpuWindow;
        private System.Windows.Forms.Label label13;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.TextBox textBoxGpuLabel;
        private System.Windows.Forms.TextBox textBoxCpuLabel;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.RadioButton radioButtonDiscretization;
        private System.Windows.Forms.RadioButton radioButtonKeepOriginal;
    }
}
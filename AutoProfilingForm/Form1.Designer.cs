namespace AutoProfilingForm
{
    partial class Form1
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
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileFToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.runGameRToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.analysisAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.analysisWindowSizeWToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.analysisAllTToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.editEToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.copyImageCToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.helpHToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.userHelpVToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutAutoProfilingToolAToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.lisenceLToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.allCharactorAndEstimateToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileFToolStripMenuItem,
            this.editEToolStripMenuItem,
            this.helpHToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(994, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStripMain";
            // 
            // fileFToolStripMenuItem
            // 
            this.fileFToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.runGameRToolStripMenuItem,
            this.analysisAToolStripMenuItem});
            this.fileFToolStripMenuItem.Name = "fileFToolStripMenuItem";
            this.fileFToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.F)));
            this.fileFToolStripMenuItem.Size = new System.Drawing.Size(52, 20);
            this.fileFToolStripMenuItem.Text = "File(F)";
            // 
            // runGameRToolStripMenuItem
            // 
            this.runGameRToolStripMenuItem.Name = "runGameRToolStripMenuItem";
            this.runGameRToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.R)));
            this.runGameRToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.runGameRToolStripMenuItem.Text = "Run Game(R)";
            this.runGameRToolStripMenuItem.Click += new System.EventHandler(this.runGameRToolStripMenuItem_Click);
            // 
            // analysisAToolStripMenuItem
            // 
            this.analysisAToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.analysisWindowSizeWToolStripMenuItem,
            this.analysisAllTToolStripMenuItem,
            this.allCharactorAndEstimateToolStripMenuItem});
            this.analysisAToolStripMenuItem.Name = "analysisAToolStripMenuItem";
            this.analysisAToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.A)));
            this.analysisAToolStripMenuItem.Size = new System.Drawing.Size(189, 22);
            this.analysisAToolStripMenuItem.Text = "Analysis(A)";
            this.analysisAToolStripMenuItem.Click += new System.EventHandler(this.analysisAToolStripMenuItem_Click);
            // 
            // analysisWindowSizeWToolStripMenuItem
            // 
            this.analysisWindowSizeWToolStripMenuItem.Name = "analysisWindowSizeWToolStripMenuItem";
            this.analysisWindowSizeWToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.W)));
            this.analysisWindowSizeWToolStripMenuItem.Size = new System.Drawing.Size(261, 22);
            this.analysisWindowSizeWToolStripMenuItem.Text = "Analysis Window Size(W)";
            this.analysisWindowSizeWToolStripMenuItem.Click += new System.EventHandler(this.analysisWindowSizeWToolStripMenuItem_Click);
            // 
            // analysisAllTToolStripMenuItem
            // 
            this.analysisAllTToolStripMenuItem.Name = "analysisAllTToolStripMenuItem";
            this.analysisAllTToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.T)));
            this.analysisAllTToolStripMenuItem.Size = new System.Drawing.Size(261, 22);
            this.analysisAllTToolStripMenuItem.Text = "Analysis All(T)";
            this.analysisAllTToolStripMenuItem.Click += new System.EventHandler(this.analysisAllTToolStripMenuItem_Click);
            // 
            // editEToolStripMenuItem
            // 
            this.editEToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.copyImageCToolStripMenuItem});
            this.editEToolStripMenuItem.Name = "editEToolStripMenuItem";
            this.editEToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.E)));
            this.editEToolStripMenuItem.Size = new System.Drawing.Size(56, 20);
            this.editEToolStripMenuItem.Text = "Edit(E)";
            // 
            // copyImageCToolStripMenuItem
            // 
            this.copyImageCToolStripMenuItem.Name = "copyImageCToolStripMenuItem";
            this.copyImageCToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.C)));
            this.copyImageCToolStripMenuItem.Size = new System.Drawing.Size(200, 22);
            this.copyImageCToolStripMenuItem.Text = "Copy Image(C)";
            // 
            // helpHToolStripMenuItem
            // 
            this.helpHToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.userHelpVToolStripMenuItem,
            this.aboutAutoProfilingToolAToolStripMenuItem,
            this.lisenceLToolStripMenuItem});
            this.helpHToolStripMenuItem.Name = "helpHToolStripMenuItem";
            this.helpHToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.H)));
            this.helpHToolStripMenuItem.Size = new System.Drawing.Size(63, 20);
            this.helpHToolStripMenuItem.Text = "Help(H)";
            // 
            // userHelpVToolStripMenuItem
            // 
            this.userHelpVToolStripMenuItem.Name = "userHelpVToolStripMenuItem";
            this.userHelpVToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.V)));
            this.userHelpVToolStripMenuItem.Size = new System.Drawing.Size(278, 22);
            this.userHelpVToolStripMenuItem.Text = "User Help(V)";
            // 
            // aboutAutoProfilingToolAToolStripMenuItem
            // 
            this.aboutAutoProfilingToolAToolStripMenuItem.Name = "aboutAutoProfilingToolAToolStripMenuItem";
            this.aboutAutoProfilingToolAToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.A)));
            this.aboutAutoProfilingToolAToolStripMenuItem.Size = new System.Drawing.Size(278, 22);
            this.aboutAutoProfilingToolAToolStripMenuItem.Text = "About Auto-Profiling Tool(A)";
            // 
            // lisenceLToolStripMenuItem
            // 
            this.lisenceLToolStripMenuItem.Name = "lisenceLToolStripMenuItem";
            this.lisenceLToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.L)));
            this.lisenceLToolStripMenuItem.Size = new System.Drawing.Size(278, 22);
            this.lisenceLToolStripMenuItem.Text = "Lisence(L)";
            // 
            // allCharactorAndEstimateToolStripMenuItem
            // 
            this.allCharactorAndEstimateToolStripMenuItem.Name = "allCharactorAndEstimateToolStripMenuItem";
            this.allCharactorAndEstimateToolStripMenuItem.ShortcutKeys = ((System.Windows.Forms.Keys)((System.Windows.Forms.Keys.Alt | System.Windows.Forms.Keys.B)));
            this.allCharactorAndEstimateToolStripMenuItem.Size = new System.Drawing.Size(267, 22);
            this.allCharactorAndEstimateToolStripMenuItem.Text = "All Charactor and Estimate";
            this.allCharactorAndEstimateToolStripMenuItem.Click += new System.EventHandler(this.allCharactorAndEstimateToolStripMenuItem_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 581);
            this.Controls.Add(this.menuStrip1);
            this.ForeColor = System.Drawing.SystemColors.ActiveCaptionText;
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Auto-Profling Tool For Cloud Gaming";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileFToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem runGameRToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem analysisAToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem editEToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem helpHToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem copyImageCToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem userHelpVToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutAutoProfilingToolAToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem lisenceLToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem analysisWindowSizeWToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem analysisAllTToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem allCharactorAndEstimateToolStripMenuItem;
    }
}


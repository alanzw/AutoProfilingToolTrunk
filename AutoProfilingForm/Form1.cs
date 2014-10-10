using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace AutoProfilingForm
{
    public partial class Form1 : Form
    {
        
        public Form1()
        {
            InitializeComponent();
        }

        private void runGameRToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MdiChildFoRunGame frmChidChildForRunGame = MdiChildFoRunGame.GetForm();
            frmChidChildForRunGame.MdiParent = this;
            frmChidChildForRunGame.WindowState = FormWindowState.Maximized;
            frmChidChildForRunGame.Show();
        }

        private void analysisAToolStripMenuItem_Click(object sender, EventArgs e)
        {
           
        }

        private void analysisWindowSizeWToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MdiChildForAnalysis frmChildForAnalysis = MdiChildForAnalysis.GetForm();
            frmChildForAnalysis.MdiParent = this;
            frmChildForAnalysis.WindowState = FormWindowState.Maximized;
            frmChildForAnalysis.Show();
        }

        private void analysisAllTToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MdiChildForAnalysisAll frmChildForAnalysisAll = MdiChildForAnalysisAll.GetForm();
            frmChildForAnalysisAll.MdiParent = this;
            frmChildForAnalysisAll.WindowState = FormWindowState.Maximized;
            frmChildForAnalysisAll.Show();
        }

        private void allCharactorAndEstimateToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MdiChildForAllAndEstimate frmChildForAllCharactor = MdiChildForAllAndEstimate.GetForm();
            frmChildForAllCharactor.MdiParent = this;
            frmChildForAllCharactor.WindowState = FormWindowState.Maximized;
            frmChildForAllCharactor.Show();
        }
    }
}

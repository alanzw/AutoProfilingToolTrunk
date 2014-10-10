using System;
using System.Collections.Generic;
using System.Collections;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO;
using ConsoleControl;

namespace AutoProfilingForm
{
    public partial class MdiChildFoRunGame : Form
    {
        private static MdiChildFoRunGame _frmForRunGame = null;
        public static MdiChildFoRunGame GetForm()
        {
            if (_frmForRunGame == null)
            {
                _frmForRunGame = new MdiChildFoRunGame();
            }
            return _frmForRunGame;
        }
        private MdiChildFoRunGame()
        {
            InitializeComponent();
        }
        /// <summary>
        /// the load function for run game form
        /// </summary>
        /// <param name="sender">the object</param>
        /// <param name="e">the event args</param>
        private void MdiChildFoRunGame_Load(object sender, EventArgs e)
        {
            // to correct the layout

        }

        private void MdiChildFoRunGame_FormClosing(Object sender, FormClosingEventArgs e)
        {
            _frmForRunGame.Close();
            _frmForRunGame = null;
        }

        private void Dispose()
        {
            Console.WriteLine("Form For Run Game Dispose!");
            Dispose(true);
            _frmForRunGame = null;
        }
        public void Close()
        {
            Dispose();
        }
        ~MdiChildFoRunGame()
        {
            Dispose(true);
        }


        private FolderBrowserDialog gameFolderDialog = null;
        private FolderBrowserDialog saveFolderDialog = null;
        private OpenFileDialog gameFileDialog = null;
        
        // to select the game
        private void buttonChooseGameDirectory_Click(object sender, EventArgs e)
        {
            //gameFolderDialog = new FolderBrowserDialog();
            //DialogResult dResult = gameFolderDialog.ShowDialog();
            gameFileDialog = new OpenFileDialog();
            DialogResult dResult = gameFileDialog.ShowDialog();

            if (dResult == DialogResult.OK)
            {
                //this.textBoxGameDirectory.Text = gameFolderDialog.SelectedPath;
                this.textBoxGameName.Text = gameFileDialog.FileName;
            }
        }

        // to select a folder to save the result
        private void buttonSaveResultDirectory_Click(object sender, EventArgs e)
        {
            saveFolderDialog = new FolderBrowserDialog();
            saveFolderDialog.ShowNewFolderButton = true;
            DialogResult dResult = saveFolderDialog.ShowDialog();
            if (dResult == DialogResult.OK)
            {
                this.textBoxSaveDirectory.Text = saveFolderDialog.SelectedPath;
            }
        }
        // the log function to log the normal information, text color is white
        private void logInfo(string str)
        {
            logInfo(str, Color.White);
        }
        // the log function to log the normal information, use the specific color
        private void logInfo(string str, Color color)
        {
            consoleControl1.WriteOutput("[info]: " + str, color);
        }

        // the log function to log the error information, text color is red
        private void logError(string err)
        {
            consoleControl1.WriteOutput("[error]: "+ err, Color.Red);
        }
        // the log function to log the wraning information, text color is Blue
        private void logWarning(string warning)
        {
            consoleControl1.WriteOutput("[warning]: "+ warning, Color.Blue);
        }

        private void logInfoLine(string str)
        {
            logInfo(str + "\n");
        }
        private void logErrorLine(string err)
        {
            logError(err + "\n");
        }
        private void logWarningLine(string warning)
        {
            logWarning(warning + "\n");
        }

        // to detect whether the dll file is exist in the game folder
        private bool checkDllExistAndMove(string dll, string folder)
        {
            DirectoryInfo info = new DirectoryInfo(folder);
            FileInfo[] fileInfos = info.GetFiles(dll);
            if (fileInfos.Length > 0)
            {
                logErrorLine("dll file '" + dll + "' exist in folder '" + folder+"'"); 
            }
            else
            {
                // move the dll file to the folder 
                File.Copy(dll, folder + "\\" + dll);
                logErrorLine("copy file '" + dll + "' to folder '" + folder+"'");
            }

            return false;
        }
        
        private bool run = false;
        private void toRun()
        {
            if (run == false)
            {
                this.buttonRun.Text = "stop";
                run = true;
                //set all to unchangable
                this.textBoxSetName.Enabled = false;
                this.textBoxSingleSetName.Enabled = false;
                this.textBoxGameName.Enabled = false;
                this.textBoxSaveDirectory.Enabled = false;
                this.buttonSaveResultDirectory.Enabled = false;
                this.buttonSetFileName.Enabled = false;
                this.buttonChooseGameDirectory.Enabled = false;
                this.button4.Enabled = false;
                this.comboBoxDllToUse.Enabled = false;

                this.radioButtonAll.Enabled = false;
                this.radioButtonSimple.Enabled = false;
                checkBoxLimitFps.Enabled = false;

                //check the configuration
                if (this.gameFileDialog == null && String.IsNullOrEmpty(this.textBoxGameName.Text))
                {
                    // error
                    logErrorLine("game folder is NULL.");
                    return;
                }
                if (gameFileDialog != null)
                {
                    logWarningLine("game name: " + gameFileDialog.FileName);
                }
                else if (!String.IsNullOrEmpty(textBoxGameName.Text))
                {
                    logWarningLine("game name: " + textBoxGameName.Text);
                }
                else
                {
                    logErrorLine("NULL Game Name.");
                    return;
                }

                if (this.saveFolderDialog == null && String.IsNullOrEmpty(this.textBoxSaveDirectory.Text))
                {
                    // save to defualt directory
                    logErrorLine("folder to save the result is NULL.");
                    return;
                }
                if (saveFolderDialog != null)
                {
                    logWarningLine("save folder: " + saveFolderDialog.SelectedPath);
                }
                else if (!String.IsNullOrEmpty(textBoxSaveDirectory.Text))
                {
                    logWarningLine("save folder: " + textBoxSaveDirectory.Text);
                }
                else
                {
                    logErrorLine("NULL Save Folder.");
                    return;
                }

                /*
                                if (String.IsNullOrEmpty(this.textBoxSetName.Text))
                                {
                                    logErrorLine("set file name is NULL.");
                                }
                 * */

                if (String.IsNullOrEmpty(this.textBoxSingleSetName.Text))
                {
                    logErrorLine("single set file name is NULL.");
                    return;
                }
                logWarningLine("single set name: " + textBoxSingleSetName.Text);

                // output to console.
                logWarningLine("run the game with dll: " + comboBoxDllToUse.GetItemText(comboBoxDllToUse.SelectedItem));

                //  Start the proces. call AutoProfilingTool.exe, the arguments need to be formed


                // format the arguments
                string arguments = null;
                arguments = " -D " + comboBoxDllToUse.Text;
                if (checkBoxFps.Checked == true)
                {
                    arguments += " -F 24 ";
                }
                arguments += " -G " + textBoxGameName.Text;


                if (this.saveFolderDialog != null)
                {
                    // save to defualt directory
                    arguments += " -P " + saveFolderDialog.SelectedPath;
                }
                else if (!String.IsNullOrEmpty(this.textBoxSaveDirectory.Text))
                {
                    arguments += " -P " + textBoxSaveDirectory.Text;
                }
                else
                {

                }
                if (!String.IsNullOrEmpty(this.textBoxSingleSetName.Text))
                {
                    arguments += " -O " + textBoxSingleSetName.Text;
                }
                logErrorLine("Game file '" + textBoxGameName.Text + "' is in folder '" + Path.GetDirectoryName(textBoxGameName.Text) + "'");
                checkDllExistAndMove(comboBoxDllToUse.Text, Path.GetDirectoryName(textBoxGameName.Text));

                logInfoLine("cmd line: " + "AutoProfilingTool.exe" + arguments);


                consoleControl1.StartProcess("AutoProfilingTool.exe", arguments);

                //  Update the UI state.
                //UpdateUIState();
            }
            else
            {
                run = false;
                this.buttonRun.Text = "run";
                this.textBoxSetName.Enabled = true;
                this.textBoxSingleSetName.Enabled = true;
                this.textBoxGameName.Enabled = true;
                this.textBoxSaveDirectory.Enabled = true;
                this.buttonSaveResultDirectory.Enabled = true;
                this.buttonSetFileName.Enabled = true;
                this.buttonChooseGameDirectory.Enabled = true;
                this.button4.Enabled = true;
                this.comboBoxDllToUse.Enabled = true;

                this.radioButtonAll.Enabled = true;
                this.radioButtonSimple.Enabled = true;
                checkBoxLimitFps.Enabled = true;

                consoleControl1.StopProcess();
            }
        }
        // run the game
        private void buttonRun_Click(object sender, EventArgs e)
        {
            toRun();
        }


        // get the set file name. the file name is auto generated, but you can change the name
        private void buttonSetFileName_Click(object sender, EventArgs e)
        {

        }

        // get the single set file name. the file name is auto generated, but you can change the name
        private void button4_Click(object sender, EventArgs e)
        {

        }


        // tab select
        private void tabControl1_Selected(object sender, TabControlEventArgs e)
        {
            if (e.TabPage == tabPageNode)
            {

            }
            else if (e.TabPage == tabPageMonitor)
            {

            }
            else if (e.TabPage == tabPageRunConfigure)
            {
                comboBoxDllToUse.Text = null;
                Console.WriteLine("select the run configure tab");
                if (radioButtonAll.Checked == true)
                    comboBoxDllToUse.SelectedText = "HookD3DAll.dll";
                else
                    comboBoxDllToUse.SelectedText = "HookD3D.dll";
            }
            else if (e.TabPage == tabPageGameConfigure)
            {
                // load the game data base
            }
        }


        private OpenFileDialog dbDialog = null;
        private void buttonChooseDBFile_Click(object sender, EventArgs e)
        {
            if (dbDialog == null)
            {
                dbDialog = new OpenFileDialog();
            }
            dbDialog.Filter = "Game Data Base File(*.xml)|*.xml";
            
            if (dbDialog.ShowDialog() == DialogResult.OK)
            {
                this.textBoxDBFile.Text = dbDialog.FileName;
            }
        }

        private bool show = false;
        private DataSet xmlDataSet = null;

        private void buttonSaveXml_Click(object sender, EventArgs e)
        {
            /*
            if (show == false)
            {
                this.buttonSaveXml.Text = "change";
                show = true;
            }
            else
            {
                show = false;
                this.buttonSaveXml.Text = "save";
            }
             */
            if (xmlDataSet == null)
            {
                xmlDataSet = new DataSet(dbDialog.FileName);
            }
            xmlDataSet.Reset();
            this.buttonSaveXmlDataSet.Enabled = false;
            xmlDataSet.ReadXml(dbDialog.FileName);
            this.dataGridView1.DataSource = xmlDataSet.Tables[0];
            //this.dataGridView1.DataBind();
        }
        private void updateDataSet(string gameName, string gameFolder)
        {
            try
            {
                string strFilter = "GameName=" + gameName;
                DataRow[] rows = xmlDataSet.Tables[0].Select(strFilter);
                if (rows.Length > 0)
                {
                    // update

                }

            }
            catch (Exception)
            {

            }
        }

        // insert 
        private void insertDataSet(string gameName, string gameFolder)
        {
            DataRow row = xmlDataSet.Tables[0].NewRow();
            row["GameName"] = gameName;
            row["GameDirectory"] = gameFolder;
            xmlDataSet.Tables[0].Rows.Add(row);
            saveToXml();
        }

        // save to the xml file
        private bool saveToXml()
        {
            xmlDataSet.WriteXml(dbDialog.FileName, XmlWriteMode.IgnoreSchema);
            return true;
        }

        private void dataGridView1_UserAddedRow(object sender, DataGridViewRowEventArgs e)
        {
            logWarningLine("add new row");
            saveToXml();
        }

        private void dataGridView1_UserDeletedRow(object sender, DataGridViewRowEventArgs e)
        {
            logWarningLine("delete new row");
            saveToXml();
        }

        // click the row header
        private void dataGridView1_RowHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                // right click, popup the right menu
                ToolStripItem addColumnItem = null;
                ToolStripItem deleteColumnItem = null;
                ToolStripItem deleteRowItem = null;
                ToolStripItem runItem = null;

                addColumnItem = contextMenuStripForDataGrid.Items[0];
                deleteColumnItem = contextMenuStripForDataGrid.Items[1];
                deleteRowItem = contextMenuStripForDataGrid.Items[2];
                runItem = contextMenuStripForDataGrid.Items[3];
                addColumnItem.Enabled = false;
                deleteColumnItem.Enabled = false;
                deleteRowItem.Enabled = true;
                runItem.Enabled = true;
                contextMenuStripForDataGrid.Show(MousePosition.X, MousePosition.Y);

                rowSelectedIndex = e.RowIndex;
            }
            else if (e.Button == MouseButtons.Left)
            {
                // select the row
                rowSelectedIndex = e.RowIndex;
            }
        }

        private int columnSelectedIndex = -1;
        private int rowSelectedIndex = -1;

        // click the column header
        private void dataGridView1_ColumnHeaderMouseClick(object sender, DataGridViewCellMouseEventArgs e)
        {
            if (e.Button == MouseButtons.Right)
            {
                // right click, popup right menu
                ToolStripItem addColumnItem = null;
                ToolStripItem deleteColumnItem = null;
                ToolStripItem deleteRowItem = null;
                ToolStripItem runItem = null;

                addColumnItem = contextMenuStripForDataGrid.Items[0];
                deleteColumnItem = contextMenuStripForDataGrid.Items[1];
                deleteRowItem = contextMenuStripForDataGrid.Items[2];
                runItem = contextMenuStripForDataGrid.Items[3];
                addColumnItem.Enabled = true;
                deleteColumnItem.Enabled = true;
                deleteRowItem.Enabled = false;
                runItem.Enabled = false;
                contextMenuStripForDataGrid.Show(MousePosition.X, MousePosition.Y);

                columnSelectedIndex = e.ColumnIndex;

            }
            else if (e.Button == MouseButtons.Left)
            {
                // left click
            }
        }

        private void addColumnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // to add a new column
            DataGridViewColumn newC = new DataGridViewColumn(new DataGridViewTextBoxCell());
            newC.DataPropertyName = null;
            newC.HeaderText = "new";
            DataGridViewCellStyle cstype = new DataGridViewCellStyle();
            newC.DefaultCellStyle = cstype;
            //newC.CellType = 
            dataGridView1.Columns.Add(newC);

            newC.Selected = true;
            
            
            
        }

        private void deleteColumnToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // delete the selected column
            dataGridView1.Columns.RemoveAt(columnSelectedIndex);
            this.buttonSaveXmlDataSet.Enabled = true;
        }

        private void deleteRowToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // delete the row
            dataGridView1.Rows.RemoveAt(rowSelectedIndex);
            this.buttonSaveXmlDataSet.Enabled = true;
        }


        private void dataSetRowChanged()
        {

        }

        // cell content is changed
        private void dataGridView1_CellEndEdit(object sender, DataGridViewCellEventArgs e)
        {
            
            {

            }
        }

        // to change the column header
        private void dataGridView1_ColumnHeaderMouseDoubleClick(object sender, DataGridViewCellMouseEventArgs e)
        {

        }

        private void buttonSaveXmlDataSet_Click(object sender, EventArgs e)
        {
            xmlDataSet.WriteXml(dbDialog.FileName);
        }

        // to the the game with selected row
        private void toRunToolStripMenuItem_Click(object sender, EventArgs e)
        {
            // start the process with dll and other stuff
            // load all the information to interface
            loadConfigure();
            toRun();
            //startGenerate();
        }


        private void writeArffHeader(StreamWriter sw)
        {
            // write the arff file header
            sw.WriteLine("% ARFF file for the game charactor with 24 features");
            sw.WriteLine("@relation charactor");

            sw.WriteLine("@attribute index real");
            sw.WriteLine("@attribute curFps real");
            sw.WriteLine("@attribute cpuUsage real");
            sw.WriteLine("@attribute gpuUsage real");
            sw.WriteLine("@attribute cmdCount real");
            sw.WriteLine("@attribute parameterDataSize real");
            sw.WriteLine("@attribute parameterDataToRemote real");
            sw.WriteLine("@attribute objCount real");
            sw.WriteLine("@attribute dataSize real");
            sw.WriteLine("@attribute triangleCount real");
            sw.WriteLine("@attribute drawTimes real");
            sw.WriteLine("@attribute ibLockCount real");
            sw.WriteLine("@attribute ibSize real");
            sw.WriteLine("@attribute vbLockCount real");
            sw.WriteLine("@attribute vbSize real");
            sw.WriteLine("@attribute surfaceLockCount real");
            sw.WriteLine("@attribute surfadeSize real");
            sw.WriteLine("@attribute texLockCount real");
            sw.WriteLine("@attribute textSize real");
            sw.WriteLine("@attribute setTex real");
            sw.WriteLine("@attribute stateBlockCount real");
            sw.WriteLine("@attribute vertexShaderCmdCount real");
            sw.WriteLine("@attribute vertexShaderConst real");
            sw.WriteLine("@attribute pixelShaderCmdConst real");
            sw.WriteLine("@attribute pixelShaderConst real");

            sw.WriteLine("@attribute gameIndex real");

            sw.WriteLine("@data");
        }


        // load the configuration to run 
        string gameFullPath = null;
        string saveDirectory = null;
        string singleSetFileName = null;
        string useDll = null;

        private void loadConfigure()
        {
            // load all the configuration to the table
            Console.WriteLine("Game Name: " + dataGridView1.Rows[rowSelectedIndex].Cells["GameName"].Value.ToString());
            Console.WriteLine("Game direictory: " + dataGridView1.Rows[rowSelectedIndex].Cells["GameDirectory"].Value.ToString());
            Console.WriteLine("Save Result direictory: " + dataGridView1.Rows[rowSelectedIndex].Cells["SaveResultDirectory"].Value.ToString());
            Console.WriteLine("Single set file Name: " + dataGridView1.Rows[rowSelectedIndex].Cells["SingleSetFileName"].Value.ToString());
            Console.WriteLine("Use Dll: " + dataGridView1.Rows[rowSelectedIndex].Cells["UseDll"].Value.ToString());

            gameFullPath = dataGridView1.Rows[rowSelectedIndex].Cells["GameDirectory"].Value.ToString() + "\\" + dataGridView1.Rows[rowSelectedIndex].Cells["GameName"].Value.ToString();
            saveDirectory = dataGridView1.Rows[rowSelectedIndex].Cells["SaveResultDirectory"].Value.ToString();
            singleSetFileName = dataGridView1.Rows[rowSelectedIndex].Cells["SingleSetFileName"].Value.ToString();
            useDll = dataGridView1.Rows[rowSelectedIndex].Cells["UseDll"].Value.ToString();

            textBoxGameName.Text = gameFullPath;
            textBoxSaveDirectory.Text = saveDirectory;
            textBoxSingleSetName.Text = singleSetFileName;
            comboBoxDllToUse.Text = null;
            comboBoxDllToUse.SelectedText = useDll;
            //xmlDataSet.Tables[0].Rows[rowSelectedIndex];
        }

        private void startGenerate()
        {
            if (charactorFileFolder == null || wekaFile == null)
            {
                // indicate that the user did not specific the input and the output, popup a window to warning
                MessageBox.Show("None input or ouput specified");
                return;
            }
            // get all the input file listed in the list box, read and write, we do not change anything but add a new charactor
            FileStream fs = null;
            string fullPath = charactorFileFolder.SelectedPath + "\\";

            // open the result file
            FileStream ofs = (FileStream)wekaFile.OpenFile();
            StreamWriter sw = new StreamWriter(ofs);

            // generate the arff file or the csv file.
            if (wekaFile.FileName.Contains(".arff"))
            {

                writeArffHeader(sw);
                
                // foreach .single.log file
                int fileIndex = 0;
                foreach (string obj in listBoxSelectedFiles.Items)
                {

                    fs = new FileStream(fullPath + obj, FileMode.Open);
                    StreamReader sr = new StreamReader(fs);
                    if (fs == null || sr == null)
                    {
                        MessageBox.Show("Open input file: " + obj + " fialed.");
                        consoleControlConfig.WriteOutput("Open input file: " + obj + "failed.\n", Color.Red);
                        return;
                    }

                    Console.WriteLine(fullPath + obj);
                    string line = null;
                    if (this.radioButtonKeepOriginal.Checked == true)
                    {
                        while (!sr.EndOfStream)
                        {
                            line = sr.ReadLine();
                            Console.WriteLine(line);
                            sw.WriteLine(line + " " + fileIndex);
                            consoleControlConfig.WriteOutput(line, Color.Green);
                        }
                    }
                    else if (this.radioButtonDiscretization.Checked == true)
                    {

                        // discretization the cpu and gpu usage
                        while (!sr.EndOfStream)
                        {
                            line = sr.ReadLine();
                            Console.WriteLine(line);


                            string[] input = line.Split(" ".ToArray());
                            // cpu
                            int cpuStepCount = Int32.Parse(input[2]) / Int32.Parse(textBoxCpuWindow.Text);
                            int gpuStepCount = Int32.Parse(input[3]) / Int32.Parse(textBoxGpuWindow.Text);

                            if (cpuStepCount < minCpuStepCount)
                            {
                                minCpuStepCount = cpuStepCount;
                            }
                            if (cpuStepCount > maxCpuStepCount)
                            {
                                maxCpuStepCount = cpuStepCount;
                            }
                            // gpu
                            if (gpuStepCount < minGpuStepCount)
                            {
                                minGpuStepCount = gpuStepCount;
                            }
                            if (gpuStepCount > maxGpuStepCount)
                            {
                                maxGpuStepCount = gpuStepCount;
                            }

                            // format the output string, like gpu,cpu,fps....

                            sw.Write(input[0] + " ");
                            sw.Write(input[1] + " ");
                            sw.Write(textBoxCpuLabel.Text + cpuStepCount + ",");
                            sw.Write(textBoxGpuLabel.Text + cpuStepCount + ",");
                            for (int i = 4; i < input.Length; i++)
                            {

                                sw.Write(input[i] + " ");
                            }

                            sw.WriteLine(line + " " + fileIndex);
                            consoleControlConfig.WriteOutput(line, Color.Green);
                        }
                    }
                    sr.Close();
                    sw.Flush();

                    fileIndex++;
                }
            }
            else if (wekaFile.FileName.Contains(".csv"))
            {

                // foreach .single.log file
                int fileIndex = 0;
                foreach (string obj in listBoxSelectedFiles.Items)
                {

                    fs = new FileStream(fullPath + obj, FileMode.Open);
                    StreamReader sr = new StreamReader(fs);
                    if (fs == null || sr == null)
                    {
                        MessageBox.Show("Open input file: " + obj + " fialed.");
                        consoleControlConfig.WriteOutput("Open input file: " + obj + "failed.\n", Color.Red);
                        return;
                    }

                    Console.WriteLine(fullPath + obj);
                    string line = null;
                    if (this.radioButtonKeepOriginal.Checked == true)
                    {
                        while (!sr.EndOfStream)
                        {
                            line = sr.ReadLine();
                            Console.WriteLine(line);
                            line.Replace(" ", ",");
                            sw.WriteLine(line + "," + fileIndex);
                            consoleControlConfig.WriteOutput(line, Color.Green);
                        }
                    }
                    else if (this.radioButtonDiscretization.Checked == true)
                    {

                        // discretization the cpu and gpu usage
                        while (!sr.EndOfStream)
                        {
                            line = sr.ReadLine();
                            Console.WriteLine(line);

                            string[] input = line.Split(" ".ToArray());
                            // cpu
                            int cpuStepCount = Int32.Parse(input[2])/Int32.Parse(textBoxCpuWindow.Text);
                            int gpuStepCount = Int32.Parse(input[3])/Int32.Parse(textBoxGpuWindow.Text);

                            if (cpuStepCount < minCpuStepCount)
                            {
                                minCpuStepCount = cpuStepCount;
                            }
                            if(cpuStepCount > maxCpuStepCount){
                                maxCpuStepCount = cpuStepCount;
                            }
                            // gpu
                            if (gpuStepCount < minGpuStepCount)
                            {
                                minGpuStepCount = gpuStepCount;
                            }
                            if(gpuStepCount > maxGpuStepCount){
                                maxGpuStepCount = gpuStepCount;
                            }
                            
                            // format the output string, like gpu,cpu,fps....

                            sw.Write(input[0] +",");
                            sw.Write(input[1] +",");
                            sw.Write(textBoxCpuLabel.Text + cpuStepCount+",");
                            sw.Write(textBoxGpuLabel.Text + cpuStepCount + ",");
                            for (int i = 4; i < input.Length; i++)
                            {

                                sw.Write(input[i] + ",");
                            }


                            sw.WriteLine("," + fileIndex);
                            consoleControlConfig.WriteOutput(line, Color.Green);
                        }
                    }
                    sr.Close();
                    sw.Flush();

                    fileIndex++;
                }
            }

            ofs.Flush();
            ofs.Close();

            textBoxCpuStepCount.Text = (maxCpuStepCount - minCpuStepCount).ToString();
            textBoxGpuStepCount.Text = (maxGpuStepCount - minGpuStepCount).ToString();
            
        }

        private int maxCpuStepCount = 0;
        private int minCpuStepCount = 100;
        private int minGpuStepCount = 100;
        private int maxGpuStepCount = 0;


        private void loadConfigureToRunToolStripMenuItem_Click(object sender, EventArgs e)
        {
            loadConfigure();
        }

        // start the procedure, generate the input file for weka
        private void buttonStartGenerate_Click(object sender, EventArgs e)
        {
            startGenerate();
        }


        // select the folder that contains all the input file
        private FolderBrowserDialog charactorFileFolder = null;
        private string[] allCharactorFiles = null;
        private void buttonChooseCharactorFile_Click(object sender, EventArgs e)
        {
            if (charactorFileFolder == null)
            {
                charactorFileFolder = new FolderBrowserDialog();
                charactorFileFolder.ShowNewFolderButton = true;
            }
            
            if (DialogResult.OK == charactorFileFolder.ShowDialog())
            {
                textBoxCharactorFileFolder.Text = charactorFileFolder.SelectedPath;
            }
            // find all the *.single.set file and show in the listBoxAllFiles
            ArrayList fileList = new ArrayList();
            //string filter = "*.single.log";
            string filter = comboBoxCharactorFileFilter.Text;
            Console.WriteLine("Use Filter: "+ filter);
            if (charactorFileFolder.SelectedPath != "" && charactorFileFolder.SelectedPath != null)
            {
                allCharactorFiles = Directory.GetFiles(charactorFileFolder.SelectedPath, filter);
                foreach (string file in allCharactorFiles)
                {
                    listBoxAllFiles.Items.Add(file.Substring(charactorFileFolder.SelectedPath.Length + 1));
                }
            }
        }

        // to save the file which is the input of WEKA
        private SaveFileDialog wekaFile = null;
        private void buttonSaveWeka_Click(object sender, EventArgs e)
        {
            if (wekaFile == null)
            {
                wekaFile = new SaveFileDialog();
                wekaFile.Filter = "CSV File(*.csv)|*.csv|Weka input file(*.arff)|*.arff";
                wekaFile.RestoreDirectory = true;
                wekaFile.CheckFileExists = true;
            }

            if (wekaFile.ShowDialog() == DialogResult.OK)
            {
                textBoxSaveWekaFile.Text = wekaFile.FileName;
                //if(wekaFile.CheckFileExists)
            }
            else
            {
                //canceled
                MessageBox.Show("You may need to specific the save filed.");
            }
        }

        // move all the files listed in the box to the right side which means selected
        private void buttonSelectAll_Click(object sender, EventArgs e)
        {
            //Object item = null;
            ArrayList arrayRight = new ArrayList();
            foreach(Object item in listBoxAllFiles.Items){
                arrayRight.Add(item);
                
            }
            foreach (Object item in arrayRight)
            {
                listBoxAllFiles.Items.Remove(item);
                listBoxSelectedFiles.Items.Add(item);
            }
        }

        // unselect all the files in the right box

        private void buttonUnselectAll_Click(object sender, EventArgs e)
        {
            ArrayList arrayRight = new ArrayList();
            foreach (Object item in listBoxSelectedFiles.Items)
            {
                arrayRight.Add(item); ;
            }
            foreach (Object item in arrayRight)
            {
                listBoxSelectedFiles.Items.Remove(item);
                listBoxAllFiles.Items.Add(item);
            }
        }

        // select the selected file
        private void buttonSelectOne_Click(object sender, EventArgs e)
        {
            Object item = null;
            item = listBoxAllFiles.SelectedItem;
            if (item != null)
            {
                listBoxAllFiles.Items.Remove(item);
                listBoxSelectedFiles.Items.Add(item);
            }
        }

        // unselect the selected file in the right side
        private void buttonUnselectOne_Click(object sender, EventArgs e)
        {
            Object item = null;
            item = listBoxSelectedFiles.SelectedItem;
            if (item == null) return;
            listBoxSelectedFiles.Items.Remove(item);
            listBoxAllFiles.Items.Add(item);
        }

        private void tabPageGameConfigure_Click(object sender, EventArgs e)
        {

        }

        private void radioButtonSimple_CheckedChanged(object sender, EventArgs e)
        {
            if(radioButtonSimple.Checked == true){
                // use the HookD3D.dll
                //comboBoxDllToUse.SelectedIndex = 1;
                comboBoxDllToUse.Refresh();
                comboBoxDllToUse.Text = null;
                comboBoxDllToUse.SelectedText = "HookD3D.dll";
            }
        }

        private void radioButtonAll_CheckedChanged(object sender, EventArgs e)
        {
            if (radioButtonAll.Checked == true)
            {
                // use the HookD3DAll.dll
                //comboBoxDllToUse.SelectedIndex = 2;
                comboBoxDllToUse.Refresh();
                comboBoxDllToUse.Text = null;
                comboBoxDllToUse.SelectedText = "HookD3DAll.dll";
            }
        }

        private void checkBoxLimitFps_CheckedChanged(object sender, EventArgs e)
        {

        }
    }

}

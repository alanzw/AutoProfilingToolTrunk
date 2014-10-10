using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ChartDirector;
using System.Collections;
using System.IO;

namespace AutoProfilingForm
{
    public partial class MdiChildForAnalysis : Form
    {
        private static MdiChildForAnalysis _frmForAnalysis = null;
        public static MdiChildForAnalysis GetForm()
        {
            if (_frmForAnalysis == null)
            {
                _frmForAnalysis = new MdiChildForAnalysis();
            }
            return _frmForAnalysis;
        }

        private MdiChildForAnalysis()
        {
            InitializeComponent();
        }

        private void MdiChidForAnalysis_FormClosing(Object sender, FormClosingEventArgs e)
        {
            _frmForAnalysis.Close();
            _frmForAnalysis = null;
        }
        private void Dispose()
        {
            Dispose(true);
            _frmForAnalysis = null;
        }
        public void Close()
        {
            Dispose();
        }
        ~MdiChildForAnalysis()
        {
            Dispose(true);
        }

        private void label6_Click(object sender, EventArgs e)
        {

        }
        /// <summary>
        /// the load function for loading the form for analyze
        /// 
        /// </summary>
        /// <param name="sender">the object</param>
        /// <param name="e">the event args</param>
        private void MdiChildForAnalysis_Load(object sender, EventArgs e)
        {
            // correct the layout
            this.radioButton2.Checked = true;

            this.showFps = true;
            this.showCpu = true;
            this.showGpu = true;

            this.checkBoxShowCpu.Checked = true;
            this.checkBoxShowGpu.Checked = true;
            this.checkBoxShowFps.Checked = true;

        }

        private OpenFileDialog setOfDialog = null;
        private OpenFileDialog singleOfDialog = null;
        private bool useSet = false;
        private bool useSingle = false;

        private bool showCpu = false;
        private bool showGpu = false;
        private bool showFps = false;
        
         
        // open the input set file, is some *.set
        private void buttonChooseInputSet_Click(object sender, EventArgs e)
        {
            setOfDialog = new OpenFileDialog();
            setOfDialog.Filter = "Set Input File(*.set)|*.set";
            DialogResult setOfFlag = setOfDialog.ShowDialog();
            if (setOfFlag == DialogResult.OK)
            {
                this.textBoxInpuSet.Text = setOfDialog.FileName;
                useSet = true;   // the input file is a .set file
            }
        }

        // open the single input file, is some *.single.set

        private void buttonChooseSingleInput_Click(object sender, EventArgs e)
        {

            singleOfDialog = new OpenFileDialog();
            singleOfDialog.Filter = "Single Input File(*.single.set)|*.single.set|Frame Input(*.frame.log)|*.frame.log|Second Input(*.second.log)|*.second.log|All(*.*)|*.*";
            DialogResult singleOfFlag = singleOfDialog.ShowDialog();
            if (singleOfFlag == DialogResult.OK)
            {
                this.textBoxSingleInput.Text = singleOfDialog.FileName;
            }
            useSingle = true; // the input is a .log or a .single.set file
        }

        private short gameCount = 0;

        private bool frameInput = false;
        private bool secondInput = false;

        private void dealSet()
        {
            // read the setOfDialog
            StreamReader sr = File.OpenText(setOfDialog.FileName);
            if (sr == null)
            {
                Console.WriteLine("null stream reader, open set " + setOfDialog.FileName + " failed.");
            }
            string line = null;
            int lineIndex = 0;
            short allLines = 0;
            while (sr.ReadLine() != null)
            {
                // add to the combo box
                allLines++;
            }

            // store the game count
            gameCount = allLines;
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            this.comboBoxShowOption.Items.Add("1");
            this.comboBoxShowOption.Items.Add("2");

        }

        private void dealSingle()
        {
            // read the singleOfDialog
            StreamReader sr = File.OpenText(singleOfDialog.FileName);


            // check the file format, whether it is a .set, .frame.log or a .second.log

            if (singleOfDialog.FileName.Contains("set"))
            {


                if (sr == null)
                {
                    Console.WriteLine("null stream reader, open single set " + singleOfDialog.FileName + " failed.");
                }
                string line = null;
                short allLines = 0;
                while (sr.ReadLine() != null)
                {
                    allLines++;
                }

                sr.BaseStream.Seek(0, SeekOrigin.Begin);

                if (allLines > 2)
                {
                    // error, should not over 2 lines
                }
                // deal the 
                if (allLines == 1)
                {
                    // just frame or second, may be it is just second, get the file name, and wo can know.
                    string t_fileName = sr.ReadLine();
                    if (t_fileName.Contains("second"))
                    {
                        // just show the second data
                        secondInput = true;
                        ReadSecondFile(t_fileName);
                    }
                    else if (t_fileName.Contains("frame"))
                    {
                        // just show the frame data
                        frameInput = true;
                        ReadFrameFile(t_fileName);
                    }
                }
                else
                {
                    // frame and second all here
                    // get the file names
                    while ((line = sr.ReadLine()) != null)
                    {
                        if (line.Contains("second"))
                        {
                            // load the second data
                            secondInput = true;
                            ReadSecondFile(line);
                        }
                        else if (line.Contains("frame"))
                        {
                            // load the frame data
                            frameInput = true;
                            ReadFrameFile(line);
                        }
                    }
                }
            }
            else if (singleOfDialog.FileName.Contains("second"))
            {
                Console.WriteLine("use a single .second.log file ");
                secondInput = true;
                ReadSecondFile(singleOfDialog.FileName);
            }
            else if (singleOfDialog.FileName.Contains("frame"))
            {
                Console.WriteLine("use a single .frame.log file");
                frameInput = true;
                ReadFrameFile(singleOfDialog.FileName);
            }

            // 
            Console.WriteLine("to show the chart.");
            ShowChart();
            //drawChart(winChartViewer1);
        }

        private int secondLines = 0;
        private int frameLines = 0;

        private bool ReadSecondFile(string fileName)
        {
            StreamReader ssr = File.OpenText(fileName);
            string seperator = " ";
            if (ssr == null)
            {
                Console.WriteLine("Open Second file: " + fileName + " failed.");
                return false;
            }
            secondLines = 0;
            /// read all lines
            while (ssr.ReadLine() != null)
            {
                secondLines++;
            }
            // alloc the data array
            this.indexForSecond = new double[secondLines];
            this.cpuInSecond = new double[secondLines];
            this.gpuInSecond = new double[secondLines];
            this.fpsInSecond = new double[secondLines];

            ssr.BaseStream.Seek(0, SeekOrigin.Begin);
            // read data to array
            string line = null;
            int lineIndex = 0;
            while((line = ssr.ReadLine())!=null){
                string[] array;
                array = line.Split(seperator.ToArray());

                // the format is: index fps cpu gpu
                indexForSecond[lineIndex] = lineIndex;
                fpsInSecond[lineIndex] = double.Parse(array[1]);
                cpuInSecond[lineIndex] = double.Parse(array[2]);
                gpuInSecond[lineIndex] = double.Parse(array[3]);
                lineIndex++;
            }

            return true;
        }

        private bool ReadFrameFile(string fileName)
        {
            StreamReader fsr = File.OpenText(fileName);
            string seperator = " ";
            int lineIndex = 0;

            if (fsr == null)
            {
                Console.WriteLine("Open Frame file: " + fileName + " failed.");
                return false;
            }
            frameLines = 0;
            // read all lines
            while (fsr.ReadLine() != null)
            {
                frameLines++;
            }

            // alloc the data array
            this.indexForFrame = new double[frameLines];
            this.cpuInFrame = new double[frameLines];
            this.gpuInFrame = new double[frameLines];
            this.fpsInFrame = new double[frameLines];

            fsr.BaseStream.Seek(0, SeekOrigin.Begin);
            // read data to array 
            string line = null;
            while ((line = fsr.ReadLine()) != null)
            {
                string[] array;
                array = line.Split(seperator.ToArray());
                indexForFrame[lineIndex] = lineIndex;
                fpsInFrame[lineIndex] = double.Parse(array[1]);
                cpuInFrame[lineIndex] = double.Parse(array[2]);
                gpuInFrame[lineIndex] = double.Parse(array[3]);
                lineIndex++;
            }
            return true;
        }

        /// <summary>
        /// to show the chart, check the show flag and draw the chart
        /// </summary>
        private void ShowChart()
        {

            // check and show
            initChartViewer(winChartViewer1);

            // set the event handler
            winChartViewer1.MouseWheel += new MouseEventHandler(winChartViewer1_MouseWheel);

            // trigger the winPortChanged event to draw the chart
            winChartViewer1.updateViewPort(true, true);

        }
        /// <summary>
        /// init the chart viewer
        /// </summary>
        /// <param name="viewer">the instance of the viewer to init</param>
        private void initChartViewer(WinChartViewer viewer)
        {
            // set the x range
            if (showInFrame)
            {
                Console.WriteLine("data loaded in init chart viewer, index lenght: " + indexForFrame.Length);
                viewer.setFullRange("x", indexForFrame[0], indexForFrame[indexForFrame.Length - 1]);
                // init the view prot to show the latest 20% of the result

                viewer.ViewPortWidth = 0.2;
                viewer.ViewPortLeft = 1 - viewer.ViewPortWidth;

                // set the maximum zoom to 10 points
                viewer.ZoomInWidthLimit = 10.0 / indexForFrame.Length;
            }
            else
            {
                Console.WriteLine("data loaded in init chart viewer, index lenght: " + indexForSecond.Length);
                viewer.setFullRange("x", indexForSecond[0], indexForSecond[indexForSecond.Length - 1]);
                // init the view prot to show the latest 20% of the result

                viewer.ViewPortWidth = 0.2;
                viewer.ViewPortLeft = 1 - viewer.ViewPortWidth;

                // set the maximum zoom to 10 points
                viewer.ZoomInWidthLimit = 10.0 / indexForSecond.Length;
            }

            // init the set the mouse usage to "pointer" mode (drag to sroll mode)
            viewer.Dock = DockStyle.Fill;

        }
        // the scroll bar event handler
        private void hScrollBar1_ValueChanged(object sender, EventArgs e)
        {
            //if (dataLoaded)
            {
                winChartViewer1.ViewPortLeft = ((double)(hScrollBar1.Value - hScrollBar1.Minimum)) / (hScrollBar1.Maximum - hScrollBar1.Minimum);
                winChartViewer1.updateViewPort(true, false);
            }
        }
        // the ViewportChanged event handle, this event occurs if the user scrolls or zooms in or out the chart by dragging or clicking on th echart. it can also be triggered by calling WinChartViewer.updateViewPort
        private void winChartViewer1_ViewPortChanged(object sender, WinViewPortEventArgs e)
        {
            Console.WriteLine("view port changed");
            // in addition to updating the chart , we may also need to updata other controls that changeds based on the view port
            updateControls(winChartViewer1);

            // update the chart if necessary
            if (e.NeedUpdateChart)
            {
                Console.WriteLine("to draw the chart");
                drawChart(winChartViewer1);
            }

            if ((!winChartViewer1.IsInMouseMoveEvent))
            {
                trackLineLabel((XYChart)winChartViewer1.Chart, winChartViewer1.PlotAreaMouseX);
                winChartViewer1.updateDisplay();
            }
        }
        // update the control
        private void updateControls(WinChartViewer viewer)
        {
            // update the start data and end data to reflect the viewport
            hScrollBar1.Enabled = winChartViewer1.ViewPortWidth < 1;
            hScrollBar1.LargeChange = (int)Math.Ceiling(winChartViewer1.ViewPortWidth *
                (hScrollBar1.Maximum - hScrollBar1.Minimum));
            hScrollBar1.SmallChange = (int)Math.Ceiling(hScrollBar1.LargeChange * 0.1);
            hScrollBar1.Value = (int)Math.Round(winChartViewer1.ViewPortLeft *
                (hScrollBar1.Maximum - hScrollBar1.Minimum)) + hScrollBar1.Minimum;
        }


        private void drawChart(WinChartViewer viewer)
        {
            // get the start index that are visible on the chart
            double viewPortStartIndex = viewer.getValueAtViewPort("x", viewer.ViewPortLeft);
            double viewPortEndIndex = viewer.getValueAtViewPort("x", viewer.ViewPortLeft + viewer.ViewPortWidth);

            // Get the array indexes that corresponds to the visible start and end
            int startIndex = 0;
            int endIndex = 0;
            if (showInFrame)
            {
                startIndex = (int)Math.Floor(Chart.bSearch(indexForFrame, viewPortStartIndex));
                endIndex = (int)Math.Ceiling(Chart.bSearch(indexForFrame, viewPortEndIndex));
                Console.WriteLine("port start: " + viewPortStartIndex + " port end: " + viewPortEndIndex + " start: " + startIndex + " end: " + endIndex + " index length: " + indexForFrame.Length);
            }
            else
            {
                startIndex = (int)Math.Floor(Chart.bSearch(indexForSecond, viewPortStartIndex));
                endIndex = (int)Math.Ceiling(Chart.bSearch(indexForSecond, viewPortEndIndex));
                Console.WriteLine("port start: " + viewPortStartIndex + " port end: " + viewPortEndIndex + " start: " + startIndex + " end: " + endIndex + " index length: " + indexForSecond.Length);
            }

            int noOfPoints = endIndex - startIndex + 1;

            // declaration the data set
            double[] viewPortDataSeriesCpuInFrame;
            double[] viewPortDataSeriesGpuInFrame;
            double[] viewPortDataSeriesFpsInFrame;
            double[] viewPortDataSeriesFpsInSecond;
            double[] viewPortDataSeriesCpuInSecond;
            double[] viewPortDataSeriesGpuInSecond;

            double[] viewPortIndex;

            if (showInFrame)
            {
                viewPortIndex = (double[])Chart.arraySlice(indexForFrame, startIndex, noOfPoints);
                if (this.showCpu)
                {
                    viewPortDataSeriesCpuInFrame = (double[])Chart.arraySlice(cpuInFrame, startIndex, noOfPoints);
                }
                if (this.showGpu)
                {
                    viewPortDataSeriesGpuInFrame = (double[])Chart.arraySlice(gpuInFrame, startIndex, noOfPoints);
                }
                if (this.showFps)
                {
                    viewPortDataSeriesFpsInFrame = (double[])Chart.arraySlice(fpsInFrame, startIndex, noOfPoints);
                }
            }
            else
            {
                viewPortIndex = (double[])Chart.arraySlice(indexForSecond, startIndex, noOfPoints);
                if (this.showCpu)
                {
                    viewPortDataSeriesCpuInSecond = (double[])Chart.arraySlice(cpuInSecond, startIndex, noOfPoints);
                }
                if (this.showGpu)
                {
                    viewPortDataSeriesGpuInSecond = (double[])Chart.arraySlice(gpuInSecond, startIndex, noOfPoints);
                }
                if (this.showFps)
                {
                    viewPortDataSeriesFpsInSecond = (double[])Chart.arraySlice(fpsInSecond, startIndex, noOfPoints);
                }
            }

            // configure overall chart apperance
            XYChart c = new XYChart(807, 371);

            c.setPlotArea(55, 50, c.getWidth() - 80, c.getHeight() - 85, c.linearGradientColor(0, 50, 0, c.getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart.Transparent, 0xffffff, 0xfffff);

            c.setClipping();

            c.addTitle("Charactor for game", "Times New Roman Bold Italic", 10);

            // Set legend icon style to use line style icon, sized for 8pt font
            c.getLegend().setLineStyleKey();
            c.getLegend().setFontSize(8);

            //LegendBox b = c.addLegend(55, 25, false, "Arial Bold", 8);
            //b.setBackground(Chart.Transparent);
            //b.setLineStyleKey();

            // set the axis stem to transparent
            c.xAxis().setColors(Chart.Transparent);
            c.yAxis().setColors(Chart.Transparent);

            // add the y axixs title
            c.yAxis().setTitle("chractor", "Arial Bold Italic", 10);

            // add data to chart

            LineLayer layer = c.addLineLayer2();
            layer.setLineWidth(2);
            layer.setFastLineMode();

            if (this.showInFrame)
                layer.setXData(this.indexForFrame);
            else
                layer.setXData(this.indexForSecond);

            /*
            layer.addDataSet(viewPortDataSeriesCpu, 0xff3333, "CPU");
            layer.addDataSet(viewPortDataSeriesGpu, 0x008800, "GPU");
            layer.addDataSet(viewPortDataSeriesFps, 0x3333cc, "FPS");
            */
            if (this.showInFrame)
            {
                if (this.showCpu)
                    layer.addDataSet(cpuInFrame, 0xff3333, "CPU In Frame");
                if (this.showGpu)
                    layer.addDataSet(gpuInFrame, 0x008800, "GPU In Frame");
                if (this.showFps)
                {
                    layer.addDataSet(fpsInFrame, 0xcccccc, "FPS In Frame");
                }

            }
            else
            {
                if (this.showCpu)
                    layer.addDataSet(cpuInSecond, 0x33cc33, "CPU In Second");
                if (this.showGpu)
                    layer.addDataSet(gpuInSecond, 0xff8833, "GPU In Second");
                if (this.showFps)
                {
                    layer.addDataSet(fpsInSecond, 0xcccccc, "FPS In Second");
                }
            }
            
            
            // configure the axis scale and labeling
            //viewer.syncDateAxisWithViewPort("x", c.xAxis());
            viewer.syncLinearAxisWithViewPort("x", c.xAxis());
            // If all ticks are yearly aligned, then we use "yyyy" as the label format.
            //c.xAxis().setFormatCondition("align", 32);
            //c.xAxis().setLabelFormat("{value|p4}");

            viewer.Chart = c;

        }

        private Control activeControl = null;

        // mouse endter event handler
        private void winChartViewer1_MouseEnter(object sender, System.EventArgs e)
        {
            activeControl = winChartViewer1.FindForm().ActiveControl;
            winChartViewer1.FindForm().ActiveControl = winChartViewer1;
        }

        private void winChartViewer1_MouseLeave(object sender, System.EventArgs e)
        {
            winChartViewer1.FindForm().ActiveControl = activeControl;
        }

        // draw track cursor when mouse is moving over plotarea
        private void winChartViewer1_MouseMovePlotArea(object sender, MouseEventArgs e)
        {
            WinChartViewer viewer = (WinChartViewer)sender;
            trackLineLabel((XYChart)viewer.Chart, viewer.PlotAreaMouseX);
            viewer.updateDisplay();
            // Hide the tracck cursor when the mouse leaves the plot area
            //viewer.removeDynamicLayer("MouseLeavePlotArea");
        }

        // mosue wheel event handler
        private void winChartViewer1_MouseWheel(object sender, MouseEventArgs e)
        {
            // we zoom in or out by 10% depeding on the mouse wheel direction
            double r = e.Delta > 0 ? 0.9 : 1 / 0.5;
            // do not zoom in beyongd the zoom in width limit
            if ((r = Math.Max(r, winChartViewer1.ZoomInWidthLimit / winChartViewer1.ViewPortWidth)) == 1)
                return;

            XYChart c = (XYChart)winChartViewer1.Chart;

            double mouseOffset = (e.X - c.getPlotArea().getLeftX()) / (double)c.getPlotArea().getWidth();
            winChartViewer1.ViewPortLeft += mouseOffset * (1 - r) * winChartViewer1.ViewPortWidth;
            winChartViewer1.ViewPortWidth *= r;

            // trigger a view port changed event to update the  chart
            winChartViewer1.updateViewPort(true, false);

        }

        // draw track line with data labels
        private void trackLineLabel(XYChart c, int mouseX)
        {
            DrawArea d = c.initDynamicLayer();

            PlotArea plotArea = c.getPlotArea();
            double xValue = c.getNearestXValue(mouseX);

            int xCoor = c.getXCoor(xValue);

            d.vline(plotArea.getTopY(), plotArea.getBottomY(), xCoor, d.dashLineColor(0x000000, 0x0101));

            // container to hold the legned entries
            ArrayList legendEntries = new ArrayList();

            for (int i = 0; i < c.getLayerCount(); ++i)
            {
                Layer layer = c.getLayerByZ(i);
                int xIndex = layer.getXIndexOf(xValue);

                // iterate through all the data sets in the layer
                for (int j = 0; j < layer.getDataSetCount(); ++j)
                {
                    ChartDirector.DataSet dataSet = layer.getDataSetByZ(j);
                    // we are only interested in visibale sets with names
                    string dataName = dataSet.getDataName();
                    int color = dataSet.getDataColor();
                    if ((!string.IsNullOrEmpty(dataName)) && (color != Chart.Transparent))
                    {
                        // Build the legend entry, consist of the legend icon, name and data value.
                        double dataValue = dataSet.getValue(xIndex);
                        legendEntries.Add("<*block*>" + dataSet.getLegendIcon() + " " + dataName + ": " + ((
                            dataValue == Chart.NoValue) ? "N/A" : c.formatValue(dataValue, "{value|P4}")) +
                            "<*/*>");

                        // Draw a track dot for data points within the plot area
                        int yCoor = c.getYCoor(dataSet.getPosition(xIndex), dataSet.getUseYAxis());
                        if ((yCoor >= plotArea.getTopY()) && (yCoor <= plotArea.getBottomY()))
                        {
                            d.circle(xCoor, yCoor, 4, 4, color, color);
                        }
                    }
                }
            }
            // Create the legend by joining the legend entries
            legendEntries.Reverse();
            string legendText = "<*block,maxWidth=" + plotArea.getWidth() + "*><*block*><*font=Arial Bold*>["
                 + c.xAxis().getFormattedLabel(xValue, "{value|P4") + "]<*/*>        " + String.Join(
                "        ", (string[])legendEntries.ToArray(typeof(string))) + "<*/*>";

            // Display the legend on the top of the plot area
            TTFText t = d.text(legendText, "Arial", 8);
            t.draw(plotArea.getLeftX() + 5, plotArea.getTopY() - 3, 0x000000, Chart.BottomLeft);

        }

        // start the analysis procedure.
        private void buttonStart_Click(object sender, EventArgs e)
        {
            // procedure
            if (useSet)
            {
                if (useSingle)
                {
                    // error
                    return;
                }
                // deal with the set input
                dealSet();
            }

            if (useSingle)
            {
                if (useSet)
                {
                    // error
                    return;
                }
                // deal with single input
                dealSingle();
            }
        }

        // the data to show
        private double[] indexForSecond;
        private double[] indexForFrame;
        private double[] cpuInFrame;
        private double[] gpuInFrame;
        private double[] cpuInSecond;
        private double[] gpuInSecond;
        private double[] fpsInFrame;
        private double[] fpsInSecond;

        double cpuWindowSizeInFrame, cpuWindowSizeInSecond, gpuWindowSizeInFrame, gpuWindowSizeInSecond;

        private void checkBoxShowCpu_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxShowCpu.Checked)
            {
                this.showCpu = true;

            }
            else
            {
                this.showCpu = false;
            }
            // update the viewport
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxShowGpu_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxShowGpu.Checked)
            {
                this.showGpu = true;
            }
            else
            {
                this.showGpu = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private bool showInFrame = false;

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton1.Checked)
                showInFrame = true;
            else
                showInFrame = false;
        }

        private void radioButton2_CheckedChanged(object sender, EventArgs e)
        {
            if (this.radioButton2.Checked)
                showInFrame = false;
            else
                showInFrame = true;
        }

        private void checkBoxShowFps_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxShowFps.Checked)
                showFps = true;
            else
                showFps = false;

            winChartViewer1.updateViewPort(true, true);
        }

    }
}

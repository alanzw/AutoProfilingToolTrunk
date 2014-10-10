using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Collections;

using ChartDirector;

using System.IO;

namespace AutoProfilingForm
{
    public partial class MdiChildForAnalysisAll : Form
    {
        private static MdiChildForAnalysisAll _frmForAnalysisAll = null;

        /// <summary>
        /// the data to show
        /// </summary>
        /// <returns></returns>
        private double[] cpu;
        private double[] gpu;
        private double[] fps;
        private double[] cmd;
        private double[] obj;
        private double[] triangle;
        private double[] draw;
        private double[] data;
        private double[] ibLock;
        private double[] ibSize;
        private double[] vbLock;
        private double[] vbSize;
        private double[] parameterSize;
        private double[] remoteParamSize;
        private double[] surLock;
        private double[] surSize;
        private double[] texLock;
        private double[] texSize;
        private double[] setTex;
        private double[] stateBlock;
        private double[] vShaderCmd;
        private double[] vShaderConst;
        private double[] pShaderCmd;
        private double[] pShaderConst;


        private double[] index;

        /// <summary>
        /// the flags to determine whether to show the datas
        /// </summary>
        private bool showCpu;
        private bool showGpu;
        private bool showCmd;
        private bool showFps;
        private bool showObj;
        private bool showTriangle;
        private bool showDrawTime;
        private bool showDataSize;
        private bool showIbLock;
        private bool showIbSize;
        private bool showVbLock;
        private bool showVbSize;
        private bool showParamSize;
        private bool showRemoteParamSize;
        private bool showSurLock;
        private bool showSurSize;
        private bool showTexLock;
        private bool showTexSize;
        private bool showSetTexTime;
        private bool showStateBlock;
        private bool showVShaderCmd;
        private bool showVShaderConst;
        private bool showPShaderCmd;
        private bool showPShaderConst;


        /// <summary>
        /// the input file path and name
        /// </summary>
        private string inputFileName;
        private string inputFilePath;
        private OpenFileDialog ofDialog = null;

        private bool dataLoaded = false;

        /// <summary>
        /// to get a singlelegton child form.
        /// </summary>
        /// <returns>return the form</returns>
        public static MdiChildForAnalysisAll GetForm()
        {
            if (_frmForAnalysisAll == null)
            {
                _frmForAnalysisAll = new MdiChildForAnalysisAll();
            }
            return _frmForAnalysisAll;
        }

        public MdiChildForAnalysisAll()
        {
            InitializeComponent();
        }

        private void MdiChildForAnalysisAll_FormClosing(Object sender, FormClosingEventArgs e)
        {
            _frmForAnalysisAll.Close();
            _frmForAnalysisAll = null;
        }

        private void Dispose()
        {
            Console.WriteLine("For for analysis all Dispose!");
            _frmForAnalysisAll = null;
        }
        public void Close()
        {
            Dispose();
        }

        ~MdiChildForAnalysisAll()
        {
            Dispose(true);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            Console.WriteLine("enter the start procedure.");
            // check the input file, the read the input and parse it
            if (ofDialog == null)
            {
                Console.WriteLine("the input file is null.");
                return;
            }

            // read the file
            StreamReader sr; //= new StreamReader(ofDialog.FileName);
            sr = File.OpenText(ofDialog.FileName);
            
            if (sr == null)
            {
                Console.WriteLine("null Stream Reader, open failed.");
            }
            string line = null; ;
            int lineIndex = 0;
            string seperator = " ";

            int allLines = 0;
            while(sr.ReadLine()!=null){
                allLines++;
            }

            //allLines++;
            sr.BaseStream.Seek(0, SeekOrigin.Begin);

            this.index = new double[allLines];
                this.cpu = new double[allLines];
                this.fps = new double[allLines];
                this.gpu = new double[allLines];

                this.cmd = new double[allLines];
                this.parameterSize = new double[allLines];
                this.remoteParamSize = new double[allLines];
                this.obj = new double[allLines];
                this.data = new double[allLines];
                this.triangle = new double[allLines];
                this.draw = new double[allLines];
                this.ibLock = new double[allLines];
                this.ibSize = new double[allLines];
                this.vbLock = new double[allLines];
                this.vbSize = new double[allLines];
                this.surLock = new double[allLines];
                this.surSize = new double[allLines];
                this.texLock = new double[allLines];
                this.texSize = new double[allLines];
                this.setTex = new double[allLines];
                this.stateBlock = new double[allLines];
                this.vShaderCmd = new double[allLines];
                this.vShaderConst = new double[allLines];
                this.pShaderCmd = new double[allLines];
                this.pShaderConst = new double[allLines];
            

            while((line = sr.ReadLine())!= null){
                Console.WriteLine(line);
                string[] array;
                array = line.Split(seperator.ToArray());
                if (array.Length < 24)
                {
                    Console.WriteLine("read array from line: " + array.Length);
                }

                this.index[lineIndex] = (double)lineIndex; //double.Parse(array[0]);
                this.cpu[lineIndex] = double.Parse(array[2]);
                this.fps[lineIndex] = double.Parse(array[1]);
                this.gpu[lineIndex] = double.Parse(array[3]);

                Console.WriteLine("index: " + index[lineIndex] +" cpu: "+cpu[lineIndex] +" gpu: "+ gpu[lineIndex] +" fps: "+ fps[lineIndex]);

                this.cmd[lineIndex] = Int32.Parse(array[4]);
                this.parameterSize[lineIndex] = Int64.Parse(array[5]);
                this.remoteParamSize[lineIndex] = Int64.Parse(array[6]);
                this.obj[lineIndex] = Int32.Parse(array[7]);
                this.data[lineIndex] = Int64.Parse(array[8]);
                this.triangle[lineIndex] = Int32.Parse(array[9]);
                this.draw[lineIndex] = Int32.Parse(array[10]);
                this.ibLock[lineIndex] = Int32.Parse(array[11]);
                this.ibSize[lineIndex] = Int32.Parse(array[12]);
                this.vbLock[lineIndex] = Int32.Parse(array[13]);
                this.vbSize[lineIndex] = Int32.Parse(array[14]);
                this.surLock[lineIndex] = Int32.Parse(array[15]);
                this.surSize[lineIndex] = Int64.Parse(array[16]);
                this.texLock[lineIndex] = Int32.Parse(array[17]);
                this.texSize[lineIndex] = Int32.Parse(array[18]);
                this.setTex[lineIndex] = Int32.Parse(array[19]);
                this.stateBlock[lineIndex] = short.Parse(array[20]);
                this.vShaderCmd[lineIndex] = Int32.Parse(array[21]);
                this.vShaderConst[lineIndex] = Int32.Parse(array[22]);
                this.pShaderCmd[lineIndex] = Int32.Parse(array[23]);

                //string.array[24]
                this.pShaderConst[lineIndex] = (int)float.Parse(array[24]);
                lineIndex++;
            }
            Console.WriteLine("end start procedure.");
            
            dataLoaded = true;

            // show chart
            ShowChart();
        }
        /// <summary>
        /// to show the chart, check the show flag and draw the chart
        /// </summary>
        private void ShowChart(){
            
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
        private void initChartViewer(WinChartViewer viewer){
            // set the x range
           // if (dataLoaded)
            {
                Console.WriteLine("data loaded in init chart viewer, index lenght: " + index.Length);
                viewer.setFullRange("x", index[0], index[index.Length - 1]);
                // init the view prot to show the latest 20% of the result
                
                viewer.ViewPortWidth = 0.2;
                viewer.ViewPortLeft = 1 - viewer.ViewPortWidth;

                // set the maximum zoom to 10 points
                viewer.ZoomInWidthLimit = 10.0 / index.Length;
            }

            // init the set the mouse usage to "pointer" mode (drag to sroll mode)
            viewer.Dock = DockStyle.Fill;

        }

        // the scroll bar event handler
        private void hScrollBar1_ValueChanged(object sender, EventArgs e)
        {
            //if (dataLoaded)
            {
                winChartViewer1.ViewPortLeft = ((double)(hScrollBar1.Value - hScrollBar1.Minimum))/ (hScrollBar1.Maximum - hScrollBar1.Minimum);
                winChartViewer1.updateViewPort(true, false);
            }
        }


        // the ViewportChanged event handle, this event occurs if the user scrolls or zooms in or out the chart by dragging or clicking on th echart. it can also be triggered by calling WinChartViewer.updateViewPort
        private void winChartViewer1_ViewPortChanged(object sender, WinViewPortEventArgs e){
            // in addition to updating the chart , we may also need to updata other controls that changeds based on the view port
            updateControls(winChartViewer1);

            // update the chart if necessary
            if(e.NeedUpdateChart)
                drawChart(winChartViewer1);

            if((!winChartViewer1.IsInMouseMoveEvent ) ){
                trackLineLabel((XYChart)winChartViewer1.Chart, winChartViewer1.PlotAreaMouseX);
                winChartViewer1.updateDisplay();
            }
        }

        // update the control
        private void updateControls(WinChartViewer viewer){
            // update the start data and end data to reflect the viewport
            hScrollBar1.Enabled = winChartViewer1.ViewPortWidth < 1;
            hScrollBar1.LargeChange = (int)Math.Ceiling(winChartViewer1.ViewPortWidth *
                (hScrollBar1.Maximum - hScrollBar1.Minimum));
            hScrollBar1.SmallChange = (int)Math.Ceiling(hScrollBar1.LargeChange * 0.1);
            hScrollBar1.Value = (int)Math.Round(winChartViewer1.ViewPortLeft *
                (hScrollBar1.Maximum - hScrollBar1.Minimum)) + hScrollBar1.Minimum;
        }

        private void drawChart(WinChartViewer viewer){
            // get the start index that are visible on the chart
            double viewPortStartIndex = viewer.getValueAtViewPort("x", viewer.ViewPortLeft);
            double viewPortEndIndex = viewer.getValueAtViewPort("x", viewer.ViewPortLeft + viewer.ViewPortWidth);

            // Get the array indexes that corresponds to the visible start and end
            int startIndex = (int)Math.Floor(Chart.bSearch(index, viewPortStartIndex));
            int endIndex = (int)Math.Ceiling(Chart.bSearch(index, viewPortEndIndex));

            Console.WriteLine("port start: " + viewPortStartIndex + " port end: "+ viewPortEndIndex + " start: " + startIndex + " end: " + endIndex +" index length: "+ index.Length);

            int noOfPoints = endIndex - startIndex + 1;

            // declaration the data set
            double[] viewPortDataSeriesCpu;
            double[] viewPortDataSeriesGpu;
            double[] viewPortDataSeriesFps;
            double[] viewPortDataSeriesCmd;
            double[] viewPortDataSeriesObj;
            double[] viewPortDataSeriesTriangle;
            double[] viewPortDataSeriesDrawTime;
            double[] viewPortDataSeriesDataSize;
            double[] viewPortDataSeriesIbLock;
            double[] viewPortDataSeriesIbSize;
            double[] viewPortDataSeriesVbLock;
            double[] viewPortDataSeriesVbSize;
            double[] viewPortDataSeriesParamSize;
            double[] viewPortDataSeriesRemoteParamSize;
            double[] viewPortDataSeriesSurLock;
            double[] viewPortDataSeriesSurSize;
            double[] viewPortDataSeriesTexLock;
            double[] viewPortDataSeriesTexSize;
            double[] viewPortDataSeriesSetTexture;
            double[] viewPortDataSeriesStateBlock;
            double[] viewPortDataSeriesVShaderCmd;
            double[] viewPortDataSeriesVShaderConst;
            double[] viewPortDataSeriesPShaderCmd;
            double[] viewPortDataSeriesPShaderConst;

            double[] viewPortIndex = (double[])Chart.arraySlice(index, startIndex, noOfPoints);
            if (this.showCpu)
            {
                viewPortDataSeriesCpu = (double[])Chart.arraySlice(cpu, startIndex, noOfPoints);
            }
            if (this.showGpu)
            {
                viewPortDataSeriesGpu = (double[])Chart.arraySlice(gpu, startIndex, noOfPoints);
            }
            if (this.showFps)
            {
                viewPortDataSeriesFps = (double[])Chart.arraySlice(fps, startIndex, noOfPoints);
            }
            if(this.showCmd)
                viewPortDataSeriesCmd = (double[])Chart.arraySlice(cmd, startIndex, noOfPoints);

            if (this.showObj)
                viewPortDataSeriesObj = (double[])Chart.arraySlice(obj, startIndex, noOfPoints);
            if (this.showTriangle)
                viewPortDataSeriesTriangle = (double[])Chart.arraySlice(triangle, startIndex, noOfPoints);
            if (this.showDrawTime)
                viewPortDataSeriesDrawTime = (double[])Chart.arraySlice(draw, startIndex, noOfPoints);
            if (this.showDataSize)
                viewPortDataSeriesDataSize = (double[])Chart.arraySlice(data, startIndex, noOfPoints);
            if (this.showIbLock)
                viewPortDataSeriesIbLock = (double[])Chart.arraySlice(ibLock, startIndex, noOfPoints);
            if (this.showIbSize)
                viewPortDataSeriesIbSize = (double[])Chart.arraySlice(ibSize, startIndex, noOfPoints);

            if (this.showVbLock)
                viewPortDataSeriesVbLock = (double[])Chart.arraySlice(vbLock, startIndex, noOfPoints);
            if (this.showVbSize)
                viewPortDataSeriesVbSize = (double[])Chart.arraySlice(vbSize, startIndex, noOfPoints);
            if (this.showParamSize)
                viewPortDataSeriesParamSize = (double[])Chart.arraySlice(parameterSize, startIndex, noOfPoints);
            if (this.showRemoteParamSize)
                viewPortDataSeriesRemoteParamSize = (double[])Chart.arraySlice(remoteParamSize, startIndex, noOfPoints);
            if (this.showSurLock)
                viewPortDataSeriesSurLock = (double[])Chart.arraySlice(surLock, startIndex, noOfPoints);

            if (this.showSurSize)
                viewPortDataSeriesSurSize = (double[])Chart.arraySlice(surSize, startIndex, noOfPoints);
            if (this.showTexLock)
                viewPortDataSeriesTexLock = (double[])Chart.arraySlice(texLock, startIndex, noOfPoints);
            if (this.showTexSize)
                viewPortDataSeriesTexSize = (double[])Chart.arraySlice(texSize, startIndex, noOfPoints);
            if (this.showSetTexTime)
                viewPortDataSeriesSetTexture = (double[])Chart.arraySlice(setTex, startIndex, noOfPoints);
            if (this.showStateBlock)
                viewPortDataSeriesStateBlock = (double[])Chart.arraySlice(stateBlock, startIndex, noOfPoints);

            if (this.showVShaderCmd)
                viewPortDataSeriesVShaderCmd = (double[])Chart.arraySlice(vShaderCmd, startIndex, noOfPoints);
            if (this.showVShaderConst)
                viewPortDataSeriesVShaderConst = (double[])Chart.arraySlice(vShaderConst, startIndex, noOfPoints);
            if (this.showPShaderCmd)
                viewPortDataSeriesPShaderCmd = (double[])Chart.arraySlice(pShaderCmd, startIndex, noOfPoints);
            if (this.showPShaderConst)
                viewPortDataSeriesPShaderConst = (double[])Chart.arraySlice(pShaderConst, startIndex, noOfPoints);



            // configure overall chart apperance
            XYChart c = new XYChart(820, 490);

            c.setPlotArea(55, 50, c.getWidth() - 80, c.getHeight() - 85, c.linearGradientColor(0, 50, 0, c.getHeight() - 35, 0xf0f6ff, 0xa0c0ff), -1, Chart.Transparent, 0xffffff, 0xfffff); 

            c.setClipping();

            c.addTitle(" All charactor for game", "Times New Roman Bold Italic", 10);

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


            layer.setXData(this.index);

            /*
            layer.addDataSet(viewPortDataSeriesCpu, 0xff3333, "CPU");
            layer.addDataSet(viewPortDataSeriesGpu, 0x008800, "GPU");
            layer.addDataSet(viewPortDataSeriesFps, 0x3333cc, "FPS");
            */
            if(this.showCpu)
                layer.addDataSet(cpu, 0xff3333, "CPU");
            if(this.showGpu)
                layer.addDataSet(gpu, 0x008800, "GPU");
            if(this.showFps)
                layer.addDataSet(fps, 0x3333cc, "FPS");


            if (this.showCmd)
                layer.addDataSet(cmd, 0x3388cc, "CMD");

            if (this.showObj)
                layer.addDataSet(obj, 0x8833cc, "OBJ");
            if (this.showTriangle)
                layer.addDataSet(triangle, 0x333388, "TRI");
            if (this.showDrawTime)
                layer.addDataSet(draw, 0xff0000, "DRAW");
            if (this.showDataSize)
                layer.addDataSet(data, 0xff00cc, "DATA");
            if (this.showIbLock)
                layer.addDataSet(ibLock, 0x8888cc, "IBLOCK");
            if (this.showIbSize)
                layer.addDataSet(ibSize, 0x8833cc, "IBSIZE");

            if (this.showVbLock)
                layer.addDataSet(vbLock, 0x3333cc, "VBLOCK");
            if (this.showVbSize)
                layer.addDataSet(vbSize, 0x3333cc, "VBSIZE");
            if (this.showParamSize)
                layer.addDataSet(parameterSize, 0x3333cc, "PARAM");
            if (this.showRemoteParamSize)
                layer.addDataSet(remoteParamSize, 0x3333cc, "REMOTE");
            if (this.showSurLock)
                layer.addDataSet(surLock, 0x3333cc, "SURLOCK");

            if (this.showSurSize)
                layer.addDataSet(surSize, 0x3333cc, "SURSIZE");
            if (this.showTexLock)
                layer.addDataSet(texLock, 0x3333cc, "TEXLOCK");
            if (this.showTexSize)
                layer.addDataSet(texSize, 0x3333cc, "TEXSIZE");
            if (this.showSetTexTime)
                layer.addDataSet(setTex, 0x3333cc, "SETTEX");
            if (this.showStateBlock)
                layer.addDataSet(stateBlock, 0x3333cc, "STATEBLOCK");

            if (this.showVShaderCmd)
                layer.addDataSet(vShaderCmd, 0x3333cc, "VSC");
            if (this.showVShaderConst)
                layer.addDataSet(vShaderConst, 0x3333cc, "VSCONST");
            if (this.showPShaderCmd)
                layer.addDataSet(pShaderCmd, 0x3333cc, "PSC");
            if (this.showPShaderConst)
                layer.addDataSet(pShaderConst, 0x3333cc, "PSCONST");


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


        /// <summary>
        /// Load for the form for analyzing the detailed game charactors.
        /// </summary>
        /// <param name="sender">the object</param>
        /// <param name="e">the event args</param>
        private void MdiChildForAnalysisAll_Load(object sender, EventArgs e)
        {
            //ShowChart(); 

        }

        /// <summary>
        /// clear all the show flag to false, and clear the graph
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonClear_Click(object sender, EventArgs e)
        {
            showCpu = false;
            showCmd = false;
            showDataSize = false;
            showDrawTime = false;
            showFps = false;
            showGpu = false;
            showIbLock = false;
            showIbSize = false;
            showObj = false;
            showParamSize = false;
            showPShaderCmd = false;
            showPShaderConst = false;
            showRemoteParamSize = false;
            showSetTexTime = false;
            showStateBlock = false;
            showSurLock = false;
            showSurSize =  false;
            showTexLock = false;
            showTexSize = false;
            showTriangle = false;
            showVbLock = false;
            showVbSize = false;
            showVShaderCmd = false;
            showVShaderConst = false;

            // set the check box false
            checkBoxCpu.Checked = false;
            checkBoxGpu.Checked = false;
            checkBoxCmd.Checked = false;
            checkBoxObj.Checked = false;
            checkBoxTriangle.Checked = false;
            checkBoxDraw.Checked = false;
            checkBoxData.Checked = false;
            checkBoxIbLock.Checked = false;
            checkBoxIbSize.Checked = false;
            checkBoxVbLock.Checked = false;
            checkBoxVbSize.Checked = false;
            checkBoxParamSize.Checked = false;
            checkBoxRemoteParamSize.Checked = false;
            checkBoxSurLock.Checked = false;
            checkBoxSurSize.Checked = false;
            checkBoxTexLock.Checked = false;
            checkBoxTexSize.Checked = false;
            checkBoxSetTex.Checked = false;
            checkBoxStateBlock.Checked = false;
            checkBoxVshaderCmd.Checked = false;
            checkBoxVshaderConst.Checked = false;
            checkBoxpShaderCmd.Checked = false;
            checkBoxpShaderSize.Checked = false;
            checkBoxFps.Checked = false;
            winChartViewer1.updateViewPort(true, true);

        }
        /// <summary>
        /// open the file dialog to select a input file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void buttonOpenInput_Click(object sender, EventArgs e)
        {
            byte[] bytes;

            ofDialog = new OpenFileDialog();
            ofDialog.Filter = "Detailed charactor file(*.second.log)|*.second.log";
            DialogResult ofFlag = ofDialog.ShowDialog();
            if (ofFlag == DialogResult.OK)
            {
                inputFileName = System.IO.Path.GetFileName(ofDialog.FileName);
                inputFilePath = System.IO.Path.GetDirectoryName(ofDialog.FileName);

                Console.WriteLine("file: " + inputFileName);
                Console.WriteLine("path: " + inputFilePath);
                this.textBox1.Text = ofDialog.FileName;
            }
        }

        private void MdiChildForAnalysisAll_ResizeBegin(object sender, EventArgs e)
        {
            // to correct the layout
            this.buttonStart.SetBounds(this.panel2.Width - this.buttonStart.Width, this.buttonStart.Location.Y, this.buttonStart.Width, this.buttonStart.Height);
        }

        // cpu check box status changed
        private void checkBoxCpu_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxCpu.Checked)
            {
                this.showCpu = true;
            }
            else
            {
                this.showCpu = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxGpu_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxGpu.Checked)
            {
                this.showGpu = true;
            }
            else
            {
                this.showGpu = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        // cmd check box status changed
        private void checkBoxCmd_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxCmd.Checked)
            {
                this.showCmd = true;
            }
            else
            {
                this.showCmd = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxFps_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxFps.Checked)
            {
                this.showFps = true;
            }
            else
            {
                this.showFps = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxObj_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxObj.Checked)
            {
                this.showObj = true;
            }
            else
            {
                this.showObj = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxTriangle_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTriangle.Checked)
            {
                this.showTriangle = true;
            }
            else
            {
                this.showTriangle = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxDraw_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxDraw.Checked)
            {
                this.showDrawTime = true;
            }
            else
            {
                this.showDrawTime = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxData_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxData.Checked)
            {
                this.showDataSize = true;
            }
            else
            {
                this.showDataSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxIbLock_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxIbLock.Checked)
            {
                this.showIbLock = true;
            }
            else
            {
                this.showIbLock = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxIbSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxIbSize.Checked)
            {
                this.showIbSize = true;
            }
            else
            {
                this.showIbSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxVbLock_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxVbLock.Checked)
            {
                this.showVbLock = true;
            }
            else
            {
                this.showVbLock = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxVbSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxVbSize.Checked)
            {
                this.showVbSize = true;
            }
            else
            {
                this.showVbSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxParamSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxParamSize.Checked)
            {
                this.showParamSize = true;
            }
            else
            {
                this.showParamSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxRemoteParamSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxRemoteParamSize.Checked)
            {
                this.showRemoteParamSize = true;
            }
            else
            {
                this.showRemoteParamSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxSurLock_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxSurLock.Checked)
            {
                this.showSurLock = true;
            }
            else
            {
                this.showSurLock = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxSurSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxSurSize.Checked)
            {
                this.showSurSize = true;
            }
            else
            {
                this.showSurSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxTexLock_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTexLock.Checked)
            {
                this.showTexLock = true;
            }
            else
            {
                this.showTexLock = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxTexSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxTexSize.Checked)
            {
                this.showTexSize = true;
            }
            else
            {
                this.showTexSize = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxSetTex_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxSetTex.Checked)
            {
                this.showSetTexTime = true;
            }
            else
            {
                this.showSetTexTime = false;
            } 
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxStateBlock_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxStateBlock.Checked)
            {
                this.showStateBlock = true;
            }
            else
            {
                this.showStateBlock = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxVshaderCmd_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxVshaderCmd.Checked)
            {
                this.showVShaderCmd = true;
            }
            else
            {
                this.showVShaderCmd = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxVshaderConst_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxVshaderConst.Checked)
            {
                this.showVShaderConst = true;
            }
            else
            {
                this.showVShaderConst = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxpShaderCmd_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxpShaderCmd.Checked)
            {
                this.showPShaderCmd = true;
            }
            else
            {
                this.showPShaderCmd = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxpShaderSize_CheckedChanged(object sender, EventArgs e)
        {
            if (this.checkBoxpShaderSize.Checked)
            {
                this.showPShaderConst = true;
            }
            else
            {
                this.showPShaderConst = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }

        private void buttonShowAll_Click(object sender, EventArgs e)
        {
            showCpu = true;
            showCmd = true;
            showDataSize = true;
            showDrawTime = true;
            showFps = true;
            showGpu = true;
            showIbLock = true;
            showIbSize = true;
            showObj = true;
            showParamSize = true;
            showPShaderCmd = true;
            showPShaderConst = true;
            showRemoteParamSize = true;
            showSetTexTime = true;
            showStateBlock = true;
            showSurLock = true;
            showSurSize = true;
            showTexLock = true;
            showTexSize = true;
            showTriangle = true;
            showVbLock = true;
            showVbSize = true;
            showVShaderCmd = true;
            showVShaderConst = true;

            // set the check box false
            checkBoxCpu.Checked = true;
            checkBoxGpu.Checked = true;
            checkBoxCmd.Checked = true;
            checkBoxObj.Checked = true;
            checkBoxTriangle.Checked = true;
            checkBoxDraw.Checked = true;
            checkBoxData.Checked = true;
            checkBoxIbLock.Checked = true;
            checkBoxIbSize.Checked = true;
            checkBoxVbLock.Checked = true;
            checkBoxVbSize.Checked = true;
            checkBoxParamSize.Checked = true;
            checkBoxRemoteParamSize.Checked = true;
            checkBoxSurLock.Checked = true;
            checkBoxSurSize.Checked = true;
            checkBoxTexLock.Checked = true;
            checkBoxTexSize.Checked = true;
            checkBoxSetTex.Checked = true;
            checkBoxStateBlock.Checked = true;
            checkBoxVshaderCmd.Checked = true;
            checkBoxVshaderConst.Checked = true;
            checkBoxpShaderCmd.Checked = true;
            checkBoxpShaderSize.Checked = true;
            checkBoxFps.Checked = true;
            winChartViewer1.updateViewPort(true, true);
        }

        private void checkBoxGpu_CheckedChanged_1(object sender, EventArgs e)
        {
            if (this.checkBoxGpu.Checked)
            {
                this.showGpu = true;
            }
            else
            {
                this.showGpu = false;
            }
            winChartViewer1.updateViewPort(true, true);
        }



        
    }
}

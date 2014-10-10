using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using ConsoleControlAPI;


namespace ConsoleControl
{
    /// <summary>
    /// the console evnt handler is used for console events.
    /// </summary>
    /// <param name="sender">the sender</param>
    /// <param name="args">the <see cref="ConsoleEventArgs"/> instance containing the event data.</param>
    public delegate void ConsoleEventHandler(object sender, ConsoleEventArgs args);

    /// <summary>
    /// The console Control allows you to embed a basic console in your application.
    /// </summary>
    public partial class ConsoleControl : UserControl
    {
        /// <summary>
        /// initializes a new instance of the <see cref="ConsoleControl"/> class.
        /// </summary>
        public ConsoleControl()
        {
            // init the component.
            InitializeComponent();

            // show diagnostics disabled by defualt.
            ShowDiagnostics = false;

            //  Input enabled by default.
            IsInputEnabled = true;

            //  Disable special commands by default.
            SendKeyboardCommandsToProcess = false;

            //  Initialise the keymappings.
            InitialiseKeyMappings();

            //  Handle process events.
            processInterace.OnProcessOutput += processInterace_OnProcessOutput;
            processInterace.OnProcessError += processInterace_OnProcessError;
            processInterace.OnProcessInput += processInterace_OnProcessInput;
            processInterace.OnProcessExit += processInterace_OnProcessExit;

            //  Wait for key down messages on the rich text box.
            richTextBoxConsole.KeyDown += richTextBoxConsole_KeyDown;
        }
        /// <summary>
        /// Handles the OnProcessError event of the processInterace control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="args">The <see cref="ProcessEventArgs"/> instance containing the event data.</param>
        void processInterace_OnProcessError(object sender, ProcessEventArgs args)
        {
            //  Write the output, in red
            WriteOutput(args.Content, Color.Red);

            //  Fire the output event.
            FireConsoleOutputEvent(args.Content);
        }

        /// <summary>
        /// Handles the OnProcessOutput event of the processInterace control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="args">The <see cref="ProcessEventArgs"/> instance containing the event data.</param>
        void processInterace_OnProcessOutput(object sender, ProcessEventArgs args)
        {
            //  Write the output, in white
            WriteOutput(args.Content, Color.White);

            //  Fire the output event.
            FireConsoleOutputEvent(args.Content);
        }

        /// <summary>
        /// Handles the OnProcessInput event of the processInterace control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="args">The <see cref="ProcessEventArgs"/> instance containing the event data.</param>
        void processInterace_OnProcessInput(object sender, ProcessEventArgs args)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Handles the OnProcessExit event of the processInterace control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="args">The <see cref="ProcessEventArgs"/> instance containing the event data.</param>
        void processInterace_OnProcessExit(object sender, ProcessEventArgs args)
        {
            //  Are we showing diagnostics?
            if (ShowDiagnostics)
            {
                WriteOutput(Environment.NewLine + processInterace.ProcessFileName + " exited.", Color.FromArgb(255, 0, 255, 0));
            }

            if (!this.IsHandleCreated)
                return;
            //  Read only again.
            Invoke((Action)(() =>
            {
                richTextBoxConsole.ReadOnly = true;
            }));
        }

        /// <summary>
        /// Initialises the key mappings.
        /// </summary>
        private void InitialiseKeyMappings()
        {
            //  Map 'tab'.
            keyMappings.Add(new KeyMapping(false, false, false, Keys.Tab, "{TAB}", "\t"));

            //  Map 'Ctrl-C'.
            keyMappings.Add(new KeyMapping(true, false, false, Keys.C, "^(c)", "\x03\r\n"));
        }

        /// <summary>
        /// Handles the KeyDown event of the richTextBoxConsole control.
        /// </summary>
        /// <param name="sender">The source of the event.</param>
        /// <param name="e">The <see cref="System.Windows.Forms.KeyEventArgs"/> instance containing the event data.</param>
        void richTextBoxConsole_KeyDown(object sender, KeyEventArgs e)
        {
            //  Are we sending keyboard commands to the process?
            if (SendKeyboardCommandsToProcess && IsProcessingRunning)
            {
                //  Get key mappings for this key event?
                var mappings = from k in keyMappings
                               where
                               (k.KeyCode == e.KeyCode &&
                               k.IsAltPressed == e.Alt &&
                               k.IsControlPressed == e.Control &&
                               k.IsShiftPressed == e.Shift)
                               select k;

                //  Go through each mapping, send the message.
                foreach (var mapping in mappings)
                {
                    //SendKeysEx.SendKeys(CurrentProcessHwnd, mapping.SendKeysMapping);
                    //inputWriter.WriteLine(mapping.StreamMapping);
                    //WriteInput("\x3", Color.White, false);
                }

                //  If we handled a mapping, we're done here.
                if (mappings.Any())
                {
                    e.SuppressKeyPress = true;
                    return;
                }
            }

            //  If we're at the input point and it's backspace, bail.
            if ((richTextBoxConsole.SelectionStart <= inputStart) && e.KeyCode == Keys.Back) e.SuppressKeyPress = true;

            //  Are we in the read-only zone?
            if (richTextBoxConsole.SelectionStart < inputStart)
            {
                //  Allow arrows and Ctrl-C.
                if (!(e.KeyCode == Keys.Left ||
                    e.KeyCode == Keys.Right ||
                    e.KeyCode == Keys.Up ||
                    e.KeyCode == Keys.Down ||
                    (e.KeyCode == Keys.C && e.Control)))
                {
                    e.SuppressKeyPress = true;
                }
            }

            //  Is it the return key?
            if (e.KeyCode == Keys.Return)
            {
                //  Get the input.
                string input = richTextBoxConsole.Text.Substring(inputStart, (richTextBoxConsole.SelectionStart) - inputStart);

                //  Write the input (without echoing).
                WriteInput(input, Color.White, false);
            }
        }

        /// <summary>
        /// Writes the output to the console control.
        /// </summary>
        /// <param name="output">The output.</param>
        /// <param name="color">The color.</param>
        public void WriteOutput(string output, Color color)
        {
            if (string.IsNullOrEmpty(lastInput) == false &&
                (output == lastInput || output.Replace("\r\n", "") == lastInput))
                return;

            if (!this.IsHandleCreated)
                return;

            Invoke((Action)(() =>
            {
                //  Write the output.
                richTextBoxConsole.SelectionColor = color;
                richTextBoxConsole.SelectedText += output;
                inputStart = richTextBoxConsole.SelectionStart;
            }));
        }

        /// <summary>
        /// Clears the output.
        /// </summary>
        public void ClearOutput()
        {
            richTextBoxConsole.Clear();
            inputStart = 0;
        }

        /// <summary>
        /// Writes the input to the console control.
        /// </summary>
        /// <param name="input">The input.</param>
        /// <param name="color">The color.</param>
        /// <param name="echo">if set to <c>true</c> echo the input.</param>
        public void WriteInput(string input, Color color, bool echo)
        {
            Invoke((Action)(() =>
            {
                //  Are we echoing?
                if (echo)
                {
                    richTextBoxConsole.SelectionColor = color;
                    richTextBoxConsole.SelectedText += input;
                    inputStart = richTextBoxConsole.SelectionStart;
                }

                lastInput = input;

                //  Write the input.
                processInterace.WriteInput(input);

                //  Fire the event.
                FireConsoleInputEvent(input);
            }));
        }

        /// <summary>
        /// Runs a process.
        /// </summary>
        /// <param name="fileName">Name of the file.</param>
        /// <param name="arguments">The arguments.</param>
        public void StartProcess(string fileName, string arguments)
        {
            //  Are we showing diagnostics?
            if (ShowDiagnostics)
            {
                WriteOutput("Preparing to run " + fileName, Color.FromArgb(255, 0, 255, 0));
                if (!string.IsNullOrEmpty(arguments))
                    WriteOutput(" with arguments " + arguments + "." + Environment.NewLine, Color.FromArgb(255, 0, 255, 0));
                else
                    WriteOutput("." + Environment.NewLine, Color.FromArgb(255, 0, 255, 0));
            }

            //  Start the process.
            processInterace.StartProcess(fileName, arguments);

            //  If we enable input, make the control not read only.
            if (IsInputEnabled)
                richTextBoxConsole.ReadOnly = false;
        }

        /// <summary>
        /// Stops the process.
        /// </summary>
        public void StopProcess()
        {
            //  Stop the interface.
            processInterace.StopProcess();
        }

        /// <summary>
        /// Fires the console output event.
        /// </summary>
        /// <param name="content">The content.</param>
        private void FireConsoleOutputEvent(string content)
        {
            //  Get the event.
            var theEvent = OnConsoleOutput;
            if (theEvent != null)
                theEvent(this, new ConsoleEventArgs(content));
        }

        /// <summary>
        /// Fires the console input event.
        /// </summary>
        /// <param name="content">The content.</param>
        private void FireConsoleInputEvent(string content)
        {
            //  Get the event.
            var theEvent = OnConsoleInput;
            if (theEvent != null)
                theEvent(this, new ConsoleEventArgs(content));
        }

        /// <summary>
        /// The internal process interface used to interface with the process.
        /// </summary>
        private readonly ProcessInterface processInterace = new ProcessInterface();

        int inputStart = -1;

        private bool isInputEnabled = true;

        private string lastInput;

        private List<KeyMapping> keyMappings = new List<KeyMapping>();

        public event ConsoleEventHandler OnConsoleOutput;

        public event ConsoleEventHandler OnConsoleInput;

        [Category("Console Control"), Description("show diagnostic information, such as exception.")]
        public bool ShowDiagnostics
        {
            get;
            set;
        }

        [Category("Console Control"), Description("If true, the user can key in input.")]
        public bool IsInputEnabled
        {
            get { return isInputEnabled; }
            set
            {
                isInputEnabled = value;
                if (IsProcessingRunning)
                    richTextBoxConsole.ReadOnly = !value;
            }
        }

        /// <summary>
        /// Gets or sets a value indicating whether [send keyboard commands to process].
        /// </summary>
        /// <value>
        /// 	<c>true</c> if [send keyboard commands to process]; otherwise, <c>false</c>.
        /// </value>
        [Category("Console Control"), Description("If true, special keyboard commands like Ctrl-C and tab are sent to the process.")]
        public bool SendKeyboardCommandsToProcess
        {
            get;
            set;
        }

        /// <summary>
        /// Gets a value indicating whether this instance is process running.
        /// </summary>
        /// <value>
        /// 	<c>true</c> if this instance is process running; otherwise, <c>false</c>.
        /// </value>
        [Browsable(false)]
        public bool IsProcessingRunning
        {
            get { return processInterace.IsProcessRunning; }
        }

        /// <summary>
        /// Gets the process interface.
        /// </summary>
        [Browsable(false)]
        public ConsoleControlAPI.ProcessInterface ProcessInterface
        {
            get { return processInterace; }
        }

        /// <summary>
        /// Gets the internal rich text box.
        /// </summary>
        [Browsable(false)]
        public RichTextBox InternalRichTextBox
        {
            get { return richTextBoxConsole; }
        }

        [Browsable(false)]
        public List<KeyMapping> KeyMappings
        {
            get{ return keyMappings; }
        }

        public override Font Font
        {
            get
            {
                return base.Font;
            }
            set
            {
                base.Font = value;
                richTextBoxConsole.Font = value;
            }
        }

        /// <summary>
        /// Gets or sets the background color for the control.
        /// </summary>
        /// <returns>A <see cref="T:System.Drawing.Color"/> that represents the background color of the control. The default is the value of the <see cref="P:System.Windows.Forms.Control.DefalutBackColor"/> property.</returns>
        
        /// <PermissionSet>
        /// 
        /// </PermissionSet>"
        public override Color BackColor
        {
            get
            {
                return base.BackColor;
            }
            set
            {
                base.BackColor = value;

                // and the internal control
                richTextBoxConsole.BackColor = value;
            }
        }
    }
    /// <summary>
    /// Used to allow us to find resources properly.
    /// </summary>
    public class Resfinder { }
}

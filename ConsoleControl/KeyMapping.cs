using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace ConsoleControl
{
    /// <summary>
    /// A keymapping defines how a key combination should be mapped to SendKeys message.
    /// </summary>
    public class KeyMapping
    {
        /// <summary>
        /// Initializes a new instance of the <see cref="KeyMapping"/> class.
        /// </summary>
        public KeyMapping() { }

        /// <summary>
        /// Initalizes a new instance of the <see cref="KeyMapping"/> class
        /// </summary>
        /// <param name="control">if set to <c>true</c> [control].</param>
        /// <param name="alt">if set to <c>true</c> [alt].</param>
        /// <param name="shift">if set to <c>true</c> [shift].</param>
        /// <param name="keyCode">The key code.</param>
        /// <param name="sendKeyMapping">The send keys mapping.</param>
        /// <param name="streamMapping">The stream mapping.</param>
        public KeyMapping(bool control, bool alt, bool shift, Keys keyCode, string sendKeyMapping, string streamMapping)
        {
            IsControlPressed = control;
            IsAltPressed = alt;
            IsShiftPressed = shift;
            KeyCode = KeyCode;
            SendKeysMapping = sendKeyMapping;
            StreamMapping = streamMapping;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instace is control pressed
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is control pressed; otherwise, <c>false</c>.
        /// </value>
        public bool IsControlPressed
        {
            get;
            set;
        }
        /// <summary>
        /// Gets or sets a value indicating whether alt is pressed.
        /// </summary>
        /// <value>
        /// <c>true</c> if this instance is alt pressed; otherwise, <c>false</c>.
        /// </value>
        public bool IsAltPressed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets a value indicating whether this instance is shift pressed.
        /// </summary>
        /// <value>
        /// <c>true</c> is this instance is shift pressed; otherwise, <c>false</c>.
        /// </value>
        public bool IsShiftPressed
        {
            get;
            set;
        }

        /// <summary>
        /// Gets or sets the key code
        /// </summary>
        /// <value>
        /// the key code.
        /// </value>
        public Keys KeyCode
        {
            get;
            set;
        }

        /// <summary>
        /// 
        /// Gets or sets the send keys mapping.
        /// </summary>
        /// <value>the send keys mapping.</value>
        public string SendKeysMapping
        {
            get;
            set;
        }
        /// <summary>
        /// Gets or sets the stream mapping.
        /// </summary>
        /// <value>the stream mapping.</value>
        public string StreamMapping
        {
            get;
            set;
        }
    }
}

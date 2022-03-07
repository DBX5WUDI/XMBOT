using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;

namespace WindowsFormsApplication1
{
    public partial class xm_ass : Form
    {
        enum BUTTON
        {
            SHAKING_HANDS,              //0

            SET_ROBOT_SPEED,            //1
            READ_ROBOT_SPEED,           //2
            READ_COORDINATE_DATA,       //4
            CLEAR_COORDINATE_DATA,      //5

            PLAT_MOVE,                      //6
            READ_PLAT,                     //7
            SET_ARM_TOTAL,              //8
            READ_ARM_TOTAL,             //9
            SET_WRIST,                  //a
            READ_WRIST,                 //b
            SET_CLAW	                    //c
        }
        BUTTON button;

        public xm_ass()
        {
            InitializeComponent();
            CheckForIllegalCrossThreadCalls = false;
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            srlboBox.Items.Clear();
            srlboBox.Items.AddRange(ports);
            if (srlboBox.Items.Count == 1) { srlboBox.SelectedIndex = 0; }
            this.bdrtboBox.Items.AddRange(new object[]{    
            "USB模式",
            "蓝牙模式"});  

        }
        private void srlbtn_Click(object sender, EventArgs e)
        {
            if (serialPort1.IsOpen)
            {
                serialPort1.Close();
                srlbtn.Text = "打开";
            }
            else
            {
                if (srlboBox.Text == "")
                {
                    MessageBox.Show("无效的串口！");
                    return;
                }
                if (bdrtboBox.Text == "")
                {
                    MessageBox.Show("请设置通讯模式！");
                    return;
                }
                serialPort1.PortName = srlboBox.Text;
                if (this.bdrtboBox.Text == "USB模式")
                {
                    serialPort1.BaudRate = 921600;
                }
                else if (this.bdrtboBox.Text == "蓝牙模式")
                {
                    serialPort1.BaudRate = 115200;
                }
                try
                {
                    serialPort1.Open();
                    srlbtn.Text = "关闭";
                }
                catch (Exception e1)
                {
                    serialPort1 = new SerialPort();
                    MessageBox.Show(e1.Message);
                }
            }
        }

        private void clrbtn_Click(object sender, EventArgs e)
        {
            rcvtxtBox.Clear();
        }
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                Byte[] receivedData = new Byte[serialPort1.BytesToRead];        //创建接收字节数组  
                serialPort1.Read(receivedData, 0, receivedData.Length);         //读取数据                         
                serialPort1.DiscardInBuffer();                                  //清空SerialPort控件的Buffer  
                string strRcv = null;

                for (int i = 0; i < receivedData.Length; i++) //窗体显示  
                {
                    strRcv += receivedData[i].ToString("X2");  //16进制显示  
                    strRcv += " ";
                }
                rcvtxtBox.Text += strRcv + "\r\n";
            }
            catch (System.Exception ex)
            {
                MessageBox.Show(ex.Message, "出错提示");
            }  
        }
        private void serialPort1_sendStr(string sndtxt)
        {
            if (serialPort1.IsOpen)
            {
                string strSend = sndtxt;
                string sendnoNull = strSend.Trim();
                string sendNOComma = sendnoNull.Replace(',', ' ');
                sendNOComma.Replace("0x", "");
                sendNOComma.Replace("0X", "");
                string[] strArray = sendNOComma.Split(' ');
                int bytebufferLength = strArray.Length;

                for (int i = 0; i < strArray.Length; i++)
                {
                    if (strArray[i] == "")
                    {
                        bytebufferLength--;
                    }
                }
                byte[] byteBuffer = new byte[bytebufferLength];

                int ii = 0;
                for (int i = 0; i < strArray.Length; i++)
                {
                    Byte[] bytesOfStr = Encoding.Default.GetBytes(strArray[i]);
                    int decNum = 0;
                    if (strArray[i] == "")
                    {
                        continue;
                    }
                    else
                    {
                        decNum = Convert.ToInt32(strArray[i], 16); //atrArray[i] == 12时，temp == 18 
                    }

                    try    //防止输错，使其只能输入一个字节的字符
                    {
                        byteBuffer[ii] = Convert.ToByte(decNum);
                    }
                    catch (Exception)
                    {
                        MessageBox.Show("字节越界，请逐个字节输入！", "Error");
                        return;
                    }
                    ii++;
                }
                serialPort1.Write(byteBuffer, 0, byteBuffer.Length);
            }
            else
            {
                MessageBox.Show("请打开串口");
            }
        }
        string[] s = new string[5];
        byte Claw_state;
        private void robot_control()
        {
            string SendBuf = "";
            byte [][]bb=new byte[5][];
            int sum;

            switch (button)
            { 
                case(BUTTON.SHAKING_HANDS):
                SendBuf= "FF FF 01 11 00 0D 00 00 00 00 00 00 00 00 00 00 00 00 00 1F";
                break;

                case(BUTTON.SET_ROBOT_SPEED):
                string_deal(SetSpeedtxtBox.Text);
                if (s.Length != 3)
                {
                    MessageBox.Show("请输入正确的数据长度");
                    return;
                }
                SendBuf = "FF FF 01 11 00 0D 01 ";
                sum = 1 + 17 + 13 + 1;
                bb[0]= BitConverter.GetBytes(Convert.ToSingle(s[0]));
                bb[1]= BitConverter.GetBytes(Convert.ToSingle(s[1]));
                bb[2]= BitConverter.GetBytes(Convert.ToSingle(s[2]));
                for (int i = 0; i < 3; i++)   
                {
                    for(int j=0;j<4;j++)
                    {
                        SendBuf += bb[i][j].ToString("X2");  //16进制显示  
                        SendBuf += " ";
                        sum+=bb[i][j];
                    }
                }
                SendBuf+=(sum%255).ToString("X2");
                break;

                case (BUTTON.READ_ROBOT_SPEED):
                SendBuf = "FF FF 01 11 00 01 02 15";
                break;
                 
                case(BUTTON.READ_COORDINATE_DATA):
                SendBuf = "FF FF 01 11 00 01 03 16";
                break;

                case(BUTTON.CLEAR_COORDINATE_DATA):
                SendBuf = "FF FF 01 11 00 01 05 18";
                break;


                case(BUTTON.PLAT_MOVE):
                string_deal(SetPlatxtBox.Text);
                if (s.Length != 1)
                {
                    MessageBox.Show("请输入正确的数据长度");
                    return;
                }
                sum = 1 + 17 + 5 + 9;
                bb[0] = BitConverter.GetBytes(Convert.ToSingle(s[0]));
                SendBuf = "FF FF 01 11 00 05 09 ";
                for (int i = 0; i < 1; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        SendBuf += bb[i][j].ToString("X2");  //16进制显示  
                        SendBuf += " ";
                        sum += bb[i][j];
                    }
                }
                SendBuf += (sum % 255).ToString("X2");
                break;

                case(BUTTON.READ_PLAT):
                SendBuf = "FF FF 01 11 00 01 0A 1D";
                break;

                case(BUTTON.SET_ARM_TOTAL):
                string_deal(SetArmtxtBox.Text);
                if (s.Length != 4)
                {
                    MessageBox.Show("请输入正确的数据长度");
                    return;
                }
                sum = 1 + 17 + 17 + 7;
                bb[0] = BitConverter.GetBytes(Convert.ToSingle(s[0]));
                bb[1] = BitConverter.GetBytes(Convert.ToSingle(s[1]));
                bb[2] = BitConverter.GetBytes(Convert.ToSingle(s[2]));
                bb[3] = BitConverter.GetBytes(Convert.ToSingle(s[3]));
                SendBuf = "FF FF 01 11 00 11 07 ";
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        SendBuf += bb[i][j].ToString("X2");  //16进制显示  
                        SendBuf += " ";
                        sum += bb[i][j];
                    }
                }
                SendBuf += (sum % 255).ToString("X2");
                break;

                case(BUTTON.READ_ARM_TOTAL):
                SendBuf = "FF FF 01 11 00 01 08 1B";
                break;

                case(BUTTON.SET_WRIST):
                string_deal(SetWristText.Text);             //这些TextBox的name不能太长
                if (s.Length != 1)
                {
                    MessageBox.Show("请输入正确的数据长度");
                    return;
                }
                sum = 1 + 17 + 5 + 11;
                bb[0] = BitConverter.GetBytes(Convert.ToSingle(s[0]));
                SendBuf = "FF FF 01 11 00 05 0B ";
                for (int i = 0; i < 1; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        SendBuf += bb[i][j].ToString("X2");  //16进制显示  
                        SendBuf += " ";
                        sum += bb[i][j];
                    }
                }
                SendBuf += (sum % 255).ToString("X2");
                break;
 
                case(BUTTON.READ_WRIST):
                SendBuf = "FF FF 01 11 00 01 0C 1F";
                break;

                case(BUTTON.SET_CLAW):
                    switch(Claw_state)
                    {
                        case (0): SendBuf = "FF FF 01 11 00 02 06 00 1A"; break;
                        case (1): SendBuf = "FF FF 01 11 00 02 06 01 1B"; break;
                        case (2): SendBuf = "FF FF 01 11 00 02 06 02 1C"; break;
                    }

                break;
            }
            Array.Clear(bb,0,bb.Length);//清除数组中的内容
            Array.Clear(s, 0, s.Length);
            SendBuftxtBox.Text = SendBuf;
            serialPort1_sendStr(SendBuf);
        }
       void string_deal(string str)
        {
           str = new System.Text.RegularExpressions.Regex("[\\s]+").Replace(str, " ");
           if (str == "")
           {
               MessageBox.Show("请添入数据");
               return;
           }
           if (str.EndsWith(" "))
           {
               MessageBox.Show("请删除数据后的空格");
               return;
           }
               s=str.Split(' ');
        }




        private void ShakeHandsbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.SHAKING_HANDS;
            robot_control();
        }

        private void SetSpeedbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_ROBOT_SPEED;
            robot_control();
        }

        private void ReadSpeedbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.READ_ROBOT_SPEED;
            robot_control();
        }

        private void ReadGlobalCoordinatebtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.READ_COORDINATE_DATA;
            robot_control();
        }

        private void ClearGlobalCoordinatebtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.CLEAR_COORDINATE_DATA;
            robot_control();
        }

        private void SetPlatbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.PLAT_MOVE;
            robot_control();
        }

        private void ReadPlatbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.READ_PLAT;
            robot_control();
        }

        private void SetArmbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_ARM_TOTAL;
            robot_control();
        }

        private void ReadArmbtn_Click(object sender, EventArgs e)
        {
            button = BUTTON.READ_ARM_TOTAL;
            robot_control();
        }

        private void SetWristxtBox_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_WRIST;
            robot_control();
        }

        private void ReadWristxtBox_Click(object sender, EventArgs e)
        {
            button = BUTTON.READ_WRIST;
            robot_control();
        }

        private void Claw_btn1_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_CLAW;
            Claw_state = 0;
            robot_control();
        }

        private void Claw_btn2_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_CLAW;
            Claw_state = 1;
            robot_control();
        }

        private void Claw_btn3_Click(object sender, EventArgs e)
        {
            button = BUTTON.SET_CLAW;
            Claw_state = 2;
            robot_control();
        }












        


    }
}

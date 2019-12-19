using System;
using System.IO;
using System.Reflection;
using OpenQA.Selenium;
using OpenQA.Selenium.Chrome;
using System.Collections.Generic;
using System.Collections.ObjectModel;

namespace NishinoLibrary
{
    class Selenium
    {

        static private ChromeDriver chrome;
        static private ChromeOptions options;

        static private int waittime;

        public Selenium()
        {
            options = new ChromeOptions();
            waittime = 500;
        }

        public void SettingTime(int time)
        {
            if (time >= 500) waittime = time;
            else Console.WriteLine("0.5秒以下を設定することはできません。");
        }


        //ブラウザを表示しない設定を行うメソッド
        public void HideOption()
        {
            Option("--headless");
        }


        //ブラウザを開く前にオプションを入れる
        public void Option(string op)
        {
            options.AddArgument(op);
        }



        //クローリングを開始
        public void CreateBrowser()
        {
            chrome = new ChromeDriver(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location), options);
        }


        //Accessメソッド
        public void Access(string url)
        {
            chrome.Url = url;
            //一秒間（1000ミリ秒）停止する
            System.Threading.Thread.Sleep(waittime);
        }

        


        public List<string> ReturnElementString(string base_tag, string tag, string word)
        {
            //指定タグのエレメントを持つ一覧を検索
            ReadOnlyCollection<IWebElement> elements = chrome.FindElements(By.TagName(base_tag));
            List<string> sort_string = new List<string> { };
            for (int i = 0; i < elements.Count; i++)
            {
                if (elements[i].GetAttribute(tag).Contains(word))
                {
                    sort_string.Add(elements[i].GetAttribute(tag));
                }
            }
            return sort_string;
        }


        public void OutputTextbox(string input_word,int box_num)
        {
            //chrome.FindElement(By.ClassName("form-control")).SendKeys(input_word);
            chrome.FindElements(By.ClassName("form-control"))[box_num].SendKeys(input_word);
        }

        //Clickメソッド(工事中)
        public void Click(string kind_element)
        {
            chrome.FindElement(By.Id(kind_element)).Click();
        }


        public string GetPageSource()
        {
            return chrome.PageSource;
        }

        //更新
        public void RefreshPage()
        {
            chrome.Navigate().Refresh();
        }


        //Quitメソッド
        public void Quit()
        {
            chrome.Quit();
        }



        public void TestChrome()
         {
            // ChromeDriverオブジェクトを生成します。
            var chrome = new ChromeDriver(Path.GetDirectoryName(Assembly.GetEntryAssembly().Location));
            // URLに移動します。
            chrome.Url = @"http://www.google.com/";
            // すぐ終了しないよう、キーが押されるまで待機します。
            Console.ReadKey();
            // ブラウザを閉じます。
            chrome.Quit();
        }
}
}







using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using NishinoLibrary;
using System.IO;

namespace Superme
{
    public partial class Form1 : Form
    {
        //other
        static Selenium sel;

        public Form1()
        {
            InitializeComponent();
        }

        //ページロード時の処理
        private void Form1_Load(object sender, EventArgs e)
        {
            //Timerメソッドを生成
            timer1.Interval = 200;//200ms
            timer1.Tick += new EventHandler(timer1_Tick);
            timer1.Enabled = true;
            NowTime.Text = DateTime.Now.ToString("HH: mm:ss");

            SeleniumTimer.Interval = 100;//1000ms
            SeleniumTimer.Tick += new EventHandler(SeleniumTimer_Tick);
            SeleniumTimer.Enabled = false;


            // ChromeDriverオブジェクトを生成
            sel = new Selenium();
            sel.CreateBrowser();
            sel.Access(@"file:///C:/Users/ynishino/Desktop/Superme/Superme_110033.html");


            FirstNameTextBox.Text = "Yuki";
            LastNameTextBox.Text = "Nishino";
            EmailTextBox.Text = @"nishino23210@gmail.com";
            TelTextBox.Text = "08046877867";

        }



        //100msごとに定期発生させる処理
        private void timer1_Tick(object sender, EventArgs e)
        {
            //表示時刻を更新
            NowTime.Text = DateTime.Now.ToString("HH:mm:ss");
            //if (DateTime.Now.ToString("HHmmss") == "105945")
            //{
            //    Now.Text = "保存中";
            //    SeleniumTimer.Enabled = true;
            //}
            //if (DateTime.Now.ToString("HHmmss") == "110200")
            //{
            //    Now.Text = "保存完了";
            //    SeleniumTimer.Enabled = false;
            //}


        }

        //Selenium実行中に発動させる処理
        private void SeleniumTimer_Tick(object sender, EventArgs e)
        {
            //抽選サイトがクローズしているかを判定
            if (sel.GetPageSource().Contains("クローズ"))
            {
                //ページをリフレッシュ
                sel.RefreshPage();
            }
            else
            {
                SeleniumTimer.Enabled = false;
                Now.Text = "入力中";
                //			<input name="c9d8c800e05378825bc8a952add0fa69" placeholder="your name" size="50" maxlength="25" class="form-control" autocomplete="off" value="">
                sel.OutputTextbox(FirstNameTextBox.Text+LastNameTextBox.Text, 0);
                sel.OutputTextbox(EmailTextBox.Text, 1);
                sel.OutputTextbox(TelTextBox.Text, 2);
                sel.Click("area_tokyo");
                sel.Click("agree");
                Now.Text = "入力完了";
            }
            //None 

        }


        //使っていないメソッド。HTMLを保存するやつ
        private void GetHtml()
        {
            //とりあえずHTMLを保存する処理を実行する
            string html_get_dir = @"C:\Users\ynishino\Desktop\superme\";
            string save_name = "Superme_" + DateTime.Now.ToString("HHmmss") + ".html";
            string filePath = html_get_dir + save_name;
            StreamWriter sw = new StreamWriter(filePath, false, Encoding.UTF8);
            sel.RefreshPage();
            sw.Write(sel.GetPageSource());
            sw.Close();
        }


        private void RunButton_Click(object sender, EventArgs e)
        {
            Now.Text = "実行中";
            SeleniumTimer.Enabled = true;
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            Now.Text = "待機中";
            SeleniumTimer.Enabled = false;
        }

        private void TextBox4_TextChanged(object sender, EventArgs e)
        {

        }
    }
}



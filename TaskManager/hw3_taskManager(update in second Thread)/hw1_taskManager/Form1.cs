using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Diagnostics;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hw1_taskManager
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            // Заполнение ListView1
            ColumnHeader c1 = new ColumnHeader(6);
            c1.Width = 150;
            c1.Text = "Process";
            this.listView1.Columns.Add(c1);

            ColumnHeader c2 = new ColumnHeader(6);
            c2.Width = 70;
            c2.Text = "PriorityClass";
            this.listView1.Columns.Add(c2);

            ColumnHeader c3 = new ColumnHeader(6);
            c3.Width = 70;
            c3.Text = "BasePriority";
            this.listView1.Columns.Add(c3);

            ColumnHeader c4 = new ColumnHeader(6);
            c4.Width = 120;
            c4.Text = "Start";
            this.listView1.Columns.Add(c4);

            ColumnHeader c5 = new ColumnHeader(6);
            c5.Width = 80;
            c5.Text = "Count Modules";
            this.listView1.Columns.Add(c5);

            ColumnHeader c6 = new ColumnHeader(6);
            c6.Width = 80;
            c6.Text = "Count Threads";
            this.listView1.Columns.Add(c6);

            ColumnHeader c7 = new ColumnHeader(6);
            c7.Width = 50;
            c7.Text = "Id";
            this.listView1.Columns.Add(c7);

            this.listView1.View = View.Details;
        }

        void startThread()
        {
            while (true)
            {
                Action A = () =>
                {
                    Process[] P = Process.GetProcesses(".");
                    for (int i = 0; i < this.listView1.Items.Count; i++)
                    {
                        bool isClose = true;
                        foreach (Process p in P)
                        {
                            if (this.listView1.Items[i].SubItems[6].Text == p.Id.ToString())
                                isClose = false;
                        }
                        if (isClose)
                            this.listView1.Items.RemoveAt(i);
                    }
                    foreach (Process p in P)
                    {
                        String PriorityClass = "N/A";
                        try
                        {
                            PriorityClass = p.PriorityClass.ToString();
                        }
                        catch { }
                        int BasePriority = -1;
                        try
                        {
                            BasePriority = p.BasePriority;
                        }
                        catch { }
                        String StartTime = "N/A";
                        try
                        {
                            StartTime = p.StartTime.ToString();

                        }
                        catch { }
                        int CountModules = 0;
                        try
                        {
                            CountModules = p.Modules.Count;
                        }
                        catch { }
                        int CountThreads = 0;
                        try
                        {
                            CountThreads = p.Threads.Count;
                        }
                        catch { }
                        bool isNew = true;
                        for (int i = 0; i < this.listView1.Items.Count; i++)
                        {
                            if (this.listView1.Items[i].SubItems[6].Text == p.Id.ToString())
                            {
                                isNew = false;
                                if (CountModules.ToString() != this.listView1.Items[i].SubItems[4].Text)
                                    this.listView1.Items[i].SubItems[4].Text = CountModules.ToString();
                                if (CountThreads.ToString() != this.listView1.Items[i].SubItems[5].Text)
                                    this.listView1.Items[i].SubItems[5].Text = CountThreads.ToString();
                                if (StartTime != this.listView1.Items[i].SubItems[3].Text)
                                    this.listView1.Items[i].SubItems[3].Text = StartTime;
                                if (BasePriority.ToString() != this.listView1.Items[i].SubItems[2].Text)
                                    this.listView1.Items[i].SubItems[2].Text = BasePriority.ToString();
                                if (PriorityClass != this.listView1.Items[i].SubItems[1].Text)
                                    this.listView1.Items[i].SubItems[1].Text = PriorityClass.ToString();
                            }
                        }
                        if (isNew)
                        {
                            ListViewItem lvi = new ListViewItem(p.ProcessName);
                            lvi.SubItems.Add(PriorityClass);
                            lvi.SubItems.Add(p.BasePriority.ToString());
                            lvi.SubItems.Add(StartTime);
                            lvi.SubItems.Add(CountModules.ToString());
                            lvi.SubItems.Add(CountThreads.ToString());
                            lvi.SubItems.Add(p.Id.ToString());
                            this.listView1.Items.Add(lvi);
                        }
                        this.listView1.Sorting = SortOrder.Ascending;
                    }
                };
                this.listView1.Invoke(A);
                Thread.Sleep(10000);
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Thread T = new Thread(startThread);
            T.IsBackground = true;
            T.Start();
        }
        void deleteProcess()
        {

            ListViewItem lvi;
            try
            {
                lvi = this.listView1.Items[this.listView1.SelectedIndices[0]];
            }
            catch
            {
                MessageBox.Show("Для удаления необходим 1 элемент", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
                Process P = Process.GetProcessById(Convert.ToInt32(lvi.SubItems[6].Text));
                if (P != null)
                    P.Kill();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            this.deleteProcess();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.listView1.Items.Clear();
        }

        private void удалитьToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ListViewItem lvi;
            try
            {
                lvi = this.listView1.Items[this.listView1.SelectedIndices[0]];
            }
            catch
            {
                MessageBox.Show("Для удаления необходим 1 элемент", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            this.deleteProcess();
        }

        private void потокиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ListViewItem lvi;
            try
            {
                lvi = this.listView1.Items[this.listView1.SelectedIndices[0]];
            }
            catch
            {
                MessageBox.Show("необходим 1 элемент", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            Form3 F3 = new Form3();
            try
            {
                Process P = Process.GetProcessById(Convert.ToInt32(this.listView1.SelectedItems[0].SubItems[6].Text));
                foreach (ProcessThread pt in P.Threads)
                {
                    lvi = new ListViewItem(pt.Id.ToString());
                    lvi.SubItems.Add(pt.StartTime.ToString());
                    lvi.SubItems.Add(pt.CurrentPriority.ToString());
                    lvi.SubItems.Add(pt.ThreadState.ToString());
                    F3.listView1.Items.Add(lvi);
                }
                F3.ShowDialog();
            }
            catch (Exception exp)
            {
               MessageBox.Show("Error: " + exp.Message);
            }
        }

        private void модулиToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ListViewItem lvi;
            try
            {
                lvi = this.listView1.Items[this.listView1.SelectedIndices[0]];
            }
            catch
            {
                MessageBox.Show("необходим 1 элемент", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            Form2 F2 = new Form2();
            try
            {
                Process P = Process.GetProcessById(Convert.ToInt32(lvi.SubItems[6].Text));
                foreach (ProcessModule pm in P.Modules)
                {
                    lvi = new ListViewItem(pm.ModuleName);
                    lvi.SubItems.Add(pm.BaseAddress.ToString());
                    lvi.SubItems.Add(pm.ModuleMemorySize.ToString());
                    lvi.SubItems.Add(pm.FileName);
                    F2.listView1.Items.Add(lvi);
                }
                F2.ShowDialog();
            }
            catch (Exception exp)
            {
                MessageBox.Show("Error: " + exp.Message);
            }
        }

        private void изменитьПриоритетToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ListViewItem lvi;
            try
            {
                lvi = this.listView1.Items[this.listView1.SelectedIndices[0]];
            }
            catch
            {
                MessageBox.Show("необходим 1 элемент", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            try
            {
                Form4 F4 = new Form4();
                F4.comboBox1.Text = lvi.SubItems[1].Text;
                DialogResult res = F4.ShowDialog();
                if (res == DialogResult.OK)
                {
                    Process P = Process.GetProcessById(Convert.ToInt32(lvi.SubItems[6].Text));
                    switch (F4.comboBox1.Text)
                    {
                        case "AboveNormal":
                            P.PriorityClass = ProcessPriorityClass.AboveNormal;
                            break;
                        case "BelowNormal":
                            P.PriorityClass = ProcessPriorityClass.BelowNormal;
                            break;
                        case "High":
                            P.PriorityClass = ProcessPriorityClass.High;
                            break;
                        case "Idle":
                            P.PriorityClass = ProcessPriorityClass.Idle;
                            break;
                        case "Normal":
                            P.PriorityClass = ProcessPriorityClass.Normal;
                            break;
                        case "RealTime":
                            P.PriorityClass = ProcessPriorityClass.RealTime;
                            break;
                        default: MessageBox.Show("Указан неверный приоритет", "Ошибка", MessageBoxButtons.OK, MessageBoxIcon.Error);
                            break;
                    }
                }
            }
            catch (Exception exp)
            {
                MessageBox.Show("Error: " + exp.Message);
            }
        }
    }
}

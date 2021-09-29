using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace hw1_taskManager
{
    public partial class Form3 : Form
    {
        public Form3()
        {
            InitializeComponent();

            // Заполнение ListView1
            ColumnHeader c1 = new ColumnHeader(6);
            c1.Width = 70;
            c1.Text = "Thread";
            this.listView1.Columns.Add(c1);

            ColumnHeader c2 = new ColumnHeader(6);
            c2.Width = 120;
            c2.Text = "StartTime";
            this.listView1.Columns.Add(c2);

            ColumnHeader c3 = new ColumnHeader(6);
            c3.Width = 70;
            c3.Text = "CurrentPriority";
            this.listView1.Columns.Add(c3);

            ColumnHeader c4 = new ColumnHeader(6);
            c4.Width = 120;
            c4.Text = "ThreadState";
            this.listView1.Columns.Add(c4);

            this.listView1.View = View.Details;
        }
    }
}

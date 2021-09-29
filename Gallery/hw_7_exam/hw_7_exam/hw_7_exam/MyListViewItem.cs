using Microsoft.Win32;
using System;
using System.Windows.Media.Imaging;

namespace hw_7_exam
{
    class MyListViewItem
    {
        public BitmapImage Image { get; set; }
        public String Name { get; set; }
        public String Parent { get; set; }

        static BitmapImage folder_open = new BitmapImage(new Uri(@"Resources/folder_open.ico", UriKind.Relative));

        public MyListViewItem(String path, String parent)
        {
            this.Image = new BitmapImage(new Uri(path));
            this.Parent = parent;
            this.Name = path;
        }
        public MyListViewItem(String path)
        {
            this.Image = folder_open;
            this.Parent = null;
            this.Name = path;
        }
    }
}
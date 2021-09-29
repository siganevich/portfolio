using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace hw_7_exam
{
    /// <summary>
    /// Логика взаимодействия для MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private BitmapImage folder_close = new BitmapImage(new Uri(@"Resources/folder_close.ico", UriKind.Relative));
        private BitmapImage folder_open = new BitmapImage(new Uri(@"Resources/folder_open.ico", UriKind.Relative));
        private List<MyListViewItem> CollectionImages1 = new List<MyListViewItem>();
        private List<MyListViewItem> CollectionImages2 = new List<MyListViewItem>();
        private int selectedIndex;
        public MainWindow()
        {
            InitializeComponent();

            String[] disks = Directory.GetLogicalDrives();
            for (int i = 0; i < disks.Length; i++)
            {
                TreeViewItem item = new TreeViewItem();
                item.Header = disks[i];
                item.Tag = folder_close;
                item.Items.Add(null);
                item.Expanded += FolderExpanded;
                item.Collapsed += FolderCollapsed;
                treeView1.Items.Add(item);
            }
        }
        private void FolderExpanded(object sender, RoutedEventArgs e)
        {
            try
            {
                TreeViewItem item = (TreeViewItem)sender;
                if (item.Items.Count != 1 || item.Items[0] != null)
                    return;
                item.Items.Clear();
                String[] dirs = Directory.GetDirectories(item.Header.ToString());
                foreach (String d in dirs)
                {
                    TreeViewItem it = new TreeViewItem();
                    it.Header = d;
                    it.Tag = folder_close;
                    item.Items.Add(it);
                    it.Expanded += FolderExpanded;
                    it.Collapsed += FolderCollapsed;
                    it.Items.Add(null);
                }
                item.Tag = folder_open;
            }
            catch (Exception exp)
            {
                MessageBox.Show("Нет доступа!");
            }
        }
        private void FolderCollapsed(object sender, RoutedEventArgs e)
        {
            TreeViewItem item = (TreeViewItem)sender;
            item.Tag = folder_close;
        }
        private void fillCollection1(String path)
        {
            // Заполнение коллекции изображений единичной папки

            var files = Directory.EnumerateFiles(path);
            foreach (MyListViewItem myLVI in this.CollectionImages1)
                if (myLVI.Parent == path)
                    return;
            this.CollectionImages1.Clear();
            foreach (String f in files)
                if (f.Contains(".png") || f.Contains(".jpg") || f.Contains(".jpeg") || f.Contains(".bmp") || f.Contains(".gif"))
                    this.CollectionImages1.Add(new MyListViewItem(f, path));
            fillListView3();
        }
        //private void fillCollection2(String path)
        //{
        //    // Заполнение коллекции изображений всей галлереи
        //    fillListView1();
        //}
        private void fillListView3()
        {
            // Заполнение листа с изображениями выбранной папки

            listView3.Items.Clear();
            foreach (MyListViewItem myLVI in this.CollectionImages1)
                listView3.Items.Add(myLVI);
        }
        private void fillListView1()
        {
            // Запонение листа с изображениями галлереи

            listView1.Items.Clear();
            foreach (MyListViewItem myLVI in this.CollectionImages2)
                listView1.Items.Add(myLVI);
        }
        private void treeView1_SelectedItemChanged(object sender, RoutedPropertyChangedEventArgs<object> e)
        {
            try
            {
                TreeViewItem item = (TreeViewItem)treeView1.SelectedItem;
                item.Tag = folder_open;
                listView2.Items.Add(new MyListViewItem(item.Header.ToString()));
                fillCollection1(item.Header.ToString());
            }
            catch (Exception exp)
            {
                MessageBox.Show("Нет доступа!");
            }
        }
        private void listView1_Selected(object sender, RoutedEventArgs e)
        {
            if (listView1.Items.Count != 0 && listView1.SelectedItem != null)
            {
                this.selectedIndex = listView1.SelectedIndex;
                lookImage();
            }
        }
        private void lookImage()
        {
            try
            {
                image1.Source = this.CollectionImages2[selectedIndex].Image;
            }
            catch
            {
                image1.Source = null;
            }
        }
        private void ButtonDelete_Click(object sender, RoutedEventArgs e)
        {
            if (listView2.SelectedIndex == -1)
                MessageBox.Show("Не выбран элемент");
            else
            {
                if (this.CollectionImages1.Count != 0 && ((MyListViewItem)CollectionImages1[0]).Parent == ((MyListViewItem)listView2.SelectedItem).Name)
                {
                    this.CollectionImages1.Clear();
                    this.listView3.Items.Clear();
                }
                listView2.Items.RemoveAt(listView2.SelectedIndex);
            }
        }
        private void ButtonBack_Click(object sender, RoutedEventArgs e)
        {
            if (image1.Source != null)
            {
                this.selectedIndex--;
                listView1.SelectedIndex--;
                if (selectedIndex < 0)
                {
                    this.selectedIndex = CollectionImages2.Count - 1;
                    listView1.SelectedIndex = this.selectedIndex;
                }
                lookImage();
            }
        }
        private void ButtonForward_Click(object sender, RoutedEventArgs e)
        {
            if (image1.Source != null)
            {
                this.selectedIndex++;
                listView1.SelectedIndex++;
                if (selectedIndex == CollectionImages2.Count)
                {
                    this.selectedIndex = 0;
                    listView1.SelectedIndex = this.selectedIndex;
                }
            }
            lookImage();
        }

        private void DeleteImageButton_Click(object sender, RoutedEventArgs e)
        {
            if (listView1.SelectedIndex == -1)
                MessageBox.Show("Не выбран элемент");
            else
            {
                this.CollectionImages2.Remove((MyListViewItem)listView1.SelectedItem);
                fillListView1();
                label1.Content = "Всего картинок - " + this.CollectionImages2.Count;
                lookImage();
            }
        }

        private void listView2_Selected(object sender, RoutedEventArgs e)
        {
            if (listView2.SelectedItem != null)
                fillCollection1(((MyListViewItem)listView2.SelectedItem).Name);
        }

        private void listView3_Selected(object sender, RoutedEventArgs e)
        {
            if ((MyListViewItem)listView3.SelectedItem != null)
            {
                this.CollectionImages2.Add((MyListViewItem)listView3.SelectedItem);
                fillListView1();
                label1.Content = "Всего картинок - " + this.CollectionImages2.Count;
            }
        }
    }
    class HeaderConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            try
            {
                String tmp = value.ToString();
                int index = tmp.LastIndexOf("\\");
                if (tmp[tmp.Length-1] != '\\')
                    tmp = tmp.Remove(0, index + 1);
                return tmp;
            }
            catch (Exception exp)
            {
                return value;
            }
        }
        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            return value;
        }
    }
}

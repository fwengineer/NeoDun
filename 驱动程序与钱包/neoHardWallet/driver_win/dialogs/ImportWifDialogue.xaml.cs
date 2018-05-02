﻿using System;
using System.Collections.Generic;
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
using System.Windows.Shapes;

namespace driver_win.dialogs
{
    /// <summary>
    /// ImportWifDialogue.xaml 的交互逻辑
    /// </summary>
    public partial class ImportWifDialogue : Window
    {
        private DriverControl driverControl;
        public ImportWifDialogue(DriverControl _driverControl)
        {
            InitializeComponent();

            driverControl = _driverControl;
        }

        private void Window_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            this.DragMove();
        }

        private async void btn_Add(object sender, RoutedEventArgs e)
        {
            string result = await driverControl.AddAddressByWif(this.label_Wif.Text.ToString());
            if (result == "suc")
            {
                this.Close();
                AddressListDialogue addressListDialogue = new AddressListDialogue(driverControl);
                addressListDialogue.WindowStartupLocation = WindowStartupLocation.CenterOwner;
                addressListDialogue.Owner = this.Owner;
                addressListDialogue.Show();

                MessageDialogue messageDialogue = new MessageDialogue("添加成功");
                messageDialogue.WindowStartupLocation = WindowStartupLocation.CenterOwner;
                messageDialogue.Owner = addressListDialogue;
                messageDialogue.Show(2);
            }
            else
            {
                MessageDialogue messageDialogue = new MessageDialogue(result);
                messageDialogue.WindowStartupLocation = WindowStartupLocation.CenterOwner;
                messageDialogue.Owner = this;
                messageDialogue.Show(2);
            }
        }

        private void Btn_CloseDialogue(object sender, RoutedEventArgs e)
        {
            this.Close();
        }
    }
}

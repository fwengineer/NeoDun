﻿using NeoDun;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using static hhgate.SignMachine;

namespace driver_win
{
    /// <summary>
    /// WindowDriver.xaml 的交互逻辑
    /// </summary>
    public partial class WindowDriver : Window, NeoDun.IWatcher
    {
        public static NeoDun.Signer signer = NeoDun.Signer.Ins;
        public static DriverCtr driverCtr = DriverCtr.Ins;

        public static bool isShowMsg = true;

        //当前选中的地址
        Address selectAddress = new Address();
        //缓存住的密码 
        string str_password = "";
        string str_password2 = "";
        public WindowDriver()
        {
            InitializeComponent();
        }



        #region 所有的页面点击事件
        //显示增加地址的页面
        private void ShowAddPage_click(object sender, RoutedEventArgs e)
        {
            ShowAddAddressPage();
        }
        public void AddAddress_click(object sender,RoutedEventArgs e)
        {
            AddAddress();
        }
        //隐藏添加地址的页面
        public void HideAddPage_click(object sender, RoutedEventArgs e)
        {
            HideAddBox();
        }
        //显示设置页面
        private void ShowSettingPage_click(object sender, RoutedEventArgs e)
        {
            ShowSettingPage();
        }
        //隐藏设置页面
        private void HideSettingPage_click(object sender, RoutedEventArgs e)
        {
            SetSettingConfig();
            HideSettingPage();
        }
        //点击重新连接按钮 
        private void Relink_click(object sender, RoutedEventArgs e)
        {
            LinkSinger();
        }
        //从输入的文本框获取地址
        private void FromText_click(object sender, RoutedEventArgs e)
        {
            driverCtr.PrivateKey2Address_FromText(this.tx_privateKey.Text);
        }
        //从备份获取地址
        private void FromBackup_click(object sender, RoutedEventArgs e)
        {
            driverCtr.PrivateKey2Address_FromBackup();
        }
        //变化地址时缓存点击的地址
        private void Addresslist_SelectionChanged(object sender, RoutedEventArgs e)
        {
            var item = addresslist.SelectedItem as NeoDun.Address;
            if (item == null)
                return;
            selectAddress.AddressText = item.AddressText;
            selectAddress.type = item.type;
        }
        //点选密码
        private void PasswordListButtonClick(object sender, RoutedEventArgs e)
        {
            var button = sender as Button;

            //将点击的按钮对应成数字 a对应1
            int i = (int)button.Name[0] - 96;
            str_password += i.ToString();
            //str_password2 += " * ";
            str_password2 += i.ToString();
            this.pwLabel.Content = str_password2;
            if (str_password.Length < 6)
            {
                return;
            }
            driverCtr.SetOrConfirmPassword(str_password);
            LockPwPage();
            //清空缓存住的选择的密码
            str_password = "";
            str_password2 = "";
        }
        //点击备份
        private void Backup_click(object sender, RoutedEventArgs e)
        {
            BackUpPrivateKey();
        }
        //删除地址
        private void DeleteAddress_click(object sender, RoutedEventArgs e)
        {
            if (selectAddress == null|| selectAddress.AddressText == null)
                return;
            string str_addressType = selectAddress.type.ToString();
            string str_addressText = selectAddress.AddressText;
            if (string.IsNullOrEmpty(str_addressType) || string.IsNullOrEmpty(str_addressText))
            {
                ErrorMsgShow("请选择要删除的地址", "错误");
                return;
            }
            DeleteAddress();
            selectAddress.AddressText = null;
        }
        //隐藏消息框
        private void HideMessagePage_click(object sender, RoutedEventArgs e)
        {
            HideMessagePage();
        }
        //重置密码
        private void ResetPassword_click(object sender, RoutedEventArgs e)
        {
            RestPassword();
        }

        #endregion



        #region 所有页面显示||隐藏的操作
        //初始页面
        private void InitPage()
        {
            HideAllPage();
            this.isLink.Content = "未连接";
            this.btn_relink.Visibility = Visibility.Visible;
            label_unlink.Visibility = Visibility.Visible;
        }
        //关闭所有页面
        private void HideAllPage()
        {
            //this.btn_relink.Visibility = Visibility.Collapsed;
            this.label_unlink.Visibility = Visibility.Collapsed;
            this.listBox.Visibility = Visibility.Collapsed;
            this.addBox.Visibility = Visibility.Collapsed;
            this.pwBox.Visibility = Visibility.Collapsed;
            this.msgBox.Visibility = Visibility.Collapsed;
            this.settingBox.Visibility = Visibility.Collapsed;
        }
        //显示提示框
        private void ShowMessagePage(string _msg, bool _bool = true)
        {
            this.msgBox.Visibility = Visibility.Visible;
            this.msgBox_label.Content = _msg;
            this.msgBox_cancel.Visibility = _bool ? Visibility.Visible : Visibility.Collapsed;
        }
        //隐藏提示框
        private void HideMessagePage()
        {
            this.msgBox.Visibility = Visibility.Collapsed;
        }
        //显示重新连接按钮
        private void ShowRelinkBtn()
        {
            this.btn_relink.Visibility = Visibility.Visible;
        }
        //隐藏重新连接按钮
        private void HideRelinkBtn()
        {
            this.btn_relink.Visibility = Visibility.Collapsed;
        }
        //显示输入密码页面
        private void ShowPwPage()
        {
            HideAllPage();
            UnLockPwPage();
            UnActiveButton();
            this.pwBox.Visibility = Visibility.Visible;
        }
        //关闭输入密码页面
        private void HidePwPage()
        {
            ActiveButton();
            this.pwBox.Visibility = Visibility.Collapsed;
        }
        //显示未连接页面
        private void ShowUnliklabel()
        {
            HideAllPage();
            this.btn_relink.Visibility = Visibility.Visible;
            this.label_unlink.Visibility = Visibility.Visible;
        }
        //显示连接后地址页面
        private void ShowAddressPage()
        {
            //HideAllPage();
            this.listBox.Visibility = Visibility.Visible;
        }
        //显示增加地址页面
        private void ShowAddAddressPage()
        {
            HideAllPage();
            this.listBox.Visibility = Visibility.Visible;
            this.addBox.Visibility = Visibility.Visible;
        }
        //隐藏增加地址页面
        private void HideAddBox()
        {
            this.addBox.Visibility = Visibility.Collapsed;
        }
        //显示设置页面
        private void ShowSettingPage()
        {
            HideAllPage();
            this.listBox.Visibility = Visibility.Visible;
            this.settingBox.Visibility = Visibility.Visible;
        }
        //隐藏设置页面
        private void HideSettingPage()
        {
            this.settingBox.Visibility = Visibility.Collapsed;
        }
        //功能按键激活
        private void ActiveButton()
        {
            this.btn_showaddpage.IsEnabled = true;
            this.btn_backup.IsEnabled = true;
            this.btn_deleteaddress.IsEnabled = true;
            this.btn_showsettingpage.IsEnabled = true;
        }
        //功能按键失效
        private void UnActiveButton()
        {
            this.btn_showaddpage.IsEnabled = false;
            this.btn_backup.IsEnabled = false;
            this.btn_deleteaddress.IsEnabled = false;
            this.btn_showsettingpage.IsEnabled = false;
        }
        #endregion

        void IWatcher.OnRecv(Message recv, Message src)
        {

        }
        void IWatcher.OnSend(Message send, bool needBack)
        {
        }
        private void Window_Activated(object sender, EventArgs e)
        {

        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            UInit();
            signer.Stop();
        }
        private void Window_Loaded(object sender, RoutedEventArgs e)
        {
            DriverS.Init();
            Init();
            InitPage();
            signer.Start(this);


            //检测钱包有没有断开连接
        }

        private void Init()
        {
            //初始化各种委托     ps：验证密码的委托在方法里动态赋值
            driverCtr.getAddresslistEventHandlerCallBack += GetAddressCallBack;
            driverCtr.linkSingerEventHandlerCallBack += LinkSingerCallBack;
            driverCtr.getSiggerInfoEventHandlerCallBack += GetSingerInfoCallBack;
            driverCtr.isNeedConfirmPasswordEventHandlerCallBack += NeedConfirmPassword;
            driverCtr.confirmResetPasswordEventHandlerCallBack += NeedConfirmPassword;
            driverCtr.setPasswordEventHandlerCallBack += NeedConfirmPassword;
            driverCtr.confirmPasswordfaildEventHandlerCallBack += ConfirmPasswordCallBack;
            driverCtr.privateKey2AddressEventHandlerCallBack += PrivateKey2AddressCallBack;
            driverCtr.setSetingInfoEventHandlerCallBack += SetSettingConfigCallBack;
            driverCtr.errorEventHandlerCallBack += ErrorMsgShow;

            hhgate.CustomServer.BeginServer();

            //打开驱动页面后尝试连接签名机
            LinkSinger();
            UnActiveButton();
        }
        private void UInit()
        {
            //解绑各种委托
            driverCtr.getAddresslistEventHandlerCallBack -= GetAddressCallBack;
            driverCtr.linkSingerEventHandlerCallBack -= LinkSingerCallBack;
            driverCtr.getSiggerInfoEventHandlerCallBack -= GetSingerInfoCallBack;
            driverCtr.isNeedConfirmPasswordEventHandlerCallBack -= NeedConfirmPassword;
            driverCtr.confirmResetPasswordEventHandlerCallBack -= NeedConfirmPassword;
            driverCtr.setPasswordEventHandlerCallBack -= NeedConfirmPassword;
            driverCtr.confirmPasswordfaildEventHandlerCallBack -= ConfirmPasswordCallBack;
            driverCtr.errorEventHandlerCallBack -= ErrorMsgShow;
            driverCtr.privateKey2AddressEventHandlerCallBack -= PrivateKey2AddressCallBack;
            driverCtr.setSetingInfoEventHandlerCallBack -= SetSettingConfigCallBack;
            driverCtr.errorEventHandlerCallBack -= ErrorMsgShow;
        }

        private void ClearCache()
        {
            this.addresslist.Items.Clear();
            str_password = "";
        }

        //锁住密码页面的按键
        private void LockPwPage()
        {
            this.passwordList.IsEnabled = false;
        }
        //解锁密码页面的按键
        private void UnLockPwPage()
        {
            this.passwordList.IsEnabled = true;
        }

        //连接签名机
        private void LinkSinger()
        {
            driverCtr.LinkSinger();
        }
        private void LinkSingerCallBack(string _label, Visibility _isShow,bool _islink)
        {
            this.isLink.Content = _label;
            this.btn_relink.Visibility = _isShow;
            if (!_islink)
            {
                HideAllPage();
                ClearCache();
            }
        }

        //获取签名机配置回掉
        private void GetSingerInfoCallBack(string _str, MyJson.JsonNode_Object myjson)
        {
            Dispatcher.Invoke((Action)delegate () {
                //this.pwLabel.Content = _str;
                //显示密码验证的页面
                //ShowPwPage();
                this.c3.IsChecked = myjson["新增地址时是否要密码验证"] as MyJson.JsonNode_ValueNumber;
                this.c4.IsChecked = myjson["删除地址是否要密码验证"] as MyJson.JsonNode_ValueNumber;
                this.c5.IsChecked = myjson["备份地址是否要密码验证"] as MyJson.JsonNode_ValueNumber;
            });
        }

        //保存设置配置
        private void SetSettingConfig()
        {
            bool[] _bools = { (bool)this.c1.IsChecked , (bool)this.c2.IsChecked , (bool)this.c3.IsChecked,
            (bool)this.c4.IsChecked,(bool)this.c5.IsChecked,(bool)this.c6.IsChecked};
            driverCtr.SetSettingInfo(_bools);
        }

        private void SetSettingConfigCallBack()
        {
            Dispatcher.Invoke((Action)delegate () {
                ErrorMsgShow("设置成功", "提示");
            });
        }
        //需要密码验证
        private void NeedConfirmPassword(string _str)
        {
            Dispatcher.Invoke((Action) delegate() {
                this.pwLabel.Content = _str;
                //显示密码验证的页面
                ShowPwPage();
            });
        }

        //需要密码验证
        private void ConfirmPasswordCallBack()
        {
            Dispatcher.Invoke((Action)delegate () {
                this.pwLabel.Content = "请输入密码";
                //显示密码验证的页面
                ShowPwPage();
                ErrorMsgShow("密码错误", "提示");
            });
        }

        //获取地址的结果  （暂没有主动点击获取地址的功能，现在都是自动获取）
        private void GetAddressCallBack()
        {
            Dispatcher.Invoke((Action) delegate()
            {
                HidePwPage();
                ShowAddressPage();
                this.addresslist.Items.Clear();
                foreach (var add in signer.addressPool.addresses)
                {
                    this.addresslist.Items.Add(add);
                }
                ActiveButton();
            });
         
        }

        //增加地址35673ECF9F18F44EBD1C9FC7CAC4327D72EEB08104EFFD20FBBB621341B80AC1
        private void PrivateKey2AddressCallBack(string _privateKey,string _address,string err)
        {
            Dispatcher.Invoke((Action) delegate()
            {
                this.tx_privateKey.Text = _privateKey;
                this.lb_address.Text = _address;
                if (!string.IsNullOrEmpty(err))
                {
                    ErrorMsgShow(err, "提示");
                }
            });
           
        }
        private void AddAddress()
        {
            driverCtr.addAddressEventHandlerCallBack += AddAddressCallBack;
            driverCtr.AddAddress(this.lb_address.Text, this.tx_privateKey.Text);
        }
        private void AddAddressCallBack(bool _suc)
        {
            Dispatcher.Invoke((Action) delegate()
            {
                driverCtr.addAddressEventHandlerCallBack -= AddAddressCallBack;
                if (!_suc)
                    ErrorMsgShow("已经拥有该地址或数据非法","通知");
                //隐藏增加地址的页面
                HideAddBox();
            });
        }

        //删除地址
        private void DeleteAddress()
        {
            driverCtr.deleteAddressEventHandlerCallBack += DeleteAddressCallBack;
            driverCtr.DeleteAddress(selectAddress.type.ToString(), selectAddress.AddressText.ToString());
        }
        private void DeleteAddressCallBack(bool suc)
        {
            Dispatcher.Invoke((Action) delegate() {
                driverCtr.deleteAddressEventHandlerCallBack -= DeleteAddressCallBack;
                if (suc)
                    ErrorMsgShow("删除成功", "提示");
                else
                    ErrorMsgShow("删除失败", "提示");
            });
        }

        //备份密钥
        private void BackUpPrivateKey()
        {
            driverCtr.backUpAddressEventHandlerCallBack += BackUpPrivateKeyCallBack;
            if (selectAddress == null)
                return;
            string str_addressType = selectAddress.type.ToString();
            string str_addressText = selectAddress.AddressText;
            if (string.IsNullOrEmpty(str_addressType) || string.IsNullOrEmpty(str_addressText))
            {
                ErrorMsgShow("请选择要备份的地址", "错误");
                return;
            }
            driverCtr.BackUpAddress(str_addressType, str_addressText);
            selectAddress.AddressText=null;
        }
        private void BackUpPrivateKeyCallBack(bool suc,string _str)  //把从签名机要到的私钥备份到本地
        {
            Dispatcher.Invoke((Action)  delegate()
            {
                driverCtr.backUpAddressEventHandlerCallBack -= BackUpPrivateKeyCallBack;
                if (!suc)
                    ErrorMsgShow("备份失败" + _str, "通知");
                else
                    ErrorMsgShow("已经成功备份"+ _str, "通知");
            });
        }


        
        //修改密码
        private void RestPassword()
        {
            driverCtr.ResetPassword();
        }
        private void RestPasswordCallBack()
        {
            
        }

        private void ErrorMsgShow(string msg ,string header)
        {
            MessageBox.Show(msg, header);
        }

        private void DevelopingFun(object sender, RoutedEventArgs e)
        {
            ErrorMsgShow("功能暂未开放","通知");
        }
       

        //模拟插入钱包
        WindowSimHardware hard = new WindowSimHardware();
        private async void CreateSimHardware(object sender, RoutedEventArgs e)
        {
            DriverS.simdriver.bActive = true;
            hard.Show();
            await Task.Delay(2000);
        }

    }
}

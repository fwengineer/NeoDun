﻿using driver_win.helper;
using NeoDun;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace driver_win.control
{
    class DelAddress:Control
    {
        public override void HandleMsg(params object[] _params)
        {
            result.msgCode = (EnumMsgCode)_params[0];
            result.errorCode = (EnumErrorCode)_params[1];
        }

        public override void Init()
        {
            result.msgCode = EnumMsgCode.DeletingName;
            result.errorCode = EnumErrorCode.Unknow;
        }

        public async override Task<bool> SendMsg(params object[] _params)
        {
            string _addressType = (string)_params[0];
            string _addressText = (string)_params[1];
            UInt16 addressType = (UInt16)Enum.Parse(typeof(AddressType), _addressType);
            byte[] bytes_addressText = NeoDun.SignTool.DecodeBase58(_addressText);
            NeoDun.Message msg = new NeoDun.Message();
            msg.tag1 = 0x02;
            msg.tag2 = 0x03;//删除
            msg.msgid = NeoDun.SignTool.RandomShort();
            msg.writeUInt16(0, addressType);
            Array.Copy(bytes_addressText, 0, msg.data, 2, bytes_addressText.Length);
            signer.SendMessage(msg, true);
            return true;
        }
    }
}

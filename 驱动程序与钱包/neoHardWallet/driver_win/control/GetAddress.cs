﻿using driver_win.helper;
using NeoDun;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace driver_win.control
{
    class GetAddress : Control
    {

        public override void HandleMsg(params object[] _params)
        {
            result.msgCode = (EnumMsgCode)_params[0];
            result.errorCode = (EnumErrorCode)_params[1];
            result.data = (object)signer.addressPool.addresses;
        }

        public override void Init()
        {
            result.msgCode = EnumMsgCode.GettingAddress;
            result.errorCode = EnumErrorCode.Unknow;
        }

        public async override Task<bool> SendMsg(params object[] _params)
        {
            signer.InitAddressPool();
            NeoDun.Message msg = new NeoDun.Message();
            msg.tag1 = 0x02;
            msg.tag2 = 0x01;//查
            msg.msgid = NeoDun.SignTool.RandomShort();
            signer.SendMessage(msg, true);
            return true;
        }
    }
}

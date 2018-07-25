﻿using driver_win.helper;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace driver_win.control
{
    //询问下位机是否允许升级固件
    class ApplyUpdateFramework : Control
    {
        public override void HandleMsg(params object[] _params)
        {
            EnumError enumError = (EnumError)_params[0];
            result.errorCode = enumError;
        }

        public override void SendMsg(params object[] _params)
        {
            NeoDun.Message msg = new NeoDun.Message();
            msg.tag1 = 0x03;
            msg.tag2 = 0x02;
            msg.msgid = NeoDun.SignTool.RandomShort();
            signer.SendMessage(msg, true);
        }
    }


    //安装（升级）固件
    class InstallFramework : Control
    {
        public override void HandleMsg(params object[] _params)
        {
            EnumError enumError = (EnumError)_params[0];
            result.errorCode = enumError;
        }

        public async override void SendMsg(params object[] _params)
        {
            try
            {
                byte[] data = (byte[])_params[0];
                EnumInstallType type = (EnumInstallType)_params[1];
                EnumPluginType content = (EnumPluginType)_params[2];

                var hash = NeoDun.SignTool.ComputeSHA256(data, 0, data.Length);
                string str_hash = NeoDun.SignTool.Bytes2HexString(hash, 0, hash.Length);
                int num = data.Length / (1024 * 50) + 1;

                List<UInt32> remoteids = new List<UInt32>();

                for (var i = 0; i < num; i++)
                {
                    byte[] _data = data.Skip(1024 * 50 * i).Take(1024 * 50).ToArray();
                    var _hash = NeoDun.SignTool.ComputeSHA256(_data, 0, _data.Length);
                    string _str_hash = NeoDun.SignTool.Bytes2HexString(_hash, 0, _hash.Length);
                    NeoDun.DataBlock block = signer.dataTable.newOrGet(_str_hash, (UInt32)_data.Length, NeoDun.DataBlockFrom.FromDriver);
                    block.data = _data;
                    signer.SendDataBlock(block);

                    var __block = signer.dataTable.getBlockBySha256(_str_hash);
                    uint remoteid = await __block.GetRemoteid();
                    if (remoteid == 0)
                    {
                        result.errorCode = EnumError.CommonFailed;
                    }
                    remoteids.Add((uint)remoteid);
                    __block.dataidRemote = 0;
                }
                NeoDun.Message signMsg = new NeoDun.Message();
                signMsg.tag1 = 0x03;
                signMsg.tag2 = 0x01;
                signMsg.msgid = NeoDun.SignTool.RandomShort();
                signMsg.writeUInt16(0, (UInt16)type);
                signMsg.writeUInt16(2, (UInt16)content);
                Array.Copy(hash, 0, signMsg.data, 4, hash.Length);

                for (var i = 0; i < remoteids.Count; i++)
                {
                    signMsg.writeUInt32(38, remoteids[i]);
                }

                signer.SendMessage(signMsg, true);

            }
            catch (Exception e)
            {
                result.errorCode = EnumError.CommonFailed;
            }
        }
    }




    //安装升级插件
    class InstallPlugin : Control
    {
        public override void HandleMsg(params object[] _params)
        {
            EnumError enumError = (EnumError)_params[0];
            result.errorCode = enumError;
        }

        public async override void SendMsg(params object[] _params)
        {
            try
            {
                byte[] data = (byte[])_params[0];
                EnumInstallType type = (EnumInstallType)_params[1];
                EnumPluginType content = (EnumPluginType)_params[2];

                var hash = NeoDun.SignTool.ComputeSHA256(data, 0, data.Length);
                string str_hash = NeoDun.SignTool.Bytes2HexString(hash, 0, hash.Length);
                int num = data.Length / (1024 * 50) + 1;

                List<UInt32> remoteids = new List<UInt32>();

                for (var i = 0; i < num; i++)
                {
                    byte[] _data = data.Skip(1024 * 50 * i).Take(1024 * 50).ToArray();
                    var _hash = NeoDun.SignTool.ComputeSHA256(_data, 0, _data.Length);
                    string _str_hash = NeoDun.SignTool.Bytes2HexString(_hash, 0, _hash.Length);
                    NeoDun.DataBlock block = signer.dataTable.newOrGet(_str_hash, (UInt32)_data.Length, NeoDun.DataBlockFrom.FromDriver);
                    block.data = _data;
                    signer.SendDataBlock(block);

                    var __block = signer.dataTable.getBlockBySha256(_str_hash);
                    uint remoteid = await __block.GetRemoteid();
                    if (remoteid == 0)
                    {
                        result.errorCode = EnumError.CommonFailed;
                    }
                    remoteids.Add((uint)remoteid);
                    __block.dataidRemote = 0;
                }
                NeoDun.Message signMsg = new NeoDun.Message();
                signMsg.tag1 = 0x03;
                signMsg.tag2 = 0x01;
                signMsg.msgid = NeoDun.SignTool.RandomShort();
                signMsg.writeUInt16(0, (UInt16)type);
                signMsg.writeUInt16(2, (UInt16)content);
                Array.Copy(hash, 0, signMsg.data, 4, hash.Length);

                for (var i = 0; i < remoteids.Count; i++)
                {
                    signMsg.writeUInt32(38, remoteids[i]);
                }

                signer.SendMessage(signMsg, true);

            }
            catch (Exception e)
            {
                result.errorCode = EnumError.CommonFailed;
            }
        }
    }


    //卸载插件
    class UninstallPlugin : Control
    {
        public override void HandleMsg(params object[] _params)
        {
            EnumError enumError = (EnumError)_params[0];
            result.errorCode = enumError;
        }

        public override void SendMsg(params object[] _params)
        {
            EnumPluginType enumPluginType = (EnumPluginType)_params[0];
            NeoDun.Message msg = new NeoDun.Message();
            msg.tag1 = 0x03;
            msg.tag2 = 0x03;
            msg.msgid = NeoDun.SignTool.RandomShort();
            msg.writeUInt16(0, (UInt16)enumPluginType);
            signer.SendMessage(msg, true);
        }
    }

}

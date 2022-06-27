import configparser
import os
import traceback
from MyLog import info, error
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QFrame, QWidget, QMenu, QMessageBox, QApplication
from PyQt5 import QtGui, QtCore

from MessageWindow import MyMessage
from UI import project
from ConfigVar import ConfigVar, ProjectMess


# 导入工程窗口
class ProFrame(QWidget, project.Ui_Form):

    def __init__(self, project):
        super(ProFrame, self).__init__()
        self.setupUi(self)
        self.projectmessage = ProjectMess()
        self.projectmessage.set(project)
        self.buttonname.setText(self.projectmessage.name)
        self.path.setText(self.projectmessage.path)
        str = 'Demo introduce:\n'
        for demo in self.projectmessage.demo:
            str = str + ConfigVar.demo_introduce[demo]
            str += '\n'
        self.demo.setText(str)
        self.setToolTip(self.projectmessage.chip + "\n" + self.projectmessage.type)
        self.path.setToolTip(self.path.text())
        self.buttonname.setToolTip(self.projectmessage.name)

    def openproject(self):
        ConfigVar.project.set(self.projectmessage)
        self.projectmessage.show()
        if ConfigVar.path_flag == 'true':
            if os.path.exists(self.projectmessage.cmd.split(' ')[1]):
                ConfigVar.mainWindow.trigger.emit(self.projectmessage.cmd)
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'open', ":/req/Create a new project/Yun.png")
        else:
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'options', ":/req/Create a new project/Yun.png")

        self.patch()

    def deleteproject(self):
        try:
            self.projectmessage.show()
            self.projectmessage.delete(ConfigVar.project_path_hash)
            ConfigVar.mainWindow.refreshsig.emit()
        except PermissionError as e:
            traceback.print_exc()
            error(e)
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'PermissionError', ":/req/Create a new project/Yun.png")
        except Exception as e:
            traceback.print_exc()
            error(e)

    # 右键菜单（通过 ContextMenuPolicy 启用菜单，链接菜单信号的槽函数）
    def myListWidgetContext(self, point):
        try:
            menu = QMenu()
            if ConfigVar.language == 'zh_cn':
                opt1 = menu.addAction("打开工程")
                opt2 = menu.addAction("打开文件夹")
                opt3 = menu.addAction("移除工程")
                opt4 = menu.addAction("Flash补丁")
            elif ConfigVar.language == 'cn':
                opt1 = menu.addAction("打開工程")
                opt2 = menu.addAction("打開文件夾")
                opt3 = menu.addAction("移除工程")
                opt4 = menu.addAction("Flash補丁")
            else:
                opt1 = menu.addAction("open Project")
                opt2 = menu.addAction("open Folder")
                opt3 = menu.addAction("remove Project")
                opt4 = menu.addAction("patch Flash")
            super(ProFrame, self).show()

            icon1 = QtGui.QIcon()
            icon1.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 5_slices/MBE风格多色图标-文档.png"), QtGui.QIcon.Normal,
                            QtGui.QIcon.Off)
            opt1.setIcon(icon1)
            icon2 = QtGui.QIcon()
            icon2.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 5_slices/打开_操作_jurassic.png"), QtGui.QIcon.Normal,
                            QtGui.QIcon.Off)
            opt2.setIcon(icon2)
            icon3 = QtGui.QIcon()
            icon3.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 5_slices/已删除项目节点_3.png"), QtGui.QIcon.Normal,
                            QtGui.QIcon.Off)
            opt3.setIcon(icon3)
            icon4 = QtGui.QIcon()
            icon4.addPixmap(QtGui.QPixmap(":/req/update/画板 – 5_slices/补丁信息close_slices/补丁信息close.png"),
                            QtGui.QIcon.Normal,
                            QtGui.QIcon.Off)
            opt4.setIcon(icon4)

            action = menu.exec_(self.widget.mapToGlobal(point))

            if action == opt1:
                self.openproject()
            elif action == opt2:
                ConfigVar.project.set(self.projectmessage)
                info("文件夹打开  " + self.projectmessage.path)
                os.system('start explorer ' + self.projectmessage.path.replace('/', '\\'))
                print(self.projectmessage.path)
                return
            elif action == opt3:
                self.deleteproject()
            elif action == opt4:
                self.patch()
            else:
                return
        except Exception as e:
            traceback.print_exc()
            error(e)

    def patch(self):
        self.projectmessage.show()
        filepath = self.projectmessage.cmd.split(' ')[1].replace('.uvprojx', '.uvoptx')
        filepath = filepath.replace('\\', '/')
        print("\n-------------------补丁：")
        print(self.projectmessage.cmd)
        info("补丁文件 " + filepath)
        try:
            pf = open(filepath, 'r')
            conf = pf.read()
            pf.close()

            conf = conf.replace('<TargetOption>\n\
      <CLKADS>12000000</CLKADS>\n\
      <OPTTT>\n\
        <gFlags>0</gFlags>\n\
        <BeepAtEnd>1</BeepAtEnd>\n\
        <RunSim>0</RunSim>\n\
        <RunTarget>1</RunTarget>\n\
        <RunAbUc>0</RunAbUc>\n\
      </OPTTT>', '<TargetOption>\n\
      <CLKADS>12000000</CLKADS>\n\
      <OPTTT>\n\
        <gFlags>1</gFlags>\n\
        <BeepAtEnd>1</BeepAtEnd>\n\
        <RunSim>0</RunSim>\n\
        <RunTarget>1</RunTarget>\n\
        <RunAbUc>0</RunAbUc>\n\
      </OPTTT>')
            conf = conf.replace('<OPTFL>\n\
        <tvExp>0</tvExp>\n\
        <tvExpOptDlg>0</tvExpOptDlg>\n\
        <IsCurrentTarget>1</IsCurrentTarget>\n\
      </OPTFL>', '<OPTFL>\n\
        <tvExp>1</tvExp>\n\
        <tvExpOptDlg>0</tvExpOptDlg>\n\
        <IsCurrentTarget>1</IsCurrentTarget>\n\
      </OPTFL>')
            conf = conf.replace('<nTsel>0</nTsel>', '<nTsel>4</nTsel>')
            conf = conf.replace('<pMon>BIN\\UL2CM3.DLL</pMon>', '<pMon>Segger\\JL2CM3.dll</pMon>')
            conf = conf.replace('<TargetDriverDllRegistry>\n\
        <SetRegEntry>\n\
          <Number>0</Number>\n\
          <Key>UL2CM3</Key>\n\
          <Name>UL2CM3(-S0 -C0 -P0 -FD20000000 -FC1000)</Name>\n\
        </SetRegEntry>\n\
      </TargetDriverDllRegistry>', '<TargetDriverDllRegistry>\n\
        <SetRegEntry>\n\
          <Number>0</Number>\n\
          <Key>JL2CM3</Key>\n\
          <Name>-U20090929 -O78 -S2 -ZTIFSpeedSel5000 -A0 -C0 -JU1 -JI127.0.0.1 -JP0 -RST0 -N00("ARM CoreSight SW-DP") -D00(0BB11477) -L00(0) -TO18 -TC10000000 -TP21 -TDS8007 -TDT0 -TDC1F -TIEFFFFFFFF -TIP8 -TB1 -TFE0 -FO7 -FD20000000 -FC1000 -FN1 -FF0VTM071x_FLASH_AP -FS00 -FL01E000</Name>\n\
        </SetRegEntry>\n\
        <SetRegEntry>\n\
          <Number>0</Number>\n\
          <Key>UL2CM3</Key>\n\
          <Name>UL2CM3(-S0 -C0 -P0 -FD20000000 -FC1000)</Name>\n\
        </SetRegEntry>\n\
      </TargetDriverDllRegistry>')
            #         conf = conf.replace('<GroupName>CMSIS</GroupName>\n\
            # <tvExp>0</tvExp>', '<GroupName>CMSIS</GroupName>\n\
            # <tvExp>1</tvExp>')
            #         conf = conf.replace('<GroupName>User</GroupName>\n\
            # <tvExp>0</tvExp>', '<GroupName>User</GroupName>\n\
            # <tvExp>1</tvExp>')
            #         conf = conf.replace('<GroupName>StdPeriph_Driver</GroupName>\n\
            # <tvExp>0</tvExp>', '<GroupName>StdPeriph_Driver</GroupName>\n\
            # <tvExp>1</tvExp>')
            #         conf = conf.replace('<GroupName>Utilities</GroupName>\n\
            # <tvExp>0</tvExp>', '<GroupName>Utilities</GroupName>\n\
            # <tvExp>1</tvExp>')
            if self.projectmessage.type == 'USBV1.0':
                conf = conf.replace('<CpuCode>0</CpuCode>', '<CpuCode>7</CpuCode>')

            pf = open(filepath, 'w')
            pf.write(conf)
            pf.close()

            # msg = MyMessage()
            # msg.btn_one(MyMessage.info, 'patchTrue', ":/req/Create a new project/Yun.png")

        except Exception as e:
            traceback.print_exc()
            error(e)
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'patchFlase', ":/req/Create a new project/Yun.png")

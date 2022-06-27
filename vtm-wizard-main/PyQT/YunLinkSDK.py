import configparser
import os.path
import shutil
import sys
import traceback

from PyQt5 import QtCore
from PyQt5.QtCore import pyqtSignal, QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QApplication, QMainWindow, QMessageBox
from MyLog import info, error, LogInit, GetPath
from AboutWindow import AboutWindow
from ChipWindow import ChipWindow
from ConfigVar import ConfigVar, WorkThread, CmdThread
from DocumentsWindow import DocumentsWindow
from ImportChipWindow import ImportChipWindow
from KeilWindow import KeilWindow
from ProChipWindow import ProChipWindow
from ProWindow import ProWindow
from MessageWindow import MyMessage
from UI.Yun import Ui_YunWizard



class MainWindow(QMainWindow, Ui_YunWizard):
    # 自定义信号对象。参数str就代表这个信号可以传一个字符串
    trigger = pyqtSignal(str)
    cmdsig = pyqtSignal(str)
    refreshsig = pyqtSignal()
    def __init__(self, parent=None):
        super(MainWindow, self).__init__()
        # ConfigVar.readconf(self)
        ConfigVar.readconf(self)
        self.setupUi(self)
        self.keilwindow = KeilWindow()
        self.chipwindow = ChipWindow()
        self.prowindow = ProWindow()
        self.importchipwindow = ImportChipWindow()
        self.prochipwindow = ProChipWindow()
        self.documentswindow = DocumentsWindow()
        self.aboutwindow = AboutWindow()
        self.trans = QTranslator()

        self.trigger.connect(self.keilthread)
        self.cmdsig.connect(self.cmdthread)
        self.refreshsig.connect(self.refresh)
        self.actionnew.triggered.connect(self.newImage)
        self.actionimport.triggered.connect(self.ImportImage)
        self.actionICP.triggered.connect(self.openICP)
        self.actionISP.triggered.connect(self.openISP)
        self.actionSSCOM.triggered.connect(self.openSSCOM)
        self.actionKeilPatch.triggered.connect(self.KeilPatch)
        self.chipBox.activated[str].connect(self.ProChipImage)
        self.actionEnglish.triggered.connect(self._trigger_english)
        self.actionzn.triggered.connect(self._trigger_zh_cn)
        self.actionzn2.triggered.connect(self._trigger_cn)

        self.ProChipImage()

        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()


    def ProChipImage(self):
        # print(self.chipBox.currentText())
        info(self.chipBox.currentText())
        self.keilbutton.setChecked(False)
        self.Allbutton.setChecked(False)
        self.prochipwindow.refreshsig.emit()
        self.prowindow.refreshsig.emit()
        self.prochipwindow = ProChipWindow()
        self.prochipwindow.chipsig.emit(self.chipBox.currentText())
        self.prowin.addWidget(self.prochipwindow)
        qsize = self.geometry()
        width = qsize.width()
        height = qsize.height()
        self.prochipwindow.resizesig.emit('[' + str(width - 1050) + ',' + str(height - 670) + ']')
        self.prochipwindow.show()

    def KeilPatch(self):
        if ConfigVar.path_flag == 'true':
            try:
                flashpath = ConfigVar.keilUV4_path.split('UV4')[0]+'ARM\\Flash\\'
                # print(flashpath)
                info(flashpath)
                shutil.copy("flash/VTM071x_FLASH_AP.FLM", flashpath + "/VTM071x_FLASH_AP.FLM")
                shutil.copy("flash/VTM071x_FLASH_LD.FLM", flashpath + "/VTM071x_FLASH_LD.FLM")
                msg = MyMessage()
                msg.btn_one(MyMessage.info, 'patchTrue', ":/req/Create a new project/Yun.png")
            except Exception as e:
                traceback.print_exc()
                error(e)
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'patchFlase', ":/req/Create a new project/Yun.png")
        else:
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'options', ":/req/Create a new project/Yun.png")


    def keilthread(self, str):
        workthread = WorkThread()
        workthread.run(str)

    def cmdthread(self, str):
        workthread = CmdThread()
        workthread.run(str)

    def showpro(self):
        try:
            if self.keilbutton.isChecked():
                if self.Allbutton.isChecked():
                    self.Allbutton.setChecked(False)
                ConfigVar.projectchip = self.chipBox.currentText() + '.keil'
                self.prochipwindow.refreshsig.emit()
                self.show_projects()
            elif not self.Allbutton.isChecked():
                self.prowindow.refreshsig.emit()
                self.ProChipImage()
        except Exception as e:
            traceback.print_exc()
            error(e)
    def showallpro(self):
        try:
            if self.Allbutton.isChecked():
                if self.keilbutton.isChecked():
                    self.keilbutton.setChecked(False)
                ConfigVar.projectchip = self.chipBox.currentText()+'.all'
                self.prochipwindow.refreshsig.emit()
                self.show_projects()
            elif not self.keilbutton.isChecked():
                self.prowindow.refreshsig.emit()
                self.ProChipImage()
        except Exception as e:
            traceback.print_exc()
            error(e)
    def searchproject(self):
        ConfigVar.projectchip = self.chipBox.currentText() + '.all'
        self.prochipwindow.refreshsig.emit()
        self.prowindow.refreshsig.emit()
        self.prowindow = ProWindow()
        self.prowin.addWidget(self.prowindow)
        qsize = self.geometry()
        width = qsize.width()
        height = qsize.height()
        self.prowindow.show()
        self.prowindow.searchsig.emit(self.searchline.text())
        self.prowindow.resizesig.emit('[' + str(width - 1050) + ',' + str(height - 670) + ']')

    def KeilImage(self):
        self.keilwindow.show()  # 打开options窗口

    def DocumentsImage(self):
        self.documentswindow.show()

    def newImage(self):
        if len(ConfigVar.python_path) > 1 and len(ConfigVar.keilUV4_path) > 7 \
                and (
                ConfigVar.python_path[len(ConfigVar.python_path) - 10:len(ConfigVar.python_path) - 4] == "python" or \
                ConfigVar.python_path[len(ConfigVar.python_path) - 10:len(ConfigVar.python_path) - 4] == "ython3") \
                and ConfigVar.keilUV4_path[len(ConfigVar.keilUV4_path) - 7:len(ConfigVar.keilUV4_path) - 4] == "UV4" and \
                ConfigVar.path_flag == 'true':
            self.chipwindow.show()# 打开新建工程窗口
        else:
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'options', ":/req/Create a new project/Yun.png")

    def AboutImage(self):
        try:
            self.aboutwindow.show()   #打开about窗口
        except Exception as e:
            traceback.print_exc()
            error(e)
    def ImportImage(self):
        self.importchipwindow.show()  # 打开导入工程窗口

    def show_projects(self):
        self.refresh()  # 刷新已有工程
        qsize = self.geometry()
        width = qsize.width()
        height = qsize.height()
        self.prowindow.resizesig.emit('[' + str(width - 1050) + ',' + str(height - 670) + ']')


    def refresh(self):
        # print("refresh")
        info("refresh------->")
        self.prowindow.refreshsig.emit()
        self.prowindow = ProWindow()
        self.prowin.addWidget(self.prowindow)  # 将窗口放入girdLayout中
        self.prowindow.show()  # 打开已有工程窗口
        self.prowindow.showallsig.emit()

    def openSSCOM(self):
        ConfigVar.mainWindow.cmdsig.emit("./Tools/sscom/sscom5.13.1.exe")
    def openICP(self):
        ConfigVar.mainWindow.cmdsig.emit("./Tools/ICP_Programming_Tool/ICP_Programming_Tool.exe")
    def openISP(self):
        ConfigVar.mainWindow.cmdsig.emit("./Tools/ISP_Programming_Tool/ISP_Programming_Tool_V2.1"
                                          "/ISP_Programming_Tool.exe")

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            info("[language] Change to English")
            self.trans.load("./translator/Yun_en")
            _app = QApplication.instance()  # 获取app实例
            _app.installTranslator(self.trans)
            # 重新翻译界面
            self.retranslateUi(self)
            ConfigVar.language = 'en'
            config = configparser.ConfigParser()
            config.read(ConfigVar.config_path_hash)
            config.set('installation', 'language', ConfigVar.language)
            with open(ConfigVar.config_path_hash, 'w') as f:
                config.write(f)
        except Exception as e:
            traceback.print_exc()
            error(e)
    def _trigger_zh_cn(self):
        try:
            # print("[MainWindow] Change to 简体中文")
            info("[language] Change to 简体中文")
            self.trans.load("./translator/Yun_zh_cn")
            _app = QApplication.instance()
            _app.installTranslator(self.trans)
            self.retranslateUi(self)
            ConfigVar.language = 'zh_cn'
            config = configparser.ConfigParser()
            config.read(ConfigVar.config_path_hash)
            config.set('installation', 'language', ConfigVar.language)
            with open(ConfigVar.config_path_hash, 'w') as f:
                config.write(f)
        except Exception as e:
            traceback.print_exc()
            error(e)
    def _trigger_cn(self):
        try:
            # print("[MainWindow] Change to 繁體中文")
            info("[language] Change to 繁體中文")
            self.trans.load("./translator/Yun_cn")
            _app = QApplication.instance()
            _app.installTranslator(self.trans)
            self.retranslateUi(self)
            ConfigVar.language = 'cn'
            config = configparser.ConfigParser()
            config.read(ConfigVar.config_path_hash)
            config.set('installation', 'language', ConfigVar.language)
            with open(ConfigVar.config_path_hash, 'w') as f:
                config.write(f)
        except Exception as e:
            traceback.print_exc()
            error(e)

    def resizeEvent(self, evt):
       try:
            width = evt.size().width()
            height = evt.size().height()
            # print("窗口大小 ：\n    width:",end='')
            # print(width)
            # print("    height:",end='')
            # print(height)
            info("窗口大小(width:%d   height:%d)", width, height)
            if width+height > 1340 + 990:
                self.searchfram.setVisible(True)
            else:
                self.searchfram.setVisible(False)
            ConfigVar.mainwindowsize = '[' + str(width - 1050) + ',' + str(height - 670) + ']'
            self.prowindow.resizesig.emit('[' + str(width - 1050) + ',' + str(height - 670) + ']')
            self.prochipwindow.resizesig.emit('['+str(width-1050)+','+str(height-670)+']')
            self.gridLayoutWidget_2.setGeometry(QtCore.QRect(240,90,746+width,491+height))
            self.prochipwindow.chipsig.emit(self.chipBox.currentText())

       except Exception as e:
           traceback.print_exc()
           error(e)
if __name__ == "__main__":
    LogPath = GetPath('log')
    LogInit(LogPath)

    app = QApplication(sys.argv)
    ConfigVar.mainWindow = MainWindow()
    # print("主窗口赋值")
    info('Start Logging!')
    ConfigVar.mainWindow.show()
    sys.exit(app.exec_())

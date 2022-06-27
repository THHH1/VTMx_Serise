import configparser
import os
import traceback
from MyLog import info, error
from PyQt5.QtCore import pyqtSignal, QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QFileDialog, QApplication
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from NewWindow import NewWindow
from MessageWindow import MyMessage
from UI import createVTM


# 导入工程窗口
class ChipWindow(QMainWindow, createVTM.Ui_chip):
    def __init__(self):
        super(ChipWindow, self).__init__()
        self.setupUi(self)
        self.newwindow = NewWindow()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.trans = QTranslator()

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(ChipWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/ChipWindow_en")
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
            self.trans.load("./translator/ChipWindow_zh_cn")
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
            self.trans.load("./translator/ChipWindow_cn")
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

    def newImage(self):
        try:
            if self.VTM071X.isChecked():
                info("Chip =" + self.VTM071X.text())
                ConfigVar.project.chip = self.VTM071X.text()
                self.newwindow.show()
                self.newwindow.backsig.connect(self.show)
                self.hide()
            elif self.VTM32030X.isChecked():
                info("Chip =" + self.VTM32030X.text())
                ConfigVar.project.chip = self.VTM32030X.text()
                msg = MyMessage()
                msg.btn_one(MyMessage.info, 'VTM32030X', ":/req/Create a new project/Yun.png")
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'chip', ":/req/Create a new project/Yun.png")
        except Exception as e:
            traceback.print_exc()
            error(e)

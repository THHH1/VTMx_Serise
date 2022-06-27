import configparser
import os
import traceback
from MyLog import info, error
from PyQt5.QtCore import pyqtSignal, QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QFileDialog, QApplication
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from MessageWindow import MyMessage
from UI import importchip
from ImportDemoWindow import ImportDemoWindow


# 导入工程窗口
class ImportChipWindow(QMainWindow, importchip.Ui_chip):
    backsig = pyqtSignal()

    def __init__(self):
        super(ImportChipWindow, self).__init__()
        self.setupUi(self)
        self.importdemowindow = ImportDemoWindow()
        self.trans = QTranslator()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.backsig.connect(self.show)

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(ImportChipWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/ImportChipWindow_en")
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
            self.trans.load("./translator/ImportChipWindow_zh_cn")
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
            self.trans.load("./translator/ImportChipWindow_cn")
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

    def ImportDemoImage(self):
        try:
            if self.VTM071X.isChecked():
                info("ConfigVar.project.chip      " + self.VTM071X.text())
                ConfigVar.project.chip = self.VTM071X.text()
                self.importdemowindow.show()
                self.importdemowindow.backsig.connect(self.show)
                self.hide()
            elif self.VTM32030X.isChecked():
                info("ConfigVar.project.chip      " + self.VTM32030X.text())
                ConfigVar.project.chip = self.VTM32030X.text()
                msg = MyMessage()
                msg.btn_one(MyMessage.info, 'VTM32030X', ":/req/Create a new project/Yun.png")
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'chip', ":/req/Create a new project/Yun.png")
        except Exception as e:
            traceback.print_exc()
            error(e)

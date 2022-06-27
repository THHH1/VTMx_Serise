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
from UI import importdemo
from ImportPathWindow import ImportPathWindow


# 导入工程窗口
class ImportDemoWindow(QMainWindow, importdemo.Ui_Form):
    backsig = pyqtSignal()

    def __init__(self):
        super(ImportDemoWindow, self).__init__()
        self.setupUi(self)
        self.importpathwindow = ImportPathWindow()
        self.trans = QTranslator()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)

    def back(self):
        self.backsig.emit()
        self.close()

    def ImportPathImage(self):
        if self.radioButton_2.isChecked():
            print(self.radioButton_2.text())
            print("ImportPath************\n")
            ConfigVar.project.type = self.radioButton_2.text()
            info('ConfigVar.project.type = ' + self.radioButton_2.text())
            for i in range(7, 12):
                cmd = "button= self.radioButton_" + str(i) + ".isChecked()"
                local = {}
                exec(cmd, {'self': self}, local)
                if local['button']:
                    cmd = "button= self.radioButton_" + str(i) + ".text()"
                    local = {}
                    exec(cmd, {'self': self}, local)
                    # print(local['button'])
                    ConfigVar.project.demo = [local['button']]
                    self.importpathwindow.show()
                    self.importpathwindow.backsig.connect(self.show)
                    self.hide()
                    break
        else:
            # print(self.radioButton.text())
            ConfigVar.project.type = self.radioButton.text()
            info('ConfigVar.project.type = ' + self.radioButton.text())
            demo = []
            for i in range(42, 63):
                cmd = "button= self.checkBox_" + str(i) + ".isChecked()"
                local = {}
                # print("cmd-------cmd: " + cmd)
                exec(cmd, {'self': self}, local)
                # print(local)
                if local['button']:
                    cmd = "button= self.checkBox_" + str(i) + ".text()"
                    local = {}
                    exec(cmd, {'self': self}, local)
                    demo.append(local['button'])
            # print(demo)
            if demo.__len__() > 0:
                ConfigVar.project.demo = demo
                self.importpathwindow.show()
                self.importpathwindow.backsig.connect(self.show)
                self.hide()
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'demo', ":/req/Create a new project/Yun.png")

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(ImportDemoWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/ImportDemoWindow_en")
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
            self.trans.load("./translator/ImportDemoWindow_zh_cn")
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
            self.trans.load("./translator/ImportDemoWindow_cn")
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

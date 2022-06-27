import configparser
import os
import re
import subprocess
import traceback
from functools import partial
from MyLog import info, error
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import pyqtSignal, QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QFileDialog, QApplication

from ConfigVar import ConfigVar
from DemoWindow import DemoWindow
from MessageWindow import MyMessage
from UI import create


# new project子窗口
class NewWindow(QMainWindow, create.Ui_Dialog):
    backsig = pyqtSignal()

    def __init__(self):
        super(NewWindow, self).__init__()
        self.setupUi(self)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.demowindow = DemoWindow()
        self.trans = QTranslator()

    def back(self):
        if self.projectname.text() != "":
            config = configparser.ConfigParser()
            config.read(ConfigVar.config_path_hash)
            ConfigVar.project.name = self.projectname.text()
            config.set('installation', 'projectname', ConfigVar.project.name)
            ConfigVar.project.path = self.projectpath.text()
            self.mkdir(ConfigVar.project.path)
            # print(ConfigVar.project.name, ConfigVar.project.path)
            info("缓存名称：%s 缓存路径：%s", ConfigVar.project.name, ConfigVar.project.path)
            with open(ConfigVar.config_path_hash, 'w') as f:
                config.write(f)
        self.backsig.emit()
        self.close()

    def show(self):

        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        ConfigVar.readconf(self)
        self.projectname.setText(ConfigVar.project.name)
        self.projectpath.setText(ConfigVar.project.path)

        names = []
        pconfig = configparser.ConfigParser()
        pconfig.read(ConfigVar.project_path_hash)
        ids = pconfig.options('path')
        for pro_name in ids:
            names.append(pconfig.get('name', pro_name))
        if self.projectname.text() in names:
            r = re.search("\d+$", names[-1])
            if r:
                self.projectname.setText("Test" + str(int(r.group()) + 1))
        super(NewWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/NewWindow_en")
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
            self.trans.load("./translator/NewWindow_zh_cn")
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
            self.trans.load("./translator/NewWindow_cn")
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

    def open_dir(self):
        directory1 = QFileDialog.getExistingDirectory()
        ConfigVar.project.path = directory1
        self.projectpath.setText(directory1)
        # print(ConfigVar.project.path)
        config = configparser.ConfigParser()
        config.read(ConfigVar.config_path_hash)
        config.set('installation', 'projectpath', ConfigVar.project.path)
        with open(ConfigVar.config_path_hash, 'w') as f:
            config.write(f)

    def to_demo(self):
        try:
            pconfig = configparser.ConfigParser()
            if self.projectpath.text() != '':
                if os.path.exists(ConfigVar.project_path_hash):
                    pconfig.read(ConfigVar.project_path_hash)
                    names = []
                    ids = pconfig.options('path')
                    for id in ids:
                        names.append(pconfig.get('name', id))
                    if self.projectname.text() == "" or self.projectname.text() in names or not re.match(
                            "^[A-Za-z0-9_-]*$", self.projectname.text()):
                        msg = MyMessage()
                        msg.btn_one(MyMessage.error, 'pname', ":/req/Create a new project/Yun.png")

                    else:
                        config = configparser.ConfigParser()
                        config.read(ConfigVar.config_path_hash)
                        ConfigVar.project.name = self.projectname.text()
                        ConfigVar.project.chip = 'VTM071X'
                        config.set('installation', 'projectname', ConfigVar.project.name)
                        ConfigVar.project.path = self.projectpath.text()
                        self.mkdir(ConfigVar.project.path)
                        # print(ConfigVar.project.name, ConfigVar.project.path)
                        info("创建名称：%s 创建路径：%s", ConfigVar.project.name, ConfigVar.project.path)
                        with open(ConfigVar.config_path_hash, 'w') as f:
                            config.write(f)
                        self.demowindow.show()
                        self.demowindow.backsig.connect(self.show)
                        self.hide()

                else:
                    config = configparser.ConfigParser()
                    config.read(ConfigVar.config_path_hash)
                    ConfigVar.project.name = self.projectname.text()
                    ConfigVar.project.chip = 'VTM071X'
                    config.set('installation', 'projectname', ConfigVar.project.name)
                    ConfigVar.project.path = self.projectpath.text()
                    self.mkdir(ConfigVar.project.path)
                    # print(ConfigVar.project.name, ConfigVar.project.path)
                    with open(ConfigVar.config_path_hash, 'w') as f:
                        config.write(f)
                    self.demowindow.show()
                    self.demowindow.backsig.connect(self.show)
                    self.hide()
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'ppath', ":/req/Create a new project/Yun.png")
        except Exception as e:
            traceback.print_exc()
            error(e)

    @staticmethod
    def mkdir(path):
        folder = os.path.exists(path)
        if not folder:  # 判断是否存在文件夹如果不存在则创建为文件夹
            os.makedirs(path)  # makedirs 创建文件时如果路径不存在会创建这个路径

    # 退出函数，可以在子窗口的代码中创建指向此函数的事件。

    def Close(self):
        reply = QMessageBox.question(self, '确认框', '确认退出吗？',
                                     QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        if reply == QMessageBox.Yes:
            self.hide()
        else:
            pass

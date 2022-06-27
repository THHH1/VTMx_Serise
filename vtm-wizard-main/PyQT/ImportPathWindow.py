import configparser
import os
import re
import time
import traceback
from MyLog import info, error
from PyQt5.QtCore import pyqtSignal, QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QFileDialog, QApplication
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from MessageWindow import MyMessage
from UI import importpath


# 导入工程窗口
class ImportPathWindow(QMainWindow, importpath.Ui_add):
    backsig = pyqtSignal()
    config = configparser.ConfigParser()
    projectpath = ''

    def __init__(self):
        super(ImportPathWindow, self).__init__()
        self.setupUi(self)
        # self.refreshsig.connect(self.hide)
        self.projectTrue.setVisible(False)
        self.projectFalse.setVisible(True)
        self.projectpath = self.projectPath.text()
        ConfigVar.readconf(self)
        self.trans = QTranslator()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)

    def back(self):
        self.backsig.emit()
        self.close()

    def add(self):
        try:
            if len(ConfigVar.python_path) > 1 and len(ConfigVar.keilUV4_path) > 7 \
                    and (
                    ConfigVar.python_path[len(ConfigVar.python_path) - 10:len(ConfigVar.python_path) - 4] == "python" or \
                    ConfigVar.python_path[len(ConfigVar.python_path) - 10:len(ConfigVar.python_path) - 4] == "python3") \
                    and ConfigVar.keilUV4_path[
                        len(ConfigVar.keilUV4_path) - 7:len(ConfigVar.keilUV4_path) - 4] == "UV4":
                names = []
                if os.path.exists(ConfigVar.project_path_hash):
                    config = configparser.ConfigParser()
                    config.read(ConfigVar.project_path_hash)
                    ids = config.options('path')
                    for id in ids:
                        names.append(config.get('name', id))
                    print(names)
                    print("+++++++++++++++++++++++\n")
                    if self.projectName.text() == "" or self.projectName.text() in names or not re.match(
                            "^[A-Za-z0-9_-]*$", self.projectName.text()):
                        msg = MyMessage()
                        msg.btn_one(MyMessage.error, 'pname', ":/req/Create a new project/Yun.png")
                        info("非法名称 %s", self.projectName.text())
                        return

                # print(self.projectpath)
                # print(os.path.exists(self.projectpath))
                if self.projectName.text() == "" or self.projectName.text() in names or not re.match("^[A-Za-z0-9_-]*$",
                                                                                                     self.projectName.text()):
                    msg = MyMessage()
                    msg.btn_one(MyMessage.error, 'pname', ":/req/Create a new project/Yun.png")
                elif not os.path.exists(self.projectpath) or self.projectpath == '' \
                        or self.projectpath.__len__() < 7 \
                        or self.projectpath[self.projectpath.__len__() - 7:self.projectpath.__len__()] != "uvprojx":
                    msg = MyMessage()
                    msg.btn_one(MyMessage.error, 'ppath', ":/req/Create a new project/Yun.png")
                    info("非法路径 %s", self.projectpath)
                else:
                    # print(self.projectName.text())
                    # print(self.projectpath)
                    ConfigVar.project.id = str(ConfigVar.ID)
                    ConfigVar.ID += 1
                    ConfigVar.project.name = self.projectName.text()
                    ConfigVar.project.path = self.projectpath.split('MDK-ARM', 1)[0]
                    ConfigVar.project.cmd = ConfigVar.keilUV4_path + " " + self.projectpath
                    ConfigVar.project.ctime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
                    ConfigVar.project.show()
                    ConfigVar.project.write(ConfigVar.project_path_hash)
                    config = configparser.ConfigParser()
                    config.read(ConfigVar.config_path_hash)
                    config.set('installation', 'ID', str(ConfigVar.ID))
                    with open(ConfigVar.config_path_hash, 'w') as f:
                        config.write(f)
                    msg = MyMessage()
                    msg.btn_one(MyMessage.info, 'add', ":/req/Create a new project/Yun.png")
                    ConfigVar.projectchip = ConfigVar.project.chip + '.all'
                    self.close()
                    try:
                        ConfigVar.mainWindow.refreshsig.emit()
                    except Exception as e:
                        traceback.print_exc()
                        error(e)
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'options', ":/req/Create a new project/Yun.png")
        except Exception as e:
            traceback.print_exc()
            error(e)

    def openfile(self):
        # fileName1, tp = QFileDialog.getOpenFileName()  # 设置文件扩展名过滤,注意用双分号间隔
        # print(fileName1[fileName1.__len__() - 7:fileName1.__len__()])
        fileNames = QFileDialog.getExistingDirectory()
        fileName1 = ""
        print("ImportPahtWindow-----openfile\n")
        for filepath, dirnames, filenames in os.walk(fileNames):
            for filename in filenames:
                file = os.path.join(filepath, filename)
                if file.__len__() > 7 and file[file.__len__() - 7:file.__len__()] == "uvprojx":
                    fileName1 = file
                    print("\n------------ImportPahtWindow:fileName1")
                    print(fileName1)
        if fileName1.__len__() > 7 and fileName1[fileName1.__len__() - 7:fileName1.__len__()] == "uvprojx":
            self.projectPath.setText(fileName1)
            self.projectTrue.setVisible(True)
            self.projectFalse.setVisible(False)
            self.projectpath = fileName1
        else:
            self.projectFalse.setVisible(True)
            self.projectTrue.setVisible(False)
            self.projectPath.setText(fileName1)
            self.projectpath = ''
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'uvprojx', ":/req/Create a new project/Yun.png")

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(ImportPathWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/ImportPathWindow_en")
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
            self.trans.load("./translator/ImportPathWindow_zh_cn")
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
            self.trans.load("./translator/ImportPathWindow_cn")
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

import configparser
import traceback
from MyLog import info, error
from PyQt5 import QtCore
from PyQt5.QtCore import QTranslator
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QFileDialog, QApplication

from ConfigVar import ConfigVar
from UI import keil
from MessageWindow import MyMessage

# options子窗口
class KeilWindow(QMainWindow, keil.Ui_Dialog):
    def __init__(self):
        super(KeilWindow, self).__init__()
        self.setupUi(self)
        self.trans = QTranslator()

        self.check()
        # self.setWindowFlags(QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
        self.label_2.setVisible(False)
        self.pypath.setVisible(False)
        self.pushButton_2.setVisible(False)
        self.pytrue.setVisible(False)
        self.pyfalse.setVisible(False)


    def show(self):
        ConfigVar.readconf(self)
        self.pypath.setText(ConfigVar.python_path)
        self.UVpath.setText(ConfigVar.keilUV4_path)
        self.check()

        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(KeilWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/KeilWindow_en")
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
            self.trans.load("./translator/KeilWindow_zh_cn")
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
            self.trans.load("./translator/KeilWindow_cn")
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
    def check(self):
        py = ConfigVar.python_path[len(ConfigVar.python_path) - 10:len(ConfigVar.python_path) - 4]
        if py == "python" or py == "ython3":
            # self.pytrue.setVisible(1)
            # self.pyfalse.setVisible(0)
            self.pypath.setText(ConfigVar.python_path)
        else:
            ConfigVar.python_path = ""
            self.pypath.setText(ConfigVar.python_path)
            # self.pytrue.setVisible(0)
            # self.pyfalse.setVisible(1)
        uv4 = ConfigVar.keilUV4_path[len(ConfigVar.keilUV4_path) - 7:len(ConfigVar.keilUV4_path) - 4]
        if uv4 == "UV4":
            self.UVtrue.setVisible(1)
            self.UVFalse.setVisible(0)
            self.UVpath.setText(ConfigVar.keilUV4_path)
        else:
            ConfigVar.keilUV4_path = ""
            self.UVpath.setText(ConfigVar.keilUV4_path)
            self.UVtrue.setVisible(0)
            self.UVFalse.setVisible(1)

    def open_dir(self):
        fileName1, tp = QFileDialog.getOpenFileName()  # 设置文件扩展名过滤,注意用双分号间隔
        ConfigVar.python_path = fileName1
        self.check()

    def open_file(self):
        fileName1, tp = QFileDialog.getOpenFileName()  # 设置文件扩展名过滤,注意用双分号间隔
        ConfigVar.keilUV4_path = fileName1
        self.check()

    def save_keil(self):
        if self.UVpath.text() == "" or self.pypath.text() == "":
            msg = MyMessage()
            msg.btn_one(MyMessage.error,'path',":/req/Create a new project/Yun.png")
        else:
            config = configparser.ConfigParser()
            config.read(ConfigVar.config_path_hash)
            ConfigVar.python_path = self.pypath.text().replace("/Program Files/", "/\"Program Files\"/")
            ConfigVar.keilUV4_path = self.UVpath.text().replace("/Program Files/", "/\"Program Files\"/")
            ConfigVar.path_flag = 'true'
            config.set('installation', 'python_path', ConfigVar.python_path)
            config.set('installation', 'keilUV4_path', ConfigVar.keilUV4_path)
            config.set('installation', 'path_flag',ConfigVar.path_flag)
            with open(ConfigVar.config_path_hash, 'w') as f:
                config.write(f)

            msg = MyMessage()
            msg.btn_one(MyMessage.none, 'set', ":/req/Create a new project/Yun.png")
            # print(ConfigVar.python_path)
            # print(ConfigVar.keilUV4_path)
            info("ConfigVar.python_path= %s  ConfigVar.keilUV4_path=%s",ConfigVar.python_path,ConfigVar.keilUV4_path)
            self.hide()

    # 退出函数，可以在子窗口的代码中创建指向此函数的事件。
    def Close(self):
        if ConfigVar.language == 'zh_cn':
            reply = QMessageBox.question(self, '确认框', '确认退出吗？',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        elif ConfigVar.language == 'cn':
            reply = QMessageBox.question(self, '確認框', '確認退出碼？',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        else:
            reply = QMessageBox.question(self, 'confirmation', 'Are you sure you want to exit?',
                                         QMessageBox.Yes | QMessageBox.No, QMessageBox.Yes)
        if reply == QMessageBox.Yes:
            self.hide()
        else:
            pass


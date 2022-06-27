import configparser
import os
import traceback
from MyLog import info, error
from PyQt5.QtCore import QTranslator, pyqtSignal
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox, QApplication
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from MessageWindow import MyMessage
from UI import demo


# choose demo子窗口
class DemoWindow(QMainWindow, demo.Ui_Dialog):
    backsig = pyqtSignal()

    def __init__(self):
        super(DemoWindow, self).__init__()
        self.setupUi(self)
        ConfigVar.readconf(self)
        self.trans = QTranslator()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)

    def back(self):
        self.backsig.emit()
        self.close()

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(DemoWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/DemoWindow_en")
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
            self.trans.load("./translator/DemoWindow_zh_cn")
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
            self.trans.load("./translator/DemoWindow_cn")
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

    def create_project(self):
        ConfigVar.project.id = str(ConfigVar.ID)
        ConfigVar.ID += 1
        config = configparser.ConfigParser()
        config.read(ConfigVar.config_path_hash)
        config.set('installation', 'ID', str(ConfigVar.ID))
        with open(ConfigVar.config_path_hash, 'w') as f:
            config.write(f)
        # print("python_path   " + ConfigVar.python_path)
        # print("keilUV4_path     " + ConfigVar.keilUV4_path)
        # print("project.name      " + ConfigVar.project.name)
        # print("project.path      " + ConfigVar.project.path)
        # print("project.id      " + ConfigVar.project.id)

        info("python_path   " + ConfigVar.python_path)
        info("keilUV4_path     " + ConfigVar.keilUV4_path)
        info("project.name      " + ConfigVar.project.name)
        info("project.path      " + ConfigVar.project.path)
        info("project.id      " + ConfigVar.project.id)
        if self.radioButton_2.isChecked():
            # print(self.radioButton_2.text())
            ConfigVar.project.type = self.radioButton_2.text()
            info("ConfigVar.project.type      " + self.radioButton_2.text())
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
                    cmd = "\"" + ConfigVar.python_path + "\" " + "./compose.py " + " -a USBV1.0" + " -o " + ConfigVar.project.name + " -p " + ConfigVar.project.path + " -m " + \
                          local['button']
                    # print(cmd)
                    info("os.system---(%s)", cmd)
                    os.system(cmd)
                    outdir = r"\out\USBV1.0\\" + ConfigVar.project.name + "\Projects" + "\\"
                    if local['button'] == 'CDC_HID_Composite':
                        cmd = ConfigVar.keilUV4_path + " " + ConfigVar.project.path + outdir + ConfigVar.project.name + "\\" + \
                              local['button'] + "\\" + "MDK-ARM" + "\\" + ConfigVar.uvprojxmap[local['button']]
                        ConfigVar.project.path = cmd.split(' ')[1].split('\MDK-ARM')[0].replace('\\', '/')
                        ConfigVar.mainWindow.trigger.emit(cmd)
                        self.close()
                        # os.system(
                        #     ConfigVar.keilUV4_path + " " + ConfigVar.project.path + outdir + "\\" + "Composite_Examples" + "\\" +
                        #     local['button'] + "\\" + "MDK-ARM" + "\\" + ConfigVar.uvprojxmap[local['button']])
                    else:
                        cmd = ConfigVar.keilUV4_path + " " + ConfigVar.project.path + outdir + ConfigVar.project.name + "\\" + "MDK-ARM" + "\\" + \
                              ConfigVar.uvprojxmap[local['button']]
                        ConfigVar.project.path = cmd.split(' ')[1].split('\MDK-ARM')[0].replace('\\', '/')
                        ConfigVar.mainWindow.trigger.emit(cmd)
                        self.close()
                        # os.system(ConfigVar.keilUV4_path + " " + ConfigVar.project.path + outdir + local[
                        #     'button'] + "\\" + "MDK-ARM" + "\\" + ConfigVar.uvprojxmap[local['button']])
                    break
        else:
            # print(self.radioButton.text())
            ConfigVar.project.type = self.radioButton.text()
            info("ConfigVar.project.type      " + self.radioButton.text())
            demo = []
            for i in range(42, 63):
                cmd = "button= self.checkBox_" + str(i) + ".isChecked()"
                local = {}
                exec(cmd, {'self': self}, local)
                if local['button']:
                    cmd = "button= self.checkBox_" + str(i) + ".text()"
                    local = {}
                    exec(cmd, {'self': self}, local)
                    demo.append(local['button'])
            ConfigVar.project.demo = demo
            if demo.__len__() > 0:
                cmd = "\"" + ConfigVar.python_path + "\" " + "./compose.py " + " -a V1.35" + " -o " + ConfigVar.project.name + " -p " + ConfigVar.project.path
                for demoname in demo:
                    cmd += " -m " + demoname
                # print("cmd = -------" + cmd)
                info("os.system---(%s)", cmd)
                os.system(cmd)
                cmd = ConfigVar.keilUV4_path + " " + ConfigVar.project.path + "\out\V1.35\\" + ConfigVar.project.name + "\Projects" + "\\" + ConfigVar.project.name + "\MDK-ARM\Project.uvprojx"
                ConfigVar.project.path = cmd.split(' ')[1].split('\MDK-ARM')[0].replace('\\', '/')
                ConfigVar.mainWindow.trigger.emit(cmd)
                self.close()
                # os.system(
                #     ConfigVar.keilUV4_path + " " + ConfigVar.project.path + "\out\V1.35\Projects" + "\\" + ConfigVar.project.name + "\MDK-ARM\Project.uvprojx")
            else:
                msg = MyMessage()
                msg.btn_one(MyMessage.error, 'demo', ":/req/Create a new project/Yun.png")
        try:
            if ConfigVar.project.chip == 'VTM071X':
                # print('刷新 VTM2071X')
                info('刷新 VTM2071X')
                ConfigVar.mainWindow.chipBox.setCurrentIndex(0)
                if ConfigVar.mainWindow.Allbutton.isChecked():
                    ConfigVar.mainWindow.Allbutton.click()
                ConfigVar.mainWindow.Allbutton.click()
            elif ConfigVar.project.chip == 'VTM32030X':
                ConfigVar.mainWindow.chipBox.setCurrentIndex(1)
                if ConfigVar.mainWindow.Allbutton.isChecked():
                    ConfigVar.mainWindow.Allbutton.click()
                ConfigVar.mainWindow.Allbutton.click()
                # print('刷新 VTM32030X')
                info('刷新 VTM32030X')
        except Exception as e:
            traceback.print_exc()
            error(e)
        ConfigVar.project.clear()

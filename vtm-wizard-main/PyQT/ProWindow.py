import configparser
import os
import subprocess
import traceback
from functools import partial
from MyLog import info, error
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import pyqtSignal
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMainWindow, QMessageBox

from ConfigVar import ConfigVar, ProjectMess
from UI import created
from ProFrame import ProFrame


# 内嵌窗口
class ProWindow(QMainWindow, created.Ui_Form):
    refreshsig = pyqtSignal()
    searchsig = pyqtSignal(str)
    showallsig = pyqtSignal()
    resizesig = pyqtSignal(str)

    def __init__(self):
        self.button = []
        self.projects = []
        self.i = 0
        self.j = 0
        self.num = 2
        self.nnum = 2
        self.resizestr = ConfigVar.mainwindowsize
        super(ProWindow, self).__init__()
        self.setupUi(self)
        self.refreshsig.connect(self.hide)
        ConfigVar.readconf(self)
        self.searchsig.connect(self.search)
        self.showallsig.connect(self.showAll)
        self.resizesig.connect(self.resizewindow)
        self.resizewindow(self.resizestr)

    def showAll(self):
        try:
            if os.path.exists(ConfigVar.project_path_hash):
                config = configparser.ConfigParser()
                config.read(ConfigVar.project_path_hash)
                ids = config.options('name')
                self.button.clear()
                for id in ids:
                    project = ProjectMess()
                    project.read(id, config)
                    # print("showAll  " + id + ": " + project.path)
                    self.gridLayout.setRowStretch(5, 5)
                    self.gridLayout.setColumnStretch(5, 5)
                    if ConfigVar.projectchip == 'VTM071X.all' or ConfigVar.projectchip == 'VTM071X.keil':
                        self.projects.append(project)
                        self.pushButton = ProFrame(project)
                        self.gridLayout.addWidget(self.pushButton, self.j, self.i, 1, 1,
                                                  QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)
                        self.pushButton.show()
                        self.i += 1
                        if self.i >= self.num:
                            self.j += 1
                            self.i = self.i % self.num
                        self.button.append(self.pushButton)

                # print("全部的 button里面有 %d个按钮",self.button.__len__())
                info("全部显示项目里面有 %d个按钮", self.button.__len__())
            else:
                info("缺少project.ini")

        except Exception as e:
            traceback.print_exc()
            error(e)

    def search(self, str):
        try:
            if os.path.exists(ConfigVar.project_path_hash):
                config = configparser.ConfigParser()
                config.read(ConfigVar.project_path_hash)
                ids = config.options('name')
                self.button.clear()
                if ConfigVar.projectchip == 'VTM071X.all' or ConfigVar.projectchip == 'VTM071X.keil':
                    for id in ids:
                        project = ProjectMess()
                        project.read(id, config)
                        # print("showAll  " + id + ": " + project.path)
                        self.gridLayout.setRowStretch(5, 5)
                        self.gridLayout.setColumnStretch(5, 5)
                        for demo in project.demo:
                            if str.lower() in demo.lower():
                                self.projects.append(project)
                                self.pushButton = ProFrame(project)
                                self.gridLayout.addWidget(self.pushButton, self.j, self.i, 1, 1,
                                                          QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)

                                self.pushButton.show()
                                self.i += 1
                                if self.i >= self.num:
                                    self.j += 1
                                    self.i = self.i % self.num
                                self.button.append(self.pushButton)
                                break
                    # print("查找到的 button里面有 %d个按钮", self.button.__len__())
                    info("查找到的显示项目里面有 %d个按钮", self.button.__len__())
            else:
                info("缺少project.ini")

        except Exception as e:
            traceback.print_exc()
            error(e)

    def resizewindow(self, str):
        try:
            if str == '':
                str = '[0,0]'
            # print('resizewindow  --  str = ',end=' ')
            # print(str)
            info("窗口变更大小 " + str)
            self.resizestr = str
            self.i = 0
            self.j = 0

            size = eval(str)
            # print(size)
            self.scrollArea.setGeometry(20, 10, 746 + size[0], 492 + size[1])
            self.nnum = int((740 + size[0]) / 332)
            # print(self.nnum)
            info("一行显示 %d 个按钮", self.nnum)
            if self.nnum != self.num:
                self.num = self.nnum
                self.gridLayout.setRowStretch(5, 5)
                self.gridLayout.setColumnStretch(5, 5)
                # for i in range(self.gridLayout.count()):
                #     self.gridLayout.itemAt(i).widget().deleteLater()
                for button in self.button:
                    # print(self.i, self.j)
                    self.gridLayout.addWidget(button, self.j, self.i, 1, 1, QtCore.Qt.AlignLeft | QtCore.Qt.AlignTop)
                    button.show()
                    self.i += 1
                    if self.i >= self.num:
                        self.j += 1
                        self.i = self.i % self.num
        except Exception as e:
            traceback.print_exc()
            error(e)

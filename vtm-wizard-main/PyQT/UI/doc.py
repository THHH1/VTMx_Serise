# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'doc.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Dialog(object):
    def setupUi(self, Dialog):
        Dialog.setObjectName("Dialog")
        Dialog.setWindowModality(QtCore.Qt.ApplicationModal)
        Dialog.resize(654, 465)
        Dialog.setMinimumSize(QtCore.QSize(654, 465))
        Dialog.setMaximumSize(QtCore.QSize(654, 465))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        Dialog.setFont(font)
        Dialog.setMouseTracking(True)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/req/Create a new project/Yun.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Dialog.setWindowIcon(icon)
        self.pushButton = QtWidgets.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(400, 400, 100, 30))
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(520, 400, 100, 30))
        self.pushButton_2.setObjectName("pushButton_2")
        self.label = QtWidgets.QLabel(Dialog)
        self.label.setGeometry(QtCore.QRect(30, 20, 131, 333))
        self.label.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.label.setText("")
        self.label.setObjectName("label")
        self.label_2 = QtWidgets.QLabel(Dialog)
        self.label_2.setGeometry(QtCore.QRect(181, 20, 451, 333))
        self.label_2.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.label_2.setText("")
        self.label_2.setObjectName("label_2")
        self.chiplist = QtWidgets.QListWidget(Dialog)
        self.chiplist.setGeometry(QtCore.QRect(30, 20, 131, 331))
        self.chiplist.setObjectName("chiplist")
        self.doclist = QtWidgets.QListWidget(Dialog)
        self.doclist.setGeometry(QtCore.QRect(180, 20, 451, 331))
        self.doclist.setObjectName("doclist")
        self.label.raise_()
        self.label_2.raise_()
        self.pushButton.raise_()
        self.pushButton_2.raise_()
        self.chiplist.raise_()
        self.doclist.raise_()

        self.retranslateUi(Dialog)
        self.pushButton_2.clicked.connect(Dialog.close)
        self.pushButton.clicked.connect(Dialog.clickopendoc)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        _translate = QtCore.QCoreApplication.translate
        Dialog.setWindowTitle(_translate("Dialog", "Documents"))
        self.pushButton.setText(_translate("Dialog", "OK"))
        self.pushButton_2.setText(_translate("Dialog", "Cancel"))
import req_rc

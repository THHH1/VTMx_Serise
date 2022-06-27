# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'project.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.setWindowModality(QtCore.Qt.NonModal)
        Form.resize(448, 240)
        Form.setMinimumSize(QtCore.QSize(332, 176))
        Form.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self.widget = QtWidgets.QWidget(Form)
        self.widget.setGeometry(QtCore.QRect(0, 0, 332, 176))
        self.widget.setMinimumSize(QtCore.QSize(332, 176))
        self.widget.setContextMenuPolicy(QtCore.Qt.CustomContextMenu)
        self.widget.setStyleSheet("")
        self.widget.setObjectName("widget")
        self.path = QtWidgets.QLabel(self.widget)
        self.path.setGeometry(QtCore.QRect(70, 50, 191, 16))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.path.setFont(font)
        self.path.setObjectName("path")
        self.demo = QtWidgets.QTextBrowser(self.widget)
        self.demo.setGeometry(QtCore.QRect(30, 75, 271, 81))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setKerning(True)
        self.demo.setFont(font)
        self.demo.setMouseTracking(False)
        self.demo.setTabletTracking(False)
        self.demo.setContextMenuPolicy(QtCore.Qt.ActionsContextMenu)
        self.demo.setStyleSheet("border:none;")
        self.demo.setOpenLinks(False)
        self.demo.setObjectName("demo")
        self.label = QtWidgets.QLabel(self.widget)
        self.label.setGeometry(QtCore.QRect(27, 27, 31, 31))
        self.label.setStyleSheet("border-image: url(:/req/YunWizard-v5.7.0/组 14.png);")
        self.label.setText("")
        self.label.setObjectName("label")
        self.buttonname = QtWidgets.QPushButton(self.widget)
        self.buttonname.setGeometry(QtCore.QRect(63, 21, 171, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setBold(True)
        font.setUnderline(True)
        font.setWeight(75)
        self.buttonname.setFont(font)
        self.buttonname.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.buttonname.setFocusPolicy(QtCore.Qt.WheelFocus)
        self.buttonname.setStyleSheet("text-align:left;")
        self.buttonname.setFlat(True)
        self.buttonname.setObjectName("buttonname")
        self.label_2 = QtWidgets.QLabel(self.widget)
        self.label_2.setGeometry(QtCore.QRect(31, 68, 271, 3))
        self.label_2.setStyleSheet("background-color: rgb(167, 167, 167);")
        self.label_2.setText("")
        self.label_2.setObjectName("label_2")
        self.blo = QtWidgets.QLabel(self.widget)
        self.blo.setGeometry(QtCore.QRect(0, 0, 332, 176))
        self.blo.setStyleSheet("background-color:rgb(249,249,249);\n"
"\n"
"border-radius: 10px;  border: 2px groove gray;\n"
"\n"
"font: 9pt \"AcadEref\";\n"
"border-style: outset;")
        self.blo.setText("")
        self.blo.setObjectName("blo")
        self.blo.raise_()
        self.path.raise_()
        self.demo.raise_()
        self.label.raise_()
        self.buttonname.raise_()
        self.label_2.raise_()

        self.retranslateUi(Form)
        self.widget.customContextMenuRequested['QPoint'].connect(Form.myListWidgetContext)
        self.buttonname.clicked.connect(Form.openproject)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.path.setText(_translate("Form", "TextLabel"))
        self.buttonname.setText(_translate("Form", "PushButton"))
import req_rc

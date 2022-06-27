# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'createVTM.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_chip(object):
    def setupUi(self, chip):
        chip.setObjectName("chip")
        chip.setWindowModality(QtCore.Qt.ApplicationModal)
        chip.resize(654, 456)
        chip.setMinimumSize(QtCore.QSize(654, 456))
        chip.setMaximumSize(QtCore.QSize(654, 456))
        chip.setMouseTracking(True)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/req/Create a new project/Yun.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        chip.setWindowIcon(icon)
        self.tableView_2 = QtWidgets.QTableView(chip)
        self.tableView_2.setGeometry(QtCore.QRect(21, 77, 608, 203))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.tableView_2.setFont(font)
        self.tableView_2.setObjectName("tableView_2")
        self.pushButton_6 = QtWidgets.QPushButton(chip)
        self.pushButton_6.setEnabled(False)
        self.pushButton_6.setGeometry(QtCore.QRect(549, 400, 72, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_6.setFont(font)
        self.pushButton_6.setLayoutDirection(QtCore.Qt.LeftToRight)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 4_slices/对号-加粗.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_6.setIcon(icon1)
        self.pushButton_6.setObjectName("pushButton_6")
        self.pushButton_3 = QtWidgets.QPushButton(chip)
        self.pushButton_3.setGeometry(QtCore.QRect(8, 400, 72, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_3.setFont(font)
        self.pushButton_3.setLayoutDirection(QtCore.Qt.LeftToRight)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 4_slices/叉叉.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_3.setIcon(icon2)
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_4 = QtWidgets.QPushButton(chip)
        self.pushButton_4.setGeometry(QtCore.QRect(418, 400, 72, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_4.setFont(font)
        self.pushButton_4.setLayoutDirection(QtCore.Qt.RightToLeft)
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 4_slices/下一步@2x.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_4.setIcon(icon3)
        self.pushButton_4.setObjectName("pushButton_4")
        self.tableView = QtWidgets.QTableView(chip)
        self.tableView.setGeometry(QtCore.QRect(6, 62, 638, 330))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.tableView.setFont(font)
        self.tableView.setObjectName("tableView")
        self.label_2 = QtWidgets.QLabel(chip)
        self.label_2.setGeometry(QtCore.QRect(56, 86, 80, 16))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.label = QtWidgets.QLabel(chip)
        self.label.setGeometry(QtCore.QRect(16, 16, 211, 41))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(16)
        font.setBold(True)
        font.setItalic(False)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.label_3 = QtWidgets.QLabel(chip)
        self.label_3.setGeometry(QtCore.QRect(30, 90, 16, 16))
        self.label_3.setStyleSheet("border-image: url(:/req/update/微芯片.png);")
        self.label_3.setText("")
        self.label_3.setObjectName("label_3")
        self.VTM32030X = QtWidgets.QPushButton(chip)
        self.VTM32030X.setEnabled(True)
        self.VTM32030X.setGeometry(QtCore.QRect(40, 140, 561, 32))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setKerning(False)
        self.VTM32030X.setFont(font)
        self.VTM32030X.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.VTM32030X.setMouseTracking(False)
        self.VTM32030X.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.VTM32030X.setStyleSheet("text-align:left;")
        self.VTM32030X.setCheckable(True)
        self.VTM32030X.setChecked(False)
        self.VTM32030X.setAutoExclusive(True)
        self.VTM32030X.setFlat(True)
        self.VTM32030X.setObjectName("VTM32030X")
        self.VTM071X = QtWidgets.QPushButton(chip)
        self.VTM071X.setEnabled(True)
        self.VTM071X.setGeometry(QtCore.QRect(40, 110, 561, 32))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setKerning(False)
        self.VTM071X.setFont(font)
        self.VTM071X.setCursor(QtGui.QCursor(QtCore.Qt.PointingHandCursor))
        self.VTM071X.setMouseTracking(False)
        self.VTM071X.setStyleSheet("text-align:left;")
        self.VTM071X.setCheckable(True)
        self.VTM071X.setChecked(False)
        self.VTM071X.setAutoExclusive(True)
        self.VTM071X.setFlat(True)
        self.VTM071X.setObjectName("VTM071X")
        self.tableView.raise_()
        self.tableView_2.raise_()
        self.pushButton_6.raise_()
        self.pushButton_3.raise_()
        self.pushButton_4.raise_()
        self.label_2.raise_()
        self.label.raise_()
        self.label_3.raise_()
        self.VTM32030X.raise_()
        self.VTM071X.raise_()

        self.retranslateUi(chip)
        self.pushButton_3.clicked.connect(chip.hide)
        self.pushButton_4.clicked.connect(chip.newImage)
        QtCore.QMetaObject.connectSlotsByName(chip)

    def retranslateUi(self, chip):
        _translate = QtCore.QCoreApplication.translate
        chip.setWindowTitle(_translate("chip", "Choose  Chip Type"))
        self.pushButton_6.setText(_translate("chip", "Create"))
        self.pushButton_3.setText(_translate("chip", "Cancel"))
        self.pushButton_4.setText(_translate("chip", "Next"))
        self.label_2.setText(_translate("chip", "chip types"))
        self.label.setText(_translate("chip", "Chip Type"))
        self.VTM32030X.setText(_translate("chip", "VTM030X"))
        self.VTM071X.setText(_translate("chip", "VTM071X"))
import req_rc

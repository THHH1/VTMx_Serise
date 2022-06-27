# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'chip.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Chip(object):
    def setupUi(self, Chip):
        Chip.setObjectName("Chip")
        Chip.resize(1216, 713)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/req/Create a new project/Yun.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Chip.setWindowIcon(icon)
        self.text32030x = QtWidgets.QTextEdit(Chip)
        self.text32030x.setGeometry(QtCore.QRect(20, 10, 746, 492))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(14)
        font.setBold(False)
        font.setWeight(50)
        self.text32030x.setFont(font)
        self.text32030x.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)
        self.text32030x.setStyleSheet("\n"
"border-image: url(:/req/update/自定义大小 – 2_slices/1.png);")
        self.text32030x.setMidLineWidth(0)
        self.text32030x.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.text32030x.setLineWrapMode(QtWidgets.QTextEdit.WidgetWidth)
        self.text32030x.setObjectName("text32030x")
        self.tableView = QtWidgets.QTableView(Chip)
        self.tableView.setGeometry(QtCore.QRect(20, 10, 746, 492))
        self.tableView.setObjectName("tableView")
        self.text071x = QtWidgets.QTextEdit(Chip)
        self.text071x.setGeometry(QtCore.QRect(20, 10, 746, 492))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(14)
        font.setBold(False)
        font.setWeight(50)
        self.text071x.setFont(font)
        self.text071x.setContextMenuPolicy(QtCore.Qt.DefaultContextMenu)
        self.text071x.setStyleSheet("\n"
"border-image: url(:/req/update/自定义大小 – 2_slices/1.png);")
        self.text071x.setMidLineWidth(0)
        self.text071x.setVerticalScrollBarPolicy(QtCore.Qt.ScrollBarAlwaysOff)
        self.text071x.setLineWrapMode(QtWidgets.QTextEdit.WidgetWidth)
        self.text071x.setObjectName("text071x")
        self.tableView.raise_()
        self.text32030x.raise_()
        self.text071x.raise_()

        self.retranslateUi(Chip)
        QtCore.QMetaObject.connectSlotsByName(Chip)

    def retranslateUi(self, Chip):
        _translate = QtCore.QCoreApplication.translate
        Chip.setWindowTitle(_translate("Chip", "Chips"))
        self.text32030x.setHtml(_translate("Chip", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'微软雅黑\'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">VTM030X </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">运行频率可以达到 84MHZ</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">工作电压 2.0V ~ 5.5V</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">X 内嵌 128K 字节的 Flash 存储器，其中用户可用空间为 120KB，以及 16K 字节的 SRAM 存储器</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">包含许多系统级外设功能，如高速通用 I/O 端口，4 通道DMA,Cordic 运算单元，USART，SPI，I2C，PWM，Motor-PWM，ADC，DAC，模拟比较器，看门狗定时器，RTC，欠压检测器等</span><span style=\" font-size:18pt;\"><br /></span></p></body></html>"))
        self.text071x.setHtml(_translate("Chip", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:\'微软雅黑\'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:16pt; font-weight:600;\">VTM071X </span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">运行频率可以达到 84MHZ</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">工作电压 2.0V ~ 5.5V</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">X 内嵌 128K 字节的 Flash 存储器，其中用户可用空间为 120KB，以及 16K 字节的 SRAM 存储器</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:12pt;\">包含许多系统级外设功能，如高速通用 I/O 端口，4 通道DMA,Cordic 运算单元，USART，SPI，I2C，PWM，Motor-PWM，ADC，DAC，模拟比较器，看门狗定时器，RTC，欠压检测器等</span><span style=\" font-size:18pt;\"><br /></span></p></body></html>"))
import req_rc
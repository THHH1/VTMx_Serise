# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'importdemo.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.setWindowModality(QtCore.Qt.ApplicationModal)
        Form.resize(654, 465)
        Form.setMinimumSize(QtCore.QSize(654, 465))
        Form.setMaximumSize(QtCore.QSize(654, 465))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        Form.setFont(font)
        Form.setMouseTracking(False)
        icon = QtGui.QIcon()
        icon.addPixmap(QtGui.QPixmap(":/req/Create a new project/Yun.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        Form.setWindowIcon(icon)
        self.scrollArea_2 = QtWidgets.QScrollArea(Form)
        self.scrollArea_2.setGeometry(QtCore.QRect(294, 114, 331, 265))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.scrollArea_2.setFont(font)
        self.scrollArea_2.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.scrollArea_2.setWidgetResizable(True)
        self.scrollArea_2.setObjectName("scrollArea_2")
        self.scrollAreaWidgetContents_2 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_2.setGeometry(QtCore.QRect(0, 0, 329, 263))
        self.scrollAreaWidgetContents_2.setObjectName("scrollAreaWidgetContents_2")
        self.verticalLayoutWidget = QtWidgets.QWidget(self.scrollAreaWidgetContents_2)
        self.verticalLayoutWidget.setGeometry(QtCore.QRect(30, 0, 271, 251))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.verticalLayoutWidget.setFont(font)
        self.verticalLayoutWidget.setObjectName("verticalLayoutWidget")
        self.verticalLayout = QtWidgets.QVBoxLayout(self.verticalLayoutWidget)
        self.verticalLayout.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout.setObjectName("verticalLayout")
        self.radioButton_11 = QtWidgets.QRadioButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_11.setFont(font)
        self.radioButton_11.setChecked(True)
        self.radioButton_11.setObjectName("radioButton_11")
        self.verticalLayout.addWidget(self.radioButton_11)
        self.radioButton_9 = QtWidgets.QRadioButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_9.setFont(font)
        self.radioButton_9.setObjectName("radioButton_9")
        self.verticalLayout.addWidget(self.radioButton_9)
        self.radioButton_10 = QtWidgets.QRadioButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_10.setFont(font)
        self.radioButton_10.setObjectName("radioButton_10")
        self.verticalLayout.addWidget(self.radioButton_10)
        self.radioButton_8 = QtWidgets.QRadioButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_8.setFont(font)
        self.radioButton_8.setObjectName("radioButton_8")
        self.verticalLayout.addWidget(self.radioButton_8)
        self.radioButton_7 = QtWidgets.QRadioButton(self.verticalLayoutWidget)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_7.setFont(font)
        self.radioButton_7.setObjectName("radioButton_7")
        self.verticalLayout.addWidget(self.radioButton_7)
        self.radioButton_7.raise_()
        self.radioButton_8.raise_()
        self.radioButton_10.raise_()
        self.radioButton_11.raise_()
        self.radioButton_9.raise_()
        self.scrollArea_2.setWidget(self.scrollAreaWidgetContents_2)
        self.pushButton_3 = QtWidgets.QPushButton(Form)
        self.pushButton_3.setGeometry(QtCore.QRect(12, 393, 81, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_3.setFont(font)
        icon1 = QtGui.QIcon()
        icon1.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 4_slices/叉叉.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_3.setIcon(icon1)
        self.pushButton_3.setObjectName("pushButton_3")
        self.listView = QtWidgets.QListView(Form)
        self.listView.setGeometry(QtCore.QRect(31, 82, 189, 297))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.listView.setFont(font)
        self.listView.setObjectName("listView")
        self.label_3 = QtWidgets.QLabel(Form)
        self.label_3.setGeometry(QtCore.QRect(102, 92, 41, 16))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(9)
        self.label_3.setFont(font)
        self.label_3.setObjectName("label_3")
        self.listView_2 = QtWidgets.QListView(Form)
        self.listView_2.setGeometry(QtCore.QRect(294, 82, 331, 297))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.listView_2.setFont(font)
        self.listView_2.setObjectName("listView_2")
        self.label_4 = QtWidgets.QLabel(Form)
        self.label_4.setGeometry(QtCore.QRect(47, 108, 19, 19))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.label_4.setFont(font)
        self.label_4.setStyleSheet("border-image: url(:/new/YunWizard-v5.7.0/未标题-1.png);")
        self.label_4.setText("")
        self.label_4.setObjectName("label_4")
        self.scrollArea_3 = QtWidgets.QScrollArea(Form)
        self.scrollArea_3.setGeometry(QtCore.QRect(294, 114, 331, 265))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.scrollArea_3.setFont(font)
        self.scrollArea_3.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.scrollArea_3.setWidgetResizable(False)
        self.scrollArea_3.setObjectName("scrollArea_3")
        self.scrollAreaWidgetContents_3 = QtWidgets.QWidget()
        self.scrollAreaWidgetContents_3.setGeometry(QtCore.QRect(0, 0, 309, 759))
        self.scrollAreaWidgetContents_3.setObjectName("scrollAreaWidgetContents_3")
        self.verticalLayoutWidget_2 = QtWidgets.QWidget(self.scrollAreaWidgetContents_3)
        self.verticalLayoutWidget_2.setGeometry(QtCore.QRect(30, 10, 293, 711))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.verticalLayoutWidget_2.setFont(font)
        self.verticalLayoutWidget_2.setObjectName("verticalLayoutWidget_2")
        self.verticalLayout_2 = QtWidgets.QVBoxLayout(self.verticalLayoutWidget_2)
        self.verticalLayout_2.setContentsMargins(0, 0, 0, 0)
        self.verticalLayout_2.setObjectName("verticalLayout_2")
        self.checkBox_60 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_60.setFont(font)
        self.checkBox_60.setObjectName("checkBox_60")
        self.verticalLayout_2.addWidget(self.checkBox_60)
        self.checkBox_47 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_47.setFont(font)
        self.checkBox_47.setObjectName("checkBox_47")
        self.verticalLayout_2.addWidget(self.checkBox_47)
        self.checkBox_54 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_54.setFont(font)
        self.checkBox_54.setObjectName("checkBox_54")
        self.verticalLayout_2.addWidget(self.checkBox_54)
        self.checkBox_46 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_46.setFont(font)
        self.checkBox_46.setObjectName("checkBox_46")
        self.verticalLayout_2.addWidget(self.checkBox_46)
        self.checkBox_42 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_42.setFont(font)
        self.checkBox_42.setObjectName("checkBox_42")
        self.verticalLayout_2.addWidget(self.checkBox_42)
        self.checkBox_50 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_50.setFont(font)
        self.checkBox_50.setObjectName("checkBox_50")
        self.verticalLayout_2.addWidget(self.checkBox_50)
        self.checkBox_55 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_55.setFont(font)
        self.checkBox_55.setObjectName("checkBox_55")
        self.verticalLayout_2.addWidget(self.checkBox_55)
        self.checkBox_48 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_48.setFont(font)
        self.checkBox_48.setObjectName("checkBox_48")
        self.verticalLayout_2.addWidget(self.checkBox_48)
        self.checkBox_62 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_62.setFont(font)
        self.checkBox_62.setObjectName("checkBox_62")
        self.verticalLayout_2.addWidget(self.checkBox_62)
        self.checkBox_44 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_44.setFont(font)
        self.checkBox_44.setObjectName("checkBox_44")
        self.verticalLayout_2.addWidget(self.checkBox_44)
        self.checkBox_58 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_58.setFont(font)
        self.checkBox_58.setObjectName("checkBox_58")
        self.verticalLayout_2.addWidget(self.checkBox_58)
        self.checkBox_59 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_59.setFont(font)
        self.checkBox_59.setObjectName("checkBox_59")
        self.verticalLayout_2.addWidget(self.checkBox_59)
        self.checkBox_45 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_45.setFont(font)
        self.checkBox_45.setObjectName("checkBox_45")
        self.verticalLayout_2.addWidget(self.checkBox_45)
        self.checkBox_43 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_43.setFont(font)
        self.checkBox_43.setObjectName("checkBox_43")
        self.verticalLayout_2.addWidget(self.checkBox_43)
        self.checkBox_52 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_52.setFont(font)
        self.checkBox_52.setObjectName("checkBox_52")
        self.verticalLayout_2.addWidget(self.checkBox_52)
        self.checkBox_51 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_51.setFont(font)
        self.checkBox_51.setObjectName("checkBox_51")
        self.verticalLayout_2.addWidget(self.checkBox_51)
        self.checkBox_57 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_57.setFont(font)
        self.checkBox_57.setObjectName("checkBox_57")
        self.verticalLayout_2.addWidget(self.checkBox_57)
        self.checkBox_61 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_61.setFont(font)
        self.checkBox_61.setObjectName("checkBox_61")
        self.verticalLayout_2.addWidget(self.checkBox_61)
        self.checkBox_49 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_49.setFont(font)
        self.checkBox_49.setObjectName("checkBox_49")
        self.verticalLayout_2.addWidget(self.checkBox_49)
        self.checkBox_53 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_53.setFont(font)
        self.checkBox_53.setObjectName("checkBox_53")
        self.verticalLayout_2.addWidget(self.checkBox_53)
        self.checkBox_56 = QtWidgets.QCheckBox(self.verticalLayoutWidget_2)
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.checkBox_56.setFont(font)
        self.checkBox_56.setObjectName("checkBox_56")
        self.verticalLayout_2.addWidget(self.checkBox_56)
        self.scrollArea_3.setWidget(self.scrollAreaWidgetContents_3)
        self.tableView = QtWidgets.QTableView(Form)
        self.tableView.setGeometry(QtCore.QRect(10, 61, 638, 330))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.tableView.setFont(font)
        self.tableView.setObjectName("tableView")
        self.label = QtWidgets.QLabel(Form)
        self.label.setGeometry(QtCore.QRect(20, 10, 221, 51))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(16)
        font.setBold(True)
        font.setItalic(False)
        font.setWeight(75)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.widget = QtWidgets.QWidget(Form)
        self.widget.setGeometry(QtCore.QRect(64, 124, 120, 80))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.widget.setFont(font)
        self.widget.setObjectName("widget")
        self.radioButton = QtWidgets.QRadioButton(self.widget)
        self.radioButton.setEnabled(True)
        self.radioButton.setGeometry(QtCore.QRect(10, 0, 81, 30))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton.setFont(font)
        self.radioButton.setChecked(True)
        self.radioButton.setObjectName("radioButton")
        self.radioButton_2 = QtWidgets.QRadioButton(self.widget)
        self.radioButton_2.setGeometry(QtCore.QRect(10, 20, 91, 30))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.radioButton_2.setFont(font)
        self.radioButton_2.setObjectName("radioButton_2")
        self.label_5 = QtWidgets.QLabel(Form)
        self.label_5.setGeometry(QtCore.QRect(373, 92, 71, 20))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        font.setPointSize(9)
        self.label_5.setFont(font)
        self.label_5.setObjectName("label_5")
        self.pushButton_6 = QtWidgets.QPushButton(Form)
        self.pushButton_6.setGeometry(QtCore.QRect(553, 393, 91, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_6.setFont(font)
        self.pushButton_6.setLayoutDirection(QtCore.Qt.RightToLeft)
        icon2 = QtGui.QIcon()
        icon2.addPixmap(QtGui.QPixmap(":/新前缀/update/画板 – 4_slices/下一步.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_6.setIcon(icon2)
        self.pushButton_6.setObjectName("pushButton_6")
        self.label_2 = QtWidgets.QLabel(Form)
        self.label_2.setGeometry(QtCore.QRect(239, 229, 23, 21))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.label_2.setFont(font)
        self.label_2.setStyleSheet("border-image: url(:/req/Create a new project/箭头_向左两次.png);")
        self.label_2.setText("")
        self.label_2.setObjectName("label_2")
        self.pushButton_7 = QtWidgets.QPushButton(Form)
        self.pushButton_7.setEnabled(True)
        self.pushButton_7.setGeometry(QtCore.QRect(453, 393, 91, 28))
        font = QtGui.QFont()
        font.setFamily("微软雅黑")
        self.pushButton_7.setFont(font)
        self.pushButton_7.setStyleSheet("")
        icon3 = QtGui.QIcon()
        icon3.addPixmap(QtGui.QPixmap(":/req/update/画板 – 4_slices/下一步_slices/下一步.png"), QtGui.QIcon.Normal, QtGui.QIcon.Off)
        self.pushButton_7.setIcon(icon3)
        self.pushButton_7.setObjectName("pushButton_7")
        self.tableView.raise_()
        self.listView_2.raise_()
        self.scrollArea_2.raise_()
        self.scrollArea_3.raise_()
        self.pushButton_3.raise_()
        self.listView.raise_()
        self.label_3.raise_()
        self.label_4.raise_()
        self.label.raise_()
        self.widget.raise_()
        self.label_5.raise_()
        self.pushButton_6.raise_()
        self.label_2.raise_()
        self.pushButton_7.raise_()

        self.retranslateUi(Form)
        self.pushButton_3.clicked.connect(Form.close)
        self.pushButton_6.clicked.connect(Form.ImportPathImage)
        self.radioButton.toggled['bool'].connect(self.scrollArea_3.setVisible)
        self.radioButton_2.toggled['bool'].connect(self.scrollArea_3.setHidden)
        self.radioButton.toggled['bool'].connect(self.scrollArea_2.setHidden)
        self.radioButton_2.toggled['bool'].connect(self.scrollArea_2.setVisible)
        self.pushButton_7.clicked.connect(Form.back)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Import Project"))
        self.radioButton_11.setText(_translate("Form", "CDC_HID_Composite"))
        self.radioButton_9.setText(_translate("Form", "Custom_HID"))
        self.radioButton_10.setText(_translate("Form", "HID"))
        self.radioButton_8.setText(_translate("Form", "MSC"))
        self.radioButton_7.setText(_translate("Form", "Virtual_COM_Port"))
        self.pushButton_3.setText(_translate("Form", "Cancel"))
        self.label_3.setText(_translate("Form", "chip"))
        self.checkBox_60.setText(_translate("Form", "TIMER_Timer_and_PWM"))
        self.checkBox_47.setText(_translate("Form", "ACMP_DAC"))
        self.checkBox_54.setText(_translate("Form", "I2C_EEPROM"))
        self.checkBox_46.setText(_translate("Form", "FLASH_IAP"))
        self.checkBox_42.setText(_translate("Form", "ADC_Chip_Temperature"))
        self.checkBox_50.setText(_translate("Form", "ADC_Trigger"))
        self.checkBox_55.setText(_translate("Form", "TIMER_Breathing_Light"))
        self.checkBox_48.setText(_translate("Form", "ADC_Pin_Loop"))
        self.checkBox_62.setText(_translate("Form", "TIMER_PWM_and_Capture"))
        self.checkBox_44.setText(_translate("Form", "DeepSleep_PowerDown"))
        self.checkBox_58.setText(_translate("Form", "MCPWM_Complementary_waveform"))
        self.checkBox_59.setText(_translate("Form", "USART_RX_and_TX"))
        self.checkBox_45.setText(_translate("Form", "ADC_ADC_Watchdog"))
        self.checkBox_43.setText(_translate("Form", "DAC_DAC0_DAC1"))
        self.checkBox_52.setText(_translate("Form", "GPIO_LED_and_Key"))
        self.checkBox_51.setText(_translate("Form", "ADC_Pin_Interrupt"))
        self.checkBox_57.setText(_translate("Form", "SPI_SPI_FLASH"))
        self.checkBox_61.setText(_translate("Form", "RTC_Time"))
        self.checkBox_49.setText(_translate("Form", "DeepSleep_DeepSleep"))
        self.checkBox_53.setText(_translate("Form", "IWDG_Reset"))
        self.checkBox_56.setText(_translate("Form", "WWDG_Reset"))
        self.label.setText(_translate("Form", "Choose Modeules"))
        self.radioButton.setText(_translate("Form", "V1.35"))
        self.radioButton_2.setText(_translate("Form", "USBV1.0"))
        self.label_5.setText(_translate("Form", "modular"))
        self.pushButton_6.setText(_translate("Form", "Next"))
        self.pushButton_7.setText(_translate("Form", "Back"))
import req_rc

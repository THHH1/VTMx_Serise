import configparser
import os
import traceback
from functools import partial
from MyLog import info, error
from PyQt5.QtGui import QIcon
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from PyQt5.QtCore import pyqtSignal, pyqtSlot, QTimer, QTranslator
from PyQt5.QtWidgets import QWidget, QHBoxLayout, QPushButton, QMessageBox, QApplication, QListWidgetItem
from PyQt5 import QtWidgets

from MessageWindow import MyMessage
from UI import doc


#Documents窗口
class DocumentsWindow(QWidget, doc.Ui_Dialog):
    docsig = pyqtSignal(str)
    def __init__(self):
        self.chips = []
        self.docs = {}
        self.chipbuttons = []
        self.docbuttons = []
        super(DocumentsWindow, self).__init__()
        self.setupUi(self)
        self.getchip()
        self.docsig.connect(self.showdoc)
        self.trans = QTranslator()
        self.getchip()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
        else:
            self._trigger_english()
        super(DocumentsWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/DocumentsWindow_en")
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
            self.trans.load("./translator/DocumentsWindow_zh_cn")
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
            self.trans.load("./translator/DocumentsWindow_cn")
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



    def getchip(self):
        path = 'documents/'
        self.chips = os.listdir(path)
        for chip in self.chips:
            # print("chip ---------------")
            # print(chip)
            docpath = path +chip+'/'
            doc = os.listdir(docpath)
            self.docs[chip] = doc
            self.showchip()

    def showchip(self):
        try:
            self.chiplist.clear()
            i =0
            # print(self.docs.keys())
            for chip in self.docs.keys():
                self.chipButton = QtWidgets.QPushButton()
                self.chipButton.setCheckable(True)
                self.chipButton.setAutoExclusive(True)
                self.chipButton.setObjectName(chip)
                self.chipButton.setText(chip)
                self.chipButton.setFlat(True)
                self.chipButton.clicked.connect(partial(self.showdoc,chip))
                item = QListWidgetItem()
                self.chiplist.addItem(item)
                self.chiplist.setItemWidget(item,self.chipButton)

        except Exception as e:
            traceback.print_exc()
            error(e)
    def showdoc(self, chip):
        try:
            self.doclist.clear()
            i = 0
            # print('showdoc   '+chip)
            info('showdoc(%s)',chip)
            path = './documents/' + chip + '/'
            for doc in self.docs[chip]:
                docpath = path+doc
                # print(docpath)
                info('  showdocpath(%s)', docpath)
                self.docButton =QDoublePushButton()
                self.docButton.setCheckable(True)
                self.docButton.setAutoExclusive(True)
                self.docButton.setObjectName(doc)
                self.docButton.path = doc
                self.docButton.setText(doc[0:50])
                self.docButton.setFlat(True)
                self.docButton.doubleClicked.connect(partial(self.opendoc, docpath))
                item = QListWidgetItem()
                self.doclist.addItem(item)
                self.doclist.setItemWidget(item, self.docButton)
        except Exception as e:
            traceback.print_exc()
            error(e)

    def opendoc(self, str):
        ConfigVar.mainWindow.cmdsig.emit(str)
    def clickopendoc(self):
        chip_d = ''
        doc_d = ''
        try:
            # print("已选择",end=' ')
            for i in range(self.chiplist.count()):
                if self.chiplist.itemWidget(self.chiplist.item(i)).isChecked():
                    chip_d = self.chiplist.itemWidget(self.chiplist.item(i)).text()
                    # print(chip_d,end=' ')
                    break
            for i in range(self.doclist.count()):
                if self.doclist.itemWidget(self.doclist.item(i)).isChecked():
                    doc_d = self.doclist.itemWidget(self.doclist.item(i)).path
                    # print(doc_d)
                    break
            info('document 选中 (%s)->(%s)',chip_d,doc_d)
        except Exception as e:
            traceback.print_exc()
            error(e)
        if chip_d == '' or doc_d == '':
            msg = MyMessage()
            msg.btn_one(MyMessage.error, 'document', ":/req/Create a new project/Yun.png")

        else:
            cmd = './documents/' + chip_d + '/'+doc_d
            ConfigVar.mainWindow.cmdsig.emit(cmd)


class QDoublePushButton(QPushButton):
    doubleClicked = pyqtSignal()
    clicked = pyqtSignal()

    def __init__(self, *args, **kwargs):
        QPushButton.__init__(self, *args, **kwargs)
        self.path =' '
        self.timer = QTimer()
        self.timer.setSingleShot(True)
        self.timer.timeout.connect(self.clicked.emit)
        super().clicked.connect(self.checkDoubleClick)

    @pyqtSlot()
    def checkDoubleClick(self):
        if self.timer.isActive():
            self.doubleClicked.emit()
            self.timer.stop()
        else:
            self.timer.start(250)

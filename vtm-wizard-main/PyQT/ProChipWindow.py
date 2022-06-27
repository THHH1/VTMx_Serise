import traceback
from MyLog import info, error
from PyQt5.QtCore import pyqtSignal
from PyQt5.QtGui import QTextBlockFormat, QTextCursor
from PyQt5.QtWidgets import QWidget
from ConfigVar import ConfigVar
from UI import chip


# 芯片介绍子窗口
class ProChipWindow(QWidget, chip.Ui_Chip):
    refreshsig = pyqtSignal()
    chipsig = pyqtSignal(str)
    resizesig = pyqtSignal(str)

    def __init__(self):
        super(ProChipWindow, self).__init__()
        self.setupUi(self)
        self.refreshsig.connect(self.hide)
        self.chipsig.connect(self.chip)
        self.resizesig.connect(self.resizewindow)
        self.text32030x.setVisible(0)
        self.text071x.setViewportMargins(40,40,40,0)
        self.text32030x.setViewportMargins(40, 40, 40, 0)

        blockFmt = QTextBlockFormat()
        blockFmt.setLineHeight(150, QTextBlockFormat.ProportionalHeight)

        theCursor = self.text071x.textCursor()
        theCursor.clearSelection()
        theCursor.select(QTextCursor.Document)
        theCursor.mergeBlockFormat(blockFmt)
        theCursor = self.text32030x.textCursor()
        theCursor.clearSelection()
        theCursor.select(QTextCursor.Document)
        theCursor.mergeBlockFormat(blockFmt)

    def chip(self, str):
        try:
            if str == 'VTM071X':
                self.text071x.setVisible(1)
                self.text32030x.setVisible(0)
            else:
                self.text071x.setVisible(0)
                self.text32030x.setVisible(1)
        except Exception as e:
            traceback.print_exc()
            error(e)
    def resizewindow(self, str):
        size = eval(str)
        # print(size)
        self.text071x.setGeometry(20, 10, 746 + size[0], 492 + size[1])
        self.text32030x.setGeometry(20, 10, 746 + size[0], 492 + size[1])
        self.tableView.setGeometry(20, 10, 746 + size[0], 492 + size[1])
from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMessageBox, QLineEdit, QWidget, QCheckBox, QPushButton, QHBoxLayout
from enum import Enum
from ConfigVar import ConfigVar

mesboxtype = [
    QMessageBox.NoIcon,
    QMessageBox.Information,
    QMessageBox.Warning,
    QMessageBox.Critical,
    QMessageBox.Question]


class MyMessage(object):
    none = 0
    info = 1
    waring = 2
    error = 3
    question = 4
    message = {
        'patchTrue': {'en': 'Patch success', 'zh_cn': '修改成功', 'cn': '修改成功'},
        'patchFlase': {'en': 'Patch failed, please check the configuration file ', 'zh_cn': '修改失败，请检查配置文件',
                       'cn': '修改失敗，請檢查配置文件'},
        'path': {'en': 'Please check path', 'zh_cn': '请检查路径', 'cn': '請檢查路徑'},
        'demo': {'en': 'Please select a module', 'zh_cn': '请选择模块', 'cn': '請選擇模塊'},
        'chip': {'en': 'Please select a chip', 'zh_cn': '请选择芯片', 'cn': '請選擇芯片'},
        'document': {'en': 'Please select a document', 'zh_cn': '请选择文档', 'cn': '請選擇文檔'},
        'pname': {'en': 'The project name is invalid or already exists', 'zh_cn': '工程名无效或已存在', 'cn': '工程名無效或已存在'},
        'ppath': {'en': 'The project path is invalid', 'zh_cn': '工程路径无效', 'cn': '工程路徑無效'},
        'add': {'en': 'Project added successfully', 'zh_cn': '工程添加成功', 'cn': '工程添加成功'},
        'options': {'en': 'Please check options', 'zh_cn': '请检查设置', 'cn': '請檢查設置'},
        'uvprojx': {'en': 'Please secet a *.uvprojx', 'zh_cn': '请选择 .uvprojx文件', 'cn': '請選擇 .uvprojx文件'},
        'set': {'en': 'Path set successfully', 'zh_cn': '路径设置成功', 'cn': '路徑設置成功'},
        'VTM32030X': {'en': 'VTM030X not yet developed', 'zh_cn': 'VTM030X 尚未开发', 'cn': 'VTM030X 尚未開發'},
        'open': {'en': 'Project is invalid or deleted', 'zh_cn': '工程无效或已删除', 'cn': '工程無效或已刪除'},
        'PermissionError': {'en': 'Another program is using this file, please close and try again',
                            'zh_cn': '另一个程序正在使用此文件，请关闭后重试', 'cn': '另一個程序正在使用此文件，請關閉后重試'}
    }
    title = ['none', 'info', 'waring', 'error', 'question']

    def btn_one(self, icontype, showmes, icon='./data/logo.ico'):
        '''
        单按钮对话框 \n
        icontype
        none = 0
        info = 1
        warning = 2
        err = 3
        question = 4
        showmes 显示信息
        '''
        ConfigVar.readconf(self)
        titelmes = self.title[icontype]
        re = QMessageBox(
            mesboxtype[icontype], titelmes, self.message[showmes][ConfigVar.language])
        re.setWindowIcon(QIcon(icon))
        if ConfigVar.language == 'zh_cn':
            ye = re.addButton('确定', QMessageBox.YesRole)
        elif ConfigVar.language == 'cn':
            ye = re.addButton('確定', QMessageBox.YesRole)
        else:
            ye = re.addButton('OK', QMessageBox.YesRole)
        re.exec_()

    def btn_two(self, icontype, showmes, titelmes='提示框', icon='./data/logo.ico'):
        '''
        双按钮对话框 \n
        icontype
        none = 0
        info = 1
        warning = 2
        err = 3
        question = 4
        showmes 显示信息
        '''
        re = QMessageBox(
            mesboxtype[icontype], titelmes, showmes)
        re.setWindowIcon(QIcon(icon))
        btn_ok = re.addButton('确定', QMessageBox.YesRole)
        btn_no = re.addButton('取消', QMessageBox.NoRole)
        re.exec_()
        return re.clickedButton() == btn_ok

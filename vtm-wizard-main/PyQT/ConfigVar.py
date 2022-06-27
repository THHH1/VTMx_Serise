import configparser
import os
import shutil
import subprocess
import sys
import time
import traceback

from PyQt5.QtGui import QIcon
from PyQt5.QtWidgets import QMessageBox

from MyLog import info, error, GetPath
# from MyLog import ConfigVar.config_path_hash
from PyQt5.QtCore import QThread


class ProjectMess:
    def __init__(self):
        self.id = ''
        self.name = ''
        self.path = ''
        self.cmd = ''
        self.ctime = ''
        self.chip = ''
        self.type = ''
        self.demo = []

    def set(self, project):
        self.id = project.id
        self.name = project.name
        self.path = project.path
        self.cmd = project.cmd
        self.ctime = project.ctime
        self.chip = project.chip
        self.type = project.type
        self.demo = project.demo

    def show(self):
        info("id =(%s) name =(%s) path=(%s) ctime=(%s) cmd=(%s) chip=(%s) type=(%s) demo=(...)",
             self.id, self.name, self.path, self.ctime, self.cmd, self.chip, self.type)

    def write(self, path):
        try:
            config = configparser.ConfigParser()
            if os.path.exists(path):
                config.read(path)
                info("打开project.ini")
            else:
                f = open(path, "w")
                str = "[name]\n[path]\n[ctime]\n[cmd]\n[chip]\n[type]\n[demo]"
                f.write(str)
                f.close()
                info("创建project.ini")
                config.read(path)
            config.set('name', self.id, self.name)
            config.set('path', self.id, self.path)
            # print("write ----- path " + self.path)
            config.set('ctime', self.id, self.ctime)
            config.set('cmd', self.id, self.cmd)
            config.set('chip', self.id, self.chip)
            config.set('type', self.id, self.type)
            config.set('demo', self.id, ' '.join(self.demo))
            with open(path, 'w') as cf:
                config.write(cf)
        except Exception as e:
            traceback.print_exc()
            error(e)

    def read(self, id, config):
        self.id = id
        self.name = config.get('name', self.id)
        self.path = config.get('path', self.id)
        self.ctime = config.get('ctime', self.id)
        self.cmd = config.get('cmd', self.id)
        self.chip = config.get('chip', self.id)
        self.type = config.get('type', self.id)
        str = config.get('demo', self.id)
        self.demo = str.split(' ')
        self.cmd = ConfigVar.keilUV4_path + ' ' + self.cmd.split(' ')[1]

    def delete(self, path):
        str = self.path.replace('/', '\\')
        if ConfigVar.language == 'zh_cn':
            re = QMessageBox(1, "提示", "选择“移除”可将工程从列表中移除。\n选择“删除”可永久删除工程。")
            re.setWindowIcon(QIcon(":/req/Create a new project/Yun.png"))
            btn_remove = re.addButton('移除', QMessageBox.YesRole)
            btn_delete = re.addButton('删除', QMessageBox.NoRole)
            btn_no = re.addButton('取消', QMessageBox.NoRole)
            re.exec_()
        elif ConfigVar.language == 'cn':
            re = QMessageBox(1, "提示", "選擇「移除」可將工程從列表中移除。\n選擇「刪除」可永久刪除工程。")
            re.setWindowIcon(QIcon(":/req/Create a new project/Yun.png"))
            btn_remove = re.addButton('移除', QMessageBox.YesRole)
            btn_delete = re.addButton('刪除', QMessageBox.NoRole)
            btn_no = re.addButton('取消', QMessageBox.NoRole)
            re.exec_()
        else:
            re = QMessageBox(1, "prompt",
                             'Choose “Remove” to remove the project from the list.\n Choose “Delete” to permanently delete the project.')
            re.setWindowIcon(QIcon(":/req/Create a new project/Yun.png"))
            btn_remove = re.addButton('remove', QMessageBox.YesRole)
            btn_delete = re.addButton('delete', QMessageBox.NoRole)
            btn_no = re.addButton('cancel', QMessageBox.NoRole)
            re.exec_()
        if re.clickedButton() == btn_no:
            return
        if re.clickedButton() == btn_delete:
            if os.path.exists(str):
                # TODO how to delete
                # str = os.path.abspath(os.path.join(str, '..\..'))
                print("==================delete dirtree")
                print("path       " + path)
                print("self.path  " + self.path)
                print("str        " + str)
                print("==================\n")
                if os.path.isdir(str):
                    shutil.rmtree(str)
                info("success removed " + str)
            else:
                info("文件删除失败，路径不存在!  %s", str)

        config = configparser.ConfigParser()
        config.read(path)
        config.remove_option('name', self.id)
        config.remove_option('path', self.id)
        config.remove_option('ctime', self.id)
        config.remove_option('cmd', self.id)
        config.remove_option('chip', self.id)
        config.remove_option('type', self.id)
        config.remove_option('demo', self.id)
        with open(path, 'w') as cf:
            config.write(cf)
        info("配置文件移除项目成功!    %s", str)

    def clear(self):
        self.id = 0
        self.name = ''
        self.path = ''
        self.cmd = ''
        self.ctime = ''
        self.chip = ''
        self.type = ''
        self.demo = []


class ConfigVar:
    config_path_hash = GetPath('config.ini')
    project_path_hash = GetPath('project.ini')
    language = 'en'
    projectchip = ''
    mainWindow = None
    python_path = 'python.exe'
    keilUV4_path = ''
    path_flag = 'false'
    projectname = ''
    projectpath = ''
    project = ProjectMess()
    mainwindowsize = ''
    ID = 1
    uvprojxmap = {'CDC_HID_Composite': 'usbd_composite_cdc_hid.uvprojx',
                  'Custom_HID': 'usbd_custom_hid.uvprojx',
                  'HID': 'usbd_hid.uvprojx',
                  'MSC': 'usbd_msc.uvprojx',
                  'Virtual_COM_Port': 'usbd_vcp.uvprojx'}
    demo_introduce = {
        'ACMP_DAC': '*Use ACMP output results',
        'ADC_ADC_Watchdog': '*Use ADC output adc conversion value',
        'ADC_Chip_Temperature': '*Use ADC output adc conversion value',
        'ADC_Pin_Interrupt': '*Use ADC output adc conversion value',
        'ADC_Pin_Loop': '*Use ADC output adc conversion value',
        'ADC_Trigger': '*Use ADC output adc conversion value',
        'DAC_DAC0_DAC1': '*Use DAC output triangular wave',
        'DeepSleep_DeepSleep': '*Use sleep or power down mode',
        'DeepSleep_PowerDown': '*Use sleep or power down mode',
        'FLASH_IAP': '*Read or write flash data',
        'GPIO_LED_and_Key': '*Configure GPIO',
        'I2C_EEPROM': '*Configure I2C and use I2C read or write 24c08 chip',
        'IWDG_Reset': '*Use IWDG',
        'MCPWM_Complementary_waveform': '*Use MCPWM',
        'RTC_Time': '*Use RTC interrupt',
        'SPI_SPI_FLASH': '*Configure SPI and use SPI read or write flash chip',
        'TIMER_Breathing_Light': '*Configure TIMER and use Breathing Light or PWM output or input  Capture',
        'TIMER_PWM_and_Capture': '*Configure TIMER and use Breathing Light or PWM output or input  Capture',
        'TIMER_Timer_and_PWM': '*Configure TIMER and use Breathing Light or PWM output or input  Capture',
        'USART_RX_and_TX': '*Configure USART or output printing',
        'WWDG_Reset': '*Use WWDG',

        'CDC_HID_Composite': '*Use usb configure Custom HID\n*Use usb create Virtual_COM_Port\nps--Drive to be installed MIC_HID_CDC_Driver.inf',
        'Custom_HID': '*Use usb configure Custom HID',
        'HID': '*Use usb configure HID',
        'MSC': '*Use usb create USB flash drive',
        'Virtual_COM_Port': '*Use usb create Virtual_COM_Port\nps--Drive to be installed MIC_HID_CDC_Driver.inf'
    }

    chip_introduce = {
        'VTM071X': 'VTM071X 运行频率可以达到 84MHZ，工作电压 2.0V ~ 5.5V,X 内嵌 128K 字节的 Flash 存储器，其中用户可用空间为 120KB，以及 16K 字节的 SRAM 存储器,包含许多系统级外设功能，如高速通用 I/O 端口，4 通道DMA,Cordic 运算单元，USART，SPI，I2C，PWM，Motor-PWM，ADC，DAC，模拟比较器，看门狗定时器，RTC，欠压检测器等',
        'VTM32030X': 'VTM32030X 运行频率可以达到 84MHZ，工作电压 2.0V ~ 5.5V,X 内嵌 128K 字节的 Flash 存储器，其中用户可用空间为 120KB，以及 16K 字节的 SRAM 存储器,包含许多系统级外设功能，如高速通用 I/O 端口，4 通道DMA,Cordic 运算单元，USART，SPI，I2C，PWM，Motor-PWM，ADC，DAC，模拟比较器，看门狗定时器，RTC，欠压检测器等'
    }

    def readconf(self):
        # 读取配置文件
        try:

            config = configparser.ConfigParser()
            if os.path.exists(ConfigVar.config_path_hash):
                config.read(ConfigVar.config_path_hash)
                ConfigVar.python_path = config.get('installation', 'python_path')
                ConfigVar.keilUV4_path = config.get('installation', 'keilUV4_path')
                ConfigVar.path_flag = config.get('installation', 'path_flag')
                ConfigVar.project.name = config.get('installation', 'projectname')
                ConfigVar.projectname = ConfigVar.project.name
                ConfigVar.project.path = config.get('installation', 'projectpath')
                ConfigVar.projectpath = ConfigVar.project.path
                ConfigVar.language = config.get('installation', 'language')
                ConfigVar.ID = int(config.get('installation', 'ID'))
            else:
                config.add_section('installation')
                config.set('installation', 'python_path', 'python.exe')
                config.set('installation', 'keilUV4_path', '')
                config.set('installation', 'path_flag', 'flase')
                config.set('installation', 'projectname', 'Test1')
                config.set('installation', 'projectpath', '')
                config.set('installation', 'language', 'en')
                config.set('installation', 'ID', '0')
                with open(ConfigVar.config_path_hash, 'w') as f:
                    config.write(f)

        except Exception as e:
            traceback.print_exc()
            error(e)


class WorkThread(QThread):
    def __int__(self):
        # 初始化函数
        super(WorkThread, self).__init__()

    def run(self, str):
        try:
            str = str.replace('/', '\\')

            ConfigVar.project.cmd = str
            ConfigVar.project.ctime = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
            ConfigVar.project.show()
            ConfigVar.project.write(ConfigVar.project_path_hash)
            # print("run************run\n" + ConfigVar.project_path_hash)
            info("配置文件保存成功!")

            if sys.platform == "win32":
                import ctypes
                ctypes.windll.kernel32.SetDllDirectoryA(None)
            subprocess.Popen([ConfigVar.keilUV4_path, str.split('.exe ')[1]], start_new_session=True)
            info("--项目线程开始-->(%s) (%s)", ConfigVar.keilUV4_path, str.split('.exe ')[1])
        except Exception as e:
            traceback.print_exc()
            error(e)


class CmdThread(QThread):
    def __int__(self):
        # 初始化函数
        super(CmdThread, self).__init__()

    def run(self, str):
        try:
            str = str.replace("/", "\\")
            info("------------------cmd线程开始--(%s)", str)

            os.system('chcp 65001')  # 文件名包含中文
            os.popen(str)
        except Exception as e:
            traceback.print_exc()
            error(e)

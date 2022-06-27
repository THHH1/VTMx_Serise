import configparser
import traceback
import webbrowser
from MyLog import info, error
from PyQt5.QtCore import QTranslator
from PyQt5.QtWidgets import QMainWindow, QApplication
from PyQt5 import QtCore
from ConfigVar import ConfigVar
from UI import about


# new project子窗口
class AboutWindow(QMainWindow, about.Ui_About):
    def __init__(self):
        super(AboutWindow, self).__init__()
        self.setupUi(self)
        self.trans = QTranslator()
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMinimizeButtonHint)
        self.setWindowFlags(QtCore.Qt.WindowCloseButtonHint | QtCore.Qt.WindowMaximizeButtonHint)
    def openweb(self):
        url ='http://www.yunlink-semi.com/'
        webbrowser.open(url, new=0, autoraise=True)

    def show(self):
        if ConfigVar.language == 'zh_cn':
            self._trigger_zh_cn()
            self.aboutus.setText('关于我们')
            self.text.setText('    合肥云联半导体有限公司成立于2020年6月，是一家专注于研发音视频的传输，发送，接收，编解码以及接口等处理芯片和高性能低功耗无线物联网系统级芯片的设计公司。公司总部位于合肥市高新区创新产业园，在北京，深圳和上海设有办事处。\n\
    公司主营业务为集成电路IC设计研发和销售，并可以实现定制化芯片设计、单芯片解决方案以及SOC芯片解决方案，同时提供相关技术咨询和技术服务。目前公司主要产品包括VT8系列低功耗4K超高清端口处理芯片，VT2202S低功耗HDMI2.0中继芯片，VT5101M/VT5101H低功耗4K超高清转换芯片（HDMI2.0,MIPI系列）以及VTC05系列低功耗蓝牙5.1/5.0SOC芯片，应用的行业有专业音视频，广电系统，车载音视频，医疗显示类产品，以及蓝牙室内定位，蓝牙低功耗组网，蓝牙智慧场景等物联网领域。\
云联半导体拥有设计能力和设计经验丰富的团队，核心成员具有多年ASIC/SOC芯片开发经验，熟悉模拟、数字和后端技术，精通设计、仿真以及流片、封装、测试全流程，在接口性IP、CPU、显示驱动、图形、音频处理，无线通讯技术等领域均有深厚的技术积累。\n\
    公司秉承“持续创新，精工细作，分享共赢”的理念，始终向客户提供高性能高品质的芯片，帮助客户快速推出新产品，并建立长期稳定的合作关系。')
            self.logogo.setStyleSheet("image: url(:/req/Create a new project/logo 中文 -3.jpg);")
        elif ConfigVar.language == 'cn':
            self._trigger_cn()
            self.logogo.setStyleSheet("image: url(:/req/Create a new project/logo 中文 -3.jpg);")
            self.text.setText('    合肥雲聯半導體有限公司成立於2020年6月，是一家專注於研發音視頻的傳輸，發送，接收，編解碼以及接口等處理芯片和高性能低功耗無線物聯網系統級芯片的設計公司。公司總部位於合肥市高新區創新產業園，在北京，深圳和上海設有辦事處。\n\
    公司主營業務為集成電路IC設計研發和銷售，並可以實現定制化芯片設計、單芯片解決方案以及SOC芯片解決方案，同時提供相關技術諮詢和技術服務。目前公司主要產品包括VT8系列低功耗4K超高清端口處理芯片，VT2202S低功耗HDMI2.0中繼芯片，VT5101M/VT5101H低功耗4K超高清轉換芯片（HDMI2.0,MIPI系列）以及VTC05系列低功耗藍牙5.1/5.0SOC芯片，應用的行業有專業音視頻，廣電系統，車載音視頻，醫療顯示類產品，以及藍牙室內定位，藍牙低功耗組網，藍牙智慧場景等物聯網領域。\
雲聯半導體擁有設計能力和設計經驗豐富的團隊，核心成員具有多年ASIC/SOC芯片開發經驗，熟悉模擬、數字和後端技術，精通設計、仿真以及流片、封裝、測試全流程，在接口性IP、CPU、顯示驅動、圖形、音頻處理，無線通訊技術等領域均有深厚的技術積累。\n\
    公司秉承“持續創新，精工細作，分享共贏”的理念，始終向客戶提供高性能高品質的芯片，幫助客戶快速推出新產品，並建立長期穩定的合作關係。')
        else:
            self._trigger_english()
            self.aboutus.setText('About Us')
            self.logogo.setStyleSheet("image: url(:/req/Create a new project/logo 英文-1.jpg);")
            self.text.setText('     Hefei Yunlian Semiconductor Co., Ltd. was established in June 2020. It is a design company focusing on the research and development of audio and video transmission, transmission, reception, codec and interface processing chips and high-performance low-power wireless IoT system-on-chip. The company is headquartered in Hefei High-tech Zone Innovation Industrial Park, with offices in Beijing, Shenzhen and Shanghai.\n\
     The company\'s main business is integrated circuit IC design, development and sales, and can realize customized chip design, single-chip solutions and SOC chip solutions, and provide related technical consultation and technical services. At present, the company\'s main products include VT8 series low-power 4K ultra-high-definition port processing chips, VT2202S low-power HDMI2.0 relay chips, VT5101M/VT5101H low-power 4K ultra-high-definition conversion chips (HDMI2.0, MIPI series) and VTC05 series Low-power Bluetooth 5.1/5.0SOC chips are used in professional audio and video, radio and television systems, automotive audio and video, medical display products, and Bluetooth indoor positioning, Bluetooth low-power networking, Bluetooth smart scenarios and other IoT fields.\
Yunlian Semiconductor has a team with design capabilities and design experience. The core members have many years of experience in ASIC/SOC chip development, are familiar with analog, digital and back-end technologies, and are proficient in design, simulation and the whole process of tape-out, packaging and testing. IP, CPU, display driver, graphics, audio processing, wireless communication technology and other fields have profound technical accumulation.\n\
     Adhering to the concept of "continuous innovation, meticulous work, sharing and win-win", the company always provides customers with high-performance and high-quality chips, helps customers quickly launch new products, and establishes long-term and stable cooperative relations.')
        super(AboutWindow, self).show()

    def _trigger_english(self):
        try:
            # print("[MainWindow] Change to English")
            self.trans.load("./translator/AboutWindow_en")
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
            #print("[MainWindow] Change to 简体中文")
            self.trans.load("./translator/AboutWindow_zh_cn")
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
            #print("[MainWindow] Change to 繁體中文")
            self.trans.load("./translator/AboutWindow_cn")
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
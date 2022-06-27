import os
import shutil
import sys
from ctypes import WinError
from xml.dom.minidom import parse
import argparse

mhelp = "-a V1.35" \
        "WWDG_Reset USART_RX_and_TX TIMER_Timer_and_PWM TIMER_PWM_and_Capture TIMER_Breathing_Light SPI_SPI_FLASH " \
        "ACMP_DAC ADC_ADC_Watchdog ADC_Chip_Temperature ADC_Pin_Interrupt ADC_Pin_Loop ADC_Trigger DAC_DAC0_DAC1 " \
        "MCPWM_Complementary_waveform RTC_Time DeepSleep_DeepSleep DeepSleep_PowerDown FLASH_IAP GPIO_LED_and_Key " \
        "I2C_EEPROM IWDG_Reset " \
        "-a USBV1.0" \
        "CDC_HID_Composite Custom_HID HID MSC Virtual_COM_Port"
parser = argparse.ArgumentParser()
parser.add_argument("-a", help="USBV1.0 V1.35")
parser.add_argument("-p", help="install path")
parser.add_argument("-m", action="append", help=mhelp)
parser.add_argument("-o", help="Project Name")
args = parser.parse_args()


def mkdir(path):
    folder = os.path.exists(path)
    if not folder:  # 判断是否存在文件夹如果不存在则创建为文件夹
        os.makedirs(path)  # makedirs 创建文件时如果路径不存在会创建这个路径


def compose(code, keycodes, valuecodes):
    f = open("./code/V1.35/" + code + ".c", "r", encoding='UTF-8')
    line = f.read()
    f.close()
    reqvalues = []
    for i in range(len(keycodes[0])):
        # print("keycodes------------"+keycodes[0][i].firstChild.data)
        try:
            DOMTree = parse(r'./xml/V1.35/codexml/' + keycodes[0][i].firstChild.data + '.xml')
            reqroot = DOMTree.documentElement
        except IOError as e:
            print("ERR----:Unable to copy file. %s" % e)
        except:
            print("ERR----:Unexpected error:", sys.exc_info())
            print("ERR----:" + keycodes[0][i].firstChild.data)
        # print("parse:" + keycodes[0][i].firstChild.data)
        for j in range(len(keycodes)):
            req = valuecodes[j][i].firstChild.data
            reqvalue = req.split('|')
            if j == 0:
                reqvalues.insert(i, reqvalue)
            else:
                for str in reqvalue:
                    if str not in reqvalues[i] and str != ' ':
                        reqvalues[i].append(str)
        headfile = "{{" + keycodes[0][i].firstChild.data + "}}"
        value = ''
        for j in range(len(reqvalues[i])):
            if reqvalues[i][j] != 'null':
                # print("     " + reqvalues[i][j])
                codes = reqroot.getElementsByTagName(reqvalues[i][j])
                if len(codes) == 0:
                    print("ERR----:" + reqvalues[i][j] + " is error !!!!!!!")
                value += codes[0].firstChild.data
        line = line.replace(headfile, value)  # 替换占位符
    return line


def writefile(path, demo, filename, line):
    mkdir(path + "/out/" + demo)
    if 'inc' in demo:
        filename = filename + ".h"
    else:
        filename = filename + ".c"
    f = open(path + "/out/" + demo + "/" + filename, "w", encoding='UTF-8')  # 写入新文件
    f.write(line)
    f.close()


def FLASH_IAP_special_changes(path):
    cf = open(path + "/out/V1.35/" + args.o + "/Projects/" + args.o + "/VTM071x_conf.h", "r")
    fcode = cf.read()
    cf.close()
    fcode = fcode[:1978] + "//" + fcode[1978:]
    cf = open(path + "/out/V1.35/" + args.o + "/Projects/" + args.o + "/VTM071x_conf.h", "w")
    cf.write(fcode)
    cf.close()
    # print("FLASH_IAP special changes --- nodefine USE_FULL_ASSERT")


def V135(argv, path):
    try:
        mkdir(path + "out/")
        folder = os.path.exists(path + "/out/V1.35/" + args.o)
        if not folder:
            shutil.copytree("code/V1.35/V1.35", path + "/out/V1.35/" + args.o)
            shutil.rmtree(path + "out/V1.35/" + args.o + "/Projects/VTM071x_StdPeriph_Templates")
    except WinError as e:
        print("ERR----:Unable to copy file. %s" % e)
    except:
        print("ERR----:Unexpected error:", sys.exc_info())
        exit(-1)
    argc = len(argv)
    keycodes = []
    valuecodes = []
    itkeycodes = []
    itvaluecodes = []
    for i in range(argc):
        # print('./xml/V1.35/' + argv[i] + '.xml')
        DOMTree = parse(r'./xml/V1.35/' + argv[i] + '.xml')
        root = DOMTree.documentElement
        keys = root.getElementsByTagName("key")
        itkeys = root.getElementsByTagName("itkey")
        values = root.getElementsByTagName("value")
        itvalues = root.getElementsByTagName("itvalue")
        keycodes.append(keys)
        valuecodes.append(values)
        itkeycodes.append(itkeys)
        itvaluecodes.append(itvalues)
    lineUSART = 'void USART_Configuration(void)\n\
{\n\
  USART_InitTypeDef USART_InitStructure;\n\
  GPIO_InitTypeDef GPIO_InitStructure;\n\
  RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);\n\
  RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);\n\
  RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);\n\
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;\n\
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;\n\
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;\n\
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\n\
  GPIO_Init(GPIO1, &GPIO_InitStructure);\n\
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;\n\
  GPIO_Init(GPIO1, &GPIO_InitStructure);\n\
  USART_DeInit(USART0);\n\
  USART_StructInit(&USART_InitStructure);\n\
  USART_Init(USART0, &USART_InitStructure);\n\
  USART_Cmd(USART0, ENABLE);\n\
}'
    lineUSART2 = 'void USART_Configuration(void)\n\
{\n\
    USART_InitTypeDef USART_InitStructure;\n\
    GPIO_InitTypeDef GPIO_InitStructure;\n\
    \n\
    /* Enable USART0 IRQ */\n\
    NVIC_EnableIRQ(USART0_IRQn);\n\
    \n\
    RCC_APBPeriphClockCmd(RCC_AHBCLKCTRL_USART0,ENABLE);\n\
    RCC_USARTCLKSel(RCC_USARTCLK_SOURCE_SYSPLL);\n\
    RCC_SETCLKDivider(RCC_CLOCKFREQ_USART0CLK, USART0_CLOCK_DIV);\n\
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;\n\
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_Level_2;\n\
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_1;\n\
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;\n\
    GPIO_Init(GPIO1, &GPIO_InitStructure);\n\
    \n\
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;\n\
    GPIO_Init(GPIO1, &GPIO_InitStructure);\n\
    \n\
    USART_DeInit(USART0);\n\
    USART_StructInit(&USART_InitStructure);\n\
    USART_Init(USART0, &USART_InitStructure);\n\
    \n\
    /* Enable USART0 RX and Receive timeout irq */\n\
    USART_ITConfig(USART0, USART_IT_RXIEN, ENABLE);\n\
    USART_RXTOCountConfig(USART0, 20);\n\
    USART_ITConfig(USART0, USART_IT_RXTOEN, ENABLE);\n\
    USART_Cmd(USART0, ENABLE);\n\
    }'
    line = compose("main_code", keycodes, valuecodes)
    if 'USART_RX_and_TX' in argv:
        line = line.replace(lineUSART, lineUSART2)
    writefile(path, "V1.35/" + args.o + "/Projects/" + args.o, "main", line)
    line = compose("VTM071x_it_code", itkeycodes, itvaluecodes)
    writefile(path, "V1.35/" + args.o + "/Projects/" + args.o, "VTM071x_it", line)

    try:
        shutil.copy("code/V1.35/system_VTM071x.c",
                    path + "/out/" + "V1.35/" + args.o + "/Projects/" + args.o + "/system_VTM071x.c")
        shutil.copy("code/V1.35/VTM071x_conf.h",
                    path + "/out/" + "V1.35/" + args.o + "/Projects/" + args.o + "/VTM071x_conf.h")
        shutil.copy("code/V1.35/VTM071x_it.h",
                    path + "/out/" + "V1.35/" + args.o + "/Projects/" + args.o + "/VTM071x_it.h")
        if "FLASH_IAP" in argv:
            FLASH_IAP_special_changes(path)
        cf = open("code\V1.35\V1.35\Projects\VTM071x_StdPeriph_Templates\MDK-ARM\Project.uvprojx", "r")
        fcode = cf.read()
        cf.close()

        str1 = "<TargetName>MT071x</TargetName>"
        str2 = "<TargetName>" + args.o + "</TargetName>"
        fcode = fcode.replace(str1, str2)
        str1 = "VTM071x_StdPeriph_Templates"
        str2 = args.o
        fcode = fcode.replace(str1, str2)
        mkdir(path + "/out/V1.35/" + args.o + "/Projects/" + args.o + "/MDK-ARM/")
        cf = open(path + "/out/V1.35/" + args.o + "/Projects/" + args.o + "/MDK-ARM/Project.uvprojx", mode='w')
        cf.write(fcode)
        cf.close()
    except IOError as e:
        print("Unable to copy file. %s" % e)
    except:
        print("Unexpected error:", sys.exc_info())


def getfiles(argv, mode):
    files = []
    for demo in argv:
        DOMTree = parse(r'./xml/USBV1.0/' + demo + '/filename.xml')
        root = DOMTree.documentElement
        file = root.getElementsByTagName(mode)
        # + root.getElementsByTagName("filename_h") + root.getElementsByTagName("filename_uvprojx")
        for filename in file:
            if filename.firstChild.data not in files:
                files.append(filename.firstChild.data)
    return files


def demo_compose(argv, files, mode, path):
    for filename in files:
        # print('+++++++++++++++++++++++' + filename + '文件keys values读取完毕' + '++++++++++++++++++++++++++++++++')
        keys = []
        values = []
        for demo in argv:
            code_xml_path = './xml/USBV1.0/' + demo + '/' + mode + '/' + filename + '.xml'
            folder = os.path.exists(code_xml_path)
            if folder:
                try:
                    DOMTree = parse(r'./xml/USBV1.0/' + demo + '/' + mode + '/' + filename + '.xml')
                except FileNotFoundError:
                    print('error:' + code_xml_path + "    not Found!!!")
                    exit(-1)
                root = DOMTree.documentElement
                for node in root.childNodes:
                    if node.nodeName != "#text" and node.nodeName not in keys:
                        keys.append(node.nodeName)

                for k in range(len(keys)):
                    req = root.getElementsByTagName(keys[k])[0].firstChild.data
                    reqvalue = req.split('|')
                    for str in reqvalue:
                        if values.__len__() <= k:
                            array = []
                            if str != ' ' and str != 'null':
                                array.append(str)
                            values.insert(k, array)
                        elif str != ' ' and str != 'null' and str not in values[k]:
                            values[k].append(str)
        # print(keys)
        # print(values)
        if filename != "demo_uvprojx":
            ccode = filename[0:len(filename) - 2]
        else:
            ccode = filename[0:len(filename) - 8]
        code = mode + "/" + ccode
        if mode == 'src':
            code = code + ".c"
        elif mode == 'inc':
            code = code + ".h"
        else:
            code = code + ".uvprojx"
        totalcode = mode + "/" + filename + ".xml"
        # print(filename)
        # print(code)
        # print(totalcode)

        f = open("./code/USBV1.0/Projects/" + code, "r", encoding='UTF-8')
        line = f.read()
        f.close()
        reqvalues = values
        try:
            DOMTree = parse(r'./xml/USBV1.0/Xml_code/' + totalcode)
            reqroot = DOMTree.documentElement
        except FileNotFoundError:
            # print("Unexpected error:", sys.exc_info())
            # print("error----./xml/USBV1.0/Xml_code/" + totalcode)
            print("just copy----./xml/USBV1.0/Xml_code/" + totalcode)
        except OSError:
            print("Unexpected error:", sys.exc_info())
        else:
            for i in range(len(keys)):
                # print("key------------"+keys[i])
                # print("parse:" + keys[i])
                headfile = "{{" + keys[i] + "}}"
                value = ''
                for j in range(len(reqvalues[i])):
                    if reqvalues[i][j] != 'null':
                        print("     " + reqvalues[i][j])
                        codes = reqroot.getElementsByTagName(reqvalues[i][j])
                        if len(codes) == 0:
                            print(reqvalues[i][j] + " is error !!!!!!!")
                        value += codes[0].firstChild.data
                line = line.replace(headfile, value)  # 替换占位符
        demofile = ""
        for str in argv:
            demofile += str
        if 'CDC_HID_Composite' in argv:
            writefile(path, "USBV1.0/" + args.o + "/Projects/" + args.o + "/" + demofile + '/' + mode, ccode, line)
        else:
            writefile(path, "USBV1.0/" + args.o + "/Projects/" + args.o + '/' + mode, ccode, line)
        # print('++++++++++++++++++++++++++++++++++++++++++' + code + '+++++++++++++++++++++++++++++++++++++++++++\n')


def project_cp(path, uvprojxmap, demo):
    print("代码生成完成 -> \n正在拷贝依赖 --->")
    namemap = {'CDC_HID_Composite': 'USBD_MSC_VTM071x',
               'Custom_HID': 'USBD_CUSTOM_HID_VTM071x',
               'HID': 'USBD_HID_VTM071x',
               'MSC': 'USBD_MSC_VTM071x',
               'Virtual_COM_Port': 'USBD_CDC_VTM071x'}

    try:
        if 'CDC_HID_Composite' == demo:
            mkdir(path + "/out/USBV1.0/" + args.o + "/Projects/" + args.o + "/" + demo + "/MDK-ARM")
            cf = open("./code/USBV1.0/Projects/MDK-ARM/" + uvprojxmap[demo], "r")
            fcode = cf.read()
            cf.close()
            str1 = "<TargetName>" + namemap[demo] + "</TargetName>"
            str2 = "<TargetName>" + args.o + r"</TargetName>"
            fcode = fcode.replace(str1, str2)
            str1 = "VTM071x_StdPeriph_Templates"
            str2 = args.o
            fcode = fcode.replace(str1, str2)
            # print(fcode)
            cf = open(
                path + "/out/USBV1.0/" + args.o + "/Projects/" + args.o + "/" + demo + "/MDK-ARM/" + uvprojxmap[demo],
                "w")
            cf.write(fcode)
            cf.close()
        else:
            mkdir(path + "/out/USBV1.0/" + args.o + "/Projects/" + args.o + "/MDK-ARM")
            cf = open("./code/USBV1.0/Projects/MDK-ARM/" + uvprojxmap[demo], "r")
            fcode = cf.read()
            cf.close()
            str1 = "<TargetName>" + namemap[demo] + "</TargetName>"
            str2 = "<TargetName>" + args.o + r"</TargetName>"
            fcode = fcode.replace(str1, str2)
            str1 = "VTM071x_StdPeriph_Templates"
            str2 = args.o
            fcode = fcode.replace(str1, str2)
            # print(fcode)
            cf = open(path + "/out/USBV1.0/" + args.o + "/Projects/" + args.o + "/MDK-ARM/" + uvprojxmap[demo], "w")
            cf.write(fcode)
            cf.close()
        # print(uvprojxmap[demo] + ' copy success')
        shutil.copy("code/USBV1.0/readme.txt", path + "/out/USBV1.0/" + args.o + "/readme.txt")
        # print('readme.txt copy success')
        folder = os.path.exists(path + "/out/USBV1.0/" + args.o + "/Driver")
        if not folder:
            shutil.copytree("code/USBV1.0/Driver", path + "/out/USBV1.0/" + args.o + "/Driver")
            print('Driver copy success')
        else:
            print('Driver has been exist')
        folder = os.path.exists(path + "/out/USBV1.0/" + args.o + "/Libraries")
        if not folder:
            shutil.copytree("code/USBV1.0/Libraries", path + "/out/USBV1.0/" + args.o + "/Libraries")
            print('Libraries copy success')
        else:
            print('Libraries has been exist')
        folder = os.path.exists(path + "/out/USBV1.0/" + args.o + "/Utilities")
        if not folder:
            shutil.copytree("code/USBV1.0/Utilities", path + "/out/USBV1.0/" + args.o + "/Utilities")
            print('Utilities copy success')
        else:
            print('Utilities has been exist')

    except IOError as e:
        print("Unable to copy file. %s" % e)
    except:
        print("Unexpected error:", sys.exc_info())
    else:
        print("依赖拷贝完成 --->")


def USBV1(argv, path):
    files = getfiles(argv, "filename_c")
    demo_compose(argv, files, 'src', path)
    files = getfiles(argv, "filename_h")
    demo_compose(argv, files, 'inc', path)
    uvprojxmap = {'CDC_HID_Composite': 'usbd_composite_cdc_hid.uvprojx',
                  'Custom_HID': 'usbd_custom_hid.uvprojx',
                  'HID': 'usbd_hid.uvprojx',
                  'MSC': 'usbd_msc.uvprojx',
                  'Virtual_COM_Port': 'usbd_vcp.uvprojx'}
    project_cp(path, uvprojxmap, argv[0])
    # if argv[0] == 'CDC_HID_Composite':
    #     os.rename(path + "/out/USBV1.0/Projects/Composite_Examples",path + "/out/USBV1.0/Projects/"+args.o)
    # else:
    #     os.rename(path + "/out/USBV1.0/Projects/"+argv[0], path + "/out/USBV1.0/Projects/" + args.o)


def parse_argv(mhelp, argv):
    mlist = mhelp.split(" ")
    for demo in args.m:
        if demo in mlist:
            argv.append(demo)
    argc = len(argv)
    if argc > 0:
        print(argv)
        print("argv-------------\n")
    else:
        print("Please choose more than one right demo!")
        exit()


if args.p is None:
    path = "../../"
else:
    path = args.p + '/'
if args.a.upper() == "V1.35":
    argv = []
    mhelp = "WWDG_Reset USART_RX_and_TX TIMER_Timer_and_PWM TIMER_PWM_and_Capture TIMER_Breathing_Light SPI_SPI_FLASH " \
            "ACMP_DAC ADC_ADC_Watchdog ADC_Chip_Temperature ADC_Pin_Interrupt ADC_Pin_Loop ADC_Trigger DAC_DAC0_DAC1 " \
            "MCPWM_Complementary_waveform RTC_Time DeepSleep_DeepSleep DeepSleep_PowerDown FLASH_IAP GPIO_LED_and_Key " \
            "I2C_EEPROM IWDG_Reset "
    parse_argv(mhelp, argv)
    V135(argv, path)
elif args.a.upper() == "USBV1.0":
    argv = []
    mhelp = "CDC_HID_Composite Custom_HID HID MSC Virtual_COM_Port"
    parse_argv(mhelp, argv)
    USBV1(argv, path)
else:
    print("Please choose the correct chip！")

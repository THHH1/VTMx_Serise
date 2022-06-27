# -*- mode: python ; coding: utf-8 -*-


block_cipher = None


a = Analysis(['main.py','AboutWindow.py','ChipWindow.py','ConfigVar.py',
'DemoWindow.py','DocumentsWindow.py','ImportChipWindow.py','ImportDemoWindow.py','ImportPathWindow.py',
'KeilWindow.py','MyLog.py','MessageWindow.py','NewWindow.py','ProChipWindow.py','ProFrame.py','ProWindow.py',
'req_rc.py','.\\UI\\about.py','.\\UI\\chip.py','.\\UI\\create.py','.\\UI\\created.py','.\\UI\\createVTM.py','.\\UI\\demo.py','.\\UI\\doc.py','.\\UI\\importchip.py',
'.\\UI\\importdemo.py','.\\UI\\importpath.py','.\\UI\\keil.py','.\\UI\\project.py','.\\UI\\Yun.py','.\\compose.py'],
             pathex=['E:\\code\\yunLink\\plugins', 'E:\\code\\yunLink\\PyQt5',
             'E:\\code\\yunLink\\vtm-wizard\\PyQT','E:\\code\\yunLink\\vtm-wizard','E:\\code\\yunLink\\PyQt5\\Qt5\\bin'],
             binaries=[],
             datas=[],
             hiddenimports=[],
             hookspath=[],
             hooksconfig={},
             runtime_hooks=[],
             excludes=['PyQt5'],
             win_no_prefer_redirects=False,
             win_private_assemblies=False,
             cipher=block_cipher,
             noarchive=False)
pyz = PYZ(a.pure, a.zipped_data,
             cipher=block_cipher)

exe = EXE(pyz,
          a.scripts, 
          [],
          exclude_binaries=True,
          name='YunLinKSDK',
          debug=False,
          bootloader_ignore_signals=False,
          strip=False,
          upx=True,
          console=False,
          disable_windowed_traceback=False,
          target_arch=None,
          codesign_identity=None,
          entitlements_file=None , icon='favicon.ico')
coll = COLLECT(exe,
               a.binaries,
               a.zipfiles,
               a.datas, 
               strip=False,
               upx=True,
               upx_exclude=[],
               name='YunLinKSDK')

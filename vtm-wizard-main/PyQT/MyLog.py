import logging
import logging.handlers
import os
import hashlib
from logging import *
# from datetime import *

global logger
global debug
global info
global warning
global error
global critical

def mkdir(path):
    folder = os.path.exists(path)
    if not folder:
        os.makedirs(path)

def GetPath(name):
    LogPath = os.path.expanduser('~') + '\AppData\Local\YunLink\\'
    mkdir(LogPath)
    name_hash = GetHash(name)
    # print(LogPath+name_hash)
    return LogPath+name_hash

def GetHash(name):
    str = os.path.abspath(os.curdir)
    hashstr = hashlib.sha256()
    hashstr.update(str.encode('utf-8'))
    # print('SHA-256:' + hashstr.hexdigest())
    return hashstr.hexdigest()[:16]+name

def LogInit(path):


    logger = logging.getLogger()
    logger.setLevel(logging.DEBUG)
    rht = logging.handlers.RotatingFileHandler(path, 'a',10485760,2,"GBK")
    fmt = logging.Formatter("%(asctime)s %(pathname)s %(filename)s %(funcName)s %(lineno)s \
         %(levelname)s - %(message)s", "%Y-%m-%d %H:%M:%S")
    rht.setFormatter(fmt)
    logger.addHandler(rht)

    debug = logger.debug
    info = logger.info
    warning = logger.warning
    error = logger.error
    critical = logger.critical


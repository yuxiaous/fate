#encoding:utf-8
#===============================================================================================
#作用：检查支付配置是否正确。
#使用方式：将脚本放在与工程AndroidManifest.xml同级目录下，在命令行调用'python env_check.py'即可。
#    如果支付配置有误，脚本会给出错误详情；如果配置成功，则提示'检查配置成功，通过检查！'
#作者：九游支付
#===============================================================================================

import os
import sys
import optparse
from string import Template

#-------全局标志位区域, 游戏开发可以修改以下变量--------------------------------------------
#--是否使用三大运营商SDK
USE_THREE_OPERATOR = True
#--是否使用支付宝支付SDK
USE_ALIPAY = True
#-------------------------------------------------------------------------------------------

#Integration工程目录
INTEGRATION_PROJECT_PATH = None
#当前目录
CWD = os.getcwd()
#AndroidManifest.xml文件名
AM_FILE_NAME = 'AndroidManifest.xml'
#AndroidManifest.xml文件结构
#<manifest>
#--<application>
#----<activity>
#----</activity>
#----#or-service/receiver/...
#--</application>
#--<uses-permission>
#--</uses-permission>
#</manifest>

#AndroidManifest.xml中的属性关键字
XMLNS_PREFIX = '{http://schemas.android.com/apk/res/android}'
NAME = XMLNS_PREFIX + 'name'


#AndroidManifest.xml匹配模板
AM_TEMPLATE_PREFIX = \
'''
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="$PACKAGE_NAME">

    <application>

        <activity
            android:name="cn.uc.paysdk.SDKActivity"
            android:configChanges="keyboardHidden|orientation|screenSize"
            android:launchMode="singleTask"
            android:theme="@android:style/Theme.Translucent.NoTitleBar"
            android:windowSoftInputMode="adjustPan|stateAlwaysHidden|adjustResize" >
        </activity>

        <service android:name="cn.uc.paysdk.service.SDKService" >
        </service>
'''

ALIPAY = \
'''
        <activity
            android:name="com.alipay.sdk.app.H5PayActivity"
            android:configChanges="orientation|keyboardHidden|navigation"
            android:exported="false"
            android:screenOrientation="behind" >
        </activity>
        <activity
            android:name="com.alipay.sdk.auth.AuthActivity"
            android:configChanges="orientation|keyboardHidden|navigation"
            android:exported="false"
            android:screenOrientation="behind" >
        </activity>
'''

THREE_OPERATOR_SDK = \
'''
        <!-- 中国电信SDK支付相關添加开始 -->
		<!-- 中国电信渠道号 :需要根据实际修改-->
        <meta-data android:name="EGAME_CHANNEL" android:value="10000000" />
        <meta-data android:name="EGAME_UNINS" android:value="false" />
     
        <activity
            android:name="cn.egame.terminal.paysdk.EgamePayActivity"
            android:configChanges="orientation|keyboard|keyboardHidden"
            android:screenOrientation="unspecified"
            android:theme="@android:style/Theme.Translucent.NoTitleBar.Fullscreen" >
        </activity>

        <activity
            android:name="cn.play.dserv.EmpActivity"
            android:configChanges="keyboard|keyboardHidden|orientation"
            android:exported="true" />

        <service
            android:name="cn.play.dserv.DService"
            android:enabled="true"
            android:exported="false"
            android:label="dservice"
            android:process=":dservice_v1" >
        </service>

        <receiver
            android:name="cn.play.dserv.DsReceiver"
            android:process=":dservice_v1" >
            <intent-filter>
                <action android:name="cn.play.dservice" />
            </intent-filter>
        </receiver>
		<!-- 中国电信SDK支付相關添加结束 -->
        
		<!-- 中国联通SDK支付相關添加开始 -->  
	<service
            android:name="com.unicom.wostore.unipay.paysecurity.SecurityServiceFramework">   
            <intent-filter>
            <!-- 请务必将action name 按照应用包名+".unicom.wostore.unipay.securityserviceframework"进行组装-->
            	<action android:name="com.ucweb.h5runtime.unicom.wostore.unipay.securityserviceframework" />
            </intent-filter>
        </service>
        
        <meta-data android:name="wostore_billing_otherpay" android:value="false"/>
        <meta-data android:name="wostore_billing_chinaunicom" android:value="true"/>
        <meta-data android:name="wostore_billing_chinamobile"  android:value="false" />
        <meta-data android:name="wostore_billing_chinatele"  android:value="false" />
        <!-- 中国联通SDK支付相關添加结束 -->
		
'''

AM_TEMPLATE_SUFFIX = \
'''
    </application>

    <uses-permission android:name="android.permission.MOUNT_UNMOUNT_FILESYSTEMS" />
    <uses-permission android:name="android.permission.WRITE_INTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.WRITE_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.INTERNET" />
    <uses-permission android:name="android.permission.ACCESS_NETWORK_STATE" />
    <uses-permission android:name="android.permission.READ_PHONE_STATE" />
    <uses-permission android:name="android.permission.ACCESS_WIFI_STATE" />
    <uses-permission android:name="android.permission.SEND_SMS" />
    <uses-permission android:name="android.permission.GET_TASKS" />
    <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
    <uses-permission android:name="android.permission.VIBRATE" />
    <uses-permission android:name="android.permission.AUTHENTICATE_ACCOUNTS" />
    <uses-permission android:name="android.permission.GET_ACCOUNTS" />
    <uses-permission android:name="android.permission.USE_CREDENTIALS" />
	    
    <!-- 运营商SDK权限添加开始 -->
    <!-- 电信 -->
    <uses-permission android:name="android.permission.ACCESS_COARSE_LOCATION" />
    <uses-permission android:name="android.permission.CHANGE_NETWORK_STATE" />
    <uses-permission android:name="android.permission.READ_EXTERNAL_STORAGE" />
    <uses-permission android:name="android.permission.GET_PACKAGE_SIZE" />
    <uses-permission android:name="android.permission.WRITE_SETTINGS" />
    <uses-permission android:name="android.permission.CALL_PHONE" />
    <!-- 移动 -->
    <uses-permission android:name="android.permission.READ_SMS" />
    <uses-permission android:name="android.permission.READ_CONTACTS" />
    <uses-permission android:name="android.permission.SYSTEM_ALERT_WINDOW" />
    <!-- 联通 -->
    <uses-permission android:name="android.permission.DISABLE_KEYGUARD"/>
    <!-- 运营商SDK权限添加結束 -->

</manifest>    
'''

SDK_CHECK_FILES = [
  'assets/UCPaySDK/pay.png',#权限验证文件
  'assets/UCGameInfo.ini',#GameInfo文件
]

THREE_OPERATOR_FILES = [
  'assets/ConsumeCodeInfo.xml',
  'assets/Charge.xml',
  'assets/d_data_store.dat.x86',
  'assets/libmegbpp_02.02.13_00.so.x86',
  'assets/AndGame.Sdk.Lib_20130_4E4DB8F73D48429B0A74BED2D59DC7A8.dat',
  'assets/libmegbpp_02.02.13_00.so',
  'assets/Config.xml',
  'assets/feeInfo.dat',#中国电信计费文件
  'assets/c_data_store.dat',
  'assets/CMGC/ConfigExtend.xml',
  'assets/d_data_store.dat',
]

#EGAME文件，后续有可能校验，目前不用校验
ASSET_EGAME_FILES = [
  'assets/egame/EGAME_107.dat',
  'assets/egame/EGAME_107.jar'
]

INTEGRATION_LIBS_FILES = [
  'libs/x86/libcmcc_haze.so',
  'libs/x86/libidentifyapp.so',
  'libs/x86/libdserv.so',
  'libs/x86/libmegjb.so',
  'libs/x86/libumc-auth.so',
  'libs/x86/libegamepay_dr2.so',
  'libs/x86/libcmcc_rusteze.so',
  'libs/x86/libcasdkjni.so',
  'libs/mmbilling.3.1.7.jar',
  'libs/UCGameSaSdk-1.3.0.jar',
  'libs/Multimode_UniPay_base.jar',
  'libs/armeabi/libcmcc_haze.so',
  'libs/armeabi/libidentifyapp.so',
  'libs/armeabi/libdserv.so',
  'libs/armeabi/libmegjb.so',
  'libs/armeabi/libumc-auth.so',
  'libs/armeabi/libegamepay_dr2.so',
  'libs/armeabi/libcmcc_rusteze.so',
  'libs/armeabi/libcasdkjni.so',
  'libs/egame.ck.jar',
  'libs/egame.log_20150625_out_release.jar',
  'libs/cn.egame.terminal.paysdk.jar',
  'libs/alipay-20150331.jar',
]


def Log(content):
  '输出日志'

  print (content)

def LogTitle(title):
  '输出标题'

  Log('=========================================================================================')
  Log('||'+ title)
  Log('---------------------------------------------')


def ExistFile(file):
  '判断单个文件是否存在'

  Log('检查文件：' + file)
  return os.path.exists(file)

def ExistFileList(files):
  '判断文件列表中所有文件都存在'

  for file in files:
    if not ExistFile(file):
      Log('文件' + file + '不存在!')
      return False
  return True

def CheckFilesConfig():
  '检查工程文件配置是否正确'

  global USE_THREE_OPERATOR
  global INTEGRATION_PROJECT_PATH

  #判断主工程assets目录文件配置
  # 1) SDK配置文件检查
  if not ExistFileList(SDK_CHECK_FILES):
    return False
  # 2) 三大运营商配置检查（如果使用三大运营商)
  if USE_THREE_OPERATOR:
    if not ExistFileList(THREE_OPERATOR_FILES):
      return False
  # 3) Integration工程libs目录检查
    check_integration = True 
    errorMsg = None
    if INTEGRATION_PROJECT_PATH is None:
      INTEGRATION_PROJECT_PATH = '../ugpsdk-integration/';
      errorMsg = '未指定integration目录，尝试使用[' + INTEGRATION_PROJECT_PATH + ']失败，该文件不存在!'
    else:
      errorMsg = '指定的integration目录[' + INTEGRATION_PROJECT_PATH + ']不存在!'
      
    if not ExistFile(INTEGRATION_PROJECT_PATH):
      check_integration = False
      Log(errorMsg)

    if check_integration:
      files = []
      for file in INTEGRATION_LIBS_FILES:
        file = os.path.join(INTEGRATION_PROJECT_PATH, file)
        files.append(file)
      if not ExistFileList(files):
        return False
  return True

def MatchAttributes(left, right):
  '判断两个节点的所有属性是否都匹配'

  for key in right.keys():
    if key not in left.keys():
      return False

    if left.get(key) != right.get(key):
      return False  
  return True

def MatchElement(left, right):
  '所有子节点的属性也都匹配,且只匹配子节点这一级，而非递归多级匹配'

  # 1) 属性检查
  if not MatchAttributes(left, right):
    return False
  # ) 子节点检查
  for left_child in list(left):
    matched = False
    for right_child in list(right):
      if MatchAttributes(left_child, right_child):
        matched = True 
    if not matched:
      return False
  return True
    

def Get(container, matcher):
  '从container中获取与ｍatcher匹配的节点'

  for ele in container:
    if MatchElement(ele, matcher):
      return ele
  return None 
   
    
def BuildAndroidManifestTemplate():
  '构建AndroidManifest.xml匹配模板'

  global AM_TEMPLATE_PREFIX
  global USE_ALIPAY
  global ALIPAY
  global USE_THREE_OPERATOR
  global THREE_OPERATOR_SDK
  global AM_TEMPLATE_SUFFIX
  template = AM_TEMPLATE_PREFIX
  if USE_ALIPAY:
    template += ALIPAY
  if USE_THREE_OPERATOR:
    template += THREE_OPERATOR_SDK
  #...添加其他支付方式相关配置模板
  template += AM_TEMPLATE_SUFFIX
  return template

PATH_NAME_CHECK_LIST = [
  (os.path.join('manifest', 'application', 'meta-data'), 'EGAME_CHANNEL'),
]

def CheckElement(tag, path, name, element, matcher):
  '检查某个节点元素是否匹配模板（包括子节点检查)'

  Log('正在检查节点 [path:' + path + '][name:' + name + ']...')
  # special case 特殊配置检查（只需要检查路径和name，不需要检查value)
  global PATH_NAME_CHECK_LIST
  for (item_path, item_name) in PATH_NAME_CHECK_LIST:
    if item_path == path and item_name == name:
      return True 
  # 1) 属性检查
  for key in matcher.keys():
    if key not in element.keys():
      Log('遗漏属性4:' + key + '[tag:' + tag + '][name:' + name + '][path:' + path+ ']')
      return False
    matcher_attr_value = matcher.get(key)
    element_attr_value = element.get(key)
    if matcher_attr_value != element_attr_value:
      Log('属性值不匹配,应该是:[' + matcher_attr_value + ']却配置成了[' + element_attr_value + ']')
      return False 
  # 2) 子节点检查
  for child in list(matcher):
    child_tag = child.tag
    child_name = child.get(NAME)
    if child_name is None:
      child_name = ''
    child_path = os.path.join(path, child_tag)

    element_children = element.findall(child_tag)
    #full attri match
    element_child = Get(element_children, child)
    #part match
    if element_child is None:
      for ele in element_children:
         # special case 特殊配置检查（只需要检查路径和name，不需要检查value)
         global PATH_NAME_CHECK_LIST
         for (item_path, item_name) in PATH_NAME_CHECK_LIST:
           ele_path = os.path.join(path, ele.tag)
           try:
             ele_name = ele.get(NAME)
           except:
             break
           if ele_name is not None:
             if ele_path == item_path and ele_name == item_name:
               Log('检查到特殊节点，忽略value,只检查路径和名字')
               element_child = ele 
    if element_child is None:
      Log('遗漏配置5：[tag:' + child_tag + '][name:' + child_name  + '][path:' + child_path + ']')
      return False 
    # 递归校验子节点
    
    if not CheckElement(child_tag, child_path, child_name, element_child, child):
      return False

  return True

def CheckEnvironment():
  '环境检查'

  exist = os.path.exists(AM_FILE_NAME)
  if not exist:
    Log('文件' + AM_FILE_NAME + '不存在!')
    return False
  return True

def ParseAndCheckAndroidManifest():
  '解析AndroidManifest.xml并对内容进行校验'

  #忽略名字检查的tag表
  ignore_name_match_tags = [
    'application'
  ]

  # ) parse xml获取包名等信息
  import xml.etree.ElementTree as ET
  tree = ET.parse(AM_FILE_NAME)
  manifest = tree.getroot()
  package_name = manifest.get('package')
  xml_namespace = manifest.get('xmlns:android')

  # ) 预处理 ANDROID_MANIFEST_TEMPLATE
  AM_TEMPLATE = BuildAndroidManifestTemplate()
  template = Template(AM_TEMPLATE).substitute(PACKAGE_NAME=package_name)
  template_root = ET.fromstring(template)
  matchers = list(template_root)
  
  #对于每一个待检查元素进行检查校验
  for matcher in matchers:
    tag = matcher.tag
    name = matcher.get(NAME)
    if not name:
      name = ''

    elements = manifest.findall(tag)
    if len(elements) == 0:
      Log('遗漏配置项1[tag:' + tag + '][name:' + name + ']')
      return False

    #进行name属性检查
    matched_element = None
    if tag not in ignore_name_match_tags:
      for ele in elements:
        me_name = ele.get(NAME)
        if me_name and me_name == name:
          matched_element = ele 
    else:
      matched_element = elements[0]

    if matched_element is None:
      Log('遗漏配置项3[tag:' + tag + '][name:' + name + ']')
      return False

    #递归检查子元素
    if not CheckElement(tag, os.path.join('manifest', tag), name, matched_element, matcher):
      return False
  return True

def Unicode(string):
#  if sys.version[0] >= 3:
#    return unicode(string) 
   return string 

def ParseOptions():
  '解析用户自定义参数'
  parser = optparse.OptionParser()
  parser.add_option('-a', '--alipay', action='store_true', default=False, help=Unicode('忽略对支付宝支付配置进行校验!'))
  parser.add_option('-o', '--operator', action='store_true', default=False, help=Unicode('忽略对运营商支付配置进行校验!'))
  parser.add_option('-i', '--ipp', help=Unicode('[integration project path]的简称,Integration工程的相对目录，如果不设置默认为[../ugpsdk-integration].'))

  options, args = parser.parse_args()

  global ALIPAY
  global USE_THREE_OPERATOR
  global INTEGRATION_PROJECT_PATH
  
  if options.alipay:
    USE_ALIPAY = False
    Log('忽略支付宝支付配置校验')
  if options.operator:
    USE_THREE_OPERATOR = False
    Log('忽略运营商支付配置校验')
  if options.ipp is not None:
    if not ExistFile(os.path.join(options.ipp, 'libs')) or (-1 == options.ipp.find('ugpsdk-integration')):
      Log('Integration 工程目录[' + options.ipp + ']不存在，请检查之后重新设置!')
      return
    INTEGRATION_PROJECT_PATH = options.ipp
  else:
    Log('not specify ipp')

  return options 

def DoMain():
  #)参数检查
  LogTitle('开始参数检查...')
  options = ParseOptions()
  if not options:
    return  
  #) 环境检查 
  LogTitle('开始环境检查...')
  if not CheckEnvironment():
    return 
  #) 读取并解析 AndroidManifest.xml 文件
  LogTitle('开始校验Androidmanifest.xml文件内容...')
  if not  ParseAndCheckAndroidManifest():
    return
  LogTitle('开始检查本地文件配置...')
  #) 检查本地文件配置 
  if not CheckFilesConfig():
    return
  #) 如果未出错，则提示通过检查
  LogTitle('(^_^)恭喜！通过检查，你的配置完全正确!')
    

if __name__ == '__main__':
  DoMain()

#!/usr/bin/python

# argv[1] Your xcode project path
# argv[2] Your project Name  like test.xcodeproj
# argv[3] Kryptanium SDK path. We will copy the SDK to the project directory.
#


import os
import sys
import shutil

from mod_pbxproj import XcodeProject

##### Common Settings.
projectPath = sys.argv[1]

frameworkPath = 'System/Library/Frameworks/';
dylibPath = '/usr/lib/';



#### Kryptannium SDK Settings.
# Dependent Frameworks
frameworks = [
{'name':'OpenGLES.framework','weak':False},
{'name':'UIKit.framework','weak':False},
{'name':'SystemConfiguration.framework','weak':False},
{'name':'QuartzCore.framework','weak':False},
{'name':'MobileCoreServices.framework','weak':False},
{'name':'ImageIO.framework','weak':False},
{'name':'Foundation.framework','weak':False},
{'name':'CoreGraphics.framework','weak':False},
{'name':'CFNetwork.framework','weak':False},
{'name':'AudioToolbox.framework','weak':False},
{'name':'AssetsLibrary.framework','weak':False},
{'name':'StoreKit.framework','weak':True},
{'name':'CoreTelephony.framework','weak':False},
{'name':'CoreText.framework','weak':False},
{'name':'MessageUI.framework','weak':False},
{'name':'CoreLocation.framework','weak':False},
{'name':'AddressBook.framework','weak':False},
{'name':'Accounts.framework','weak':False},
{'name':'Social.framework','weak':False},
{'name':'Twitter.framework','weak':False},
]

# Dependent dylibs.
dylibs = [
'libsqlite3.dylib',
'libz.dylib',
]

#Other linker Flags.
other_ldflags = [
	'-ObjC',
	'-lxml2'
]

#XCODE Build Settings.
build_settings = [
#{'key':'GCC_ENABLE_OBJC_EXCEPTIONS','value':'YES'},
]




#### Methods
def flog(log):
	print log,
	f = open('KryptaniumBuildLogFile.txt','a')
	f.write(log)
	f.close()

def add_frameworks(project):
	flog('\n======== Add Dependent Frameworks ========\n')
	for f in frameworks:
		frame_name = f['name']
		project.add_file_if_doesnt_exist(frameworkPath + frame_name, tree='SDKROOT',weak=f['weak'])
		flog( frame_name + ' \n')


def add_dylibs(project):
	flog('\n======== Add Dependent dylibs ========\n')
	for d in dylibs:
		project.add_file_if_doesnt_exist(dylibPath + d, tree='SDKROOT')
		flog(d +'  \n')

def add_other_ldflags(project):
	flog('\n======== Add Other Linker Flags ========\n')
	for f in other_ldflags:
		project.add_other_ldflags(f)
		flog( f + ' \n')


def change_buildsettings(project):
	flog('\n======== Change Build Settings ========\n')
	for s in build_settings:
		project.mod_buildSettings(s['key'],s['value'])
		flog(s['key'] + '=' + s['value'] + '\n')

def save_project(project):
	project.saveFormat3_2()





#### Script Start.
#flog('Start of python script\n')
flog('project path:\n' + projectPath + '\n')

project = XcodeProject.Load(projectPath + '/project.pbxproj')

add_frameworks(project)
add_dylibs(project)
add_other_ldflags(project)
change_buildsettings(project)
save_project(project)
flog('\nAll done!\n')
#### Script End.

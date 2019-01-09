import subprocess
import ConfigParser
from glob import glob
import os
import sys

configDict = {}


#Installs Dependencies
def update(args):
	subprocess.call(['sudo','apt-get', 'update', '-y'])
	subprocess.call(['sudo','apt', 'install', 'gcc', '-y'])
	subprocess.call(['sudo','apt', 'install', 'wget', '-y'])
	subprocess.call(['sudo','apt', 'install', 'unzip', '-y'])
	subprocess.call(['sudo','apt', 'install', 'rsync', '-y'])

	if not '--without-ssl' in args:
		print 'Installing Openssl'
		subprocess.call(['sudo','apt', 'install', 'openssl', '-y'])
		subprocess.call(['sudo','apt', 'install', 'libssl-dev', '-y'])
	
	if not (configDict['python_version'] == 'None'):
		subprocess.call(['sudo', 'apt-get', 'install', 'python' + configDict['python_version'] + '-dev', '-y'])
	

#Downloads and builds Boost, Swig, and Patchelf.
def init():

	directory = '/usr/share/'
	subprocess.call(['sudo', 'mkdir', '-p', configDict['package_name'] + '/programs/'], cwd=directory)	
	subprocess.call(['sudo', 'chmod', '777', configDict['package_name']], cwd=directory)
	subprocess.call(['sudo', 'chmod', '777', 'programs/'], cwd=directory + configDict['package_name'])
	directory = '/usr/share/' + configDict['package_name'] + '/programs/'
	subprocess.call(['wget',configDict['boost_download']], cwd=directory)
	subprocess.call(['wget',configDict['swig_download']], cwd=directory)
	subprocess.call(['wget',configDict['patchelf_download']], cwd=directory)
	call = 'tar -xzvf ' +  glob(os.path.join(directory, 'boost*'))[0]
	subprocess.check_call(call.split(), cwd=directory)
	call = 'tar -xzvf ' +  glob(os.path.join(directory, 'swig*'))[0]
	subprocess.check_call(call.split(), cwd=directory)
	call = 'tar -xzvf ' +  glob(os.path.join(directory, 'patchelf*'))[0]
	subprocess.check_call(call.split(), cwd=directory)
	call = glob(os.path.join(directory, '*.tar.gz'))
	subprocess.call(['sudo', 'rm'] + call[0].split())
	subprocess.call(['sudo','rm'] + call[1].split())
	subprocess.call(['sudo','rm'] + call[2].split())

	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'swig*'))[0]
	subprocess.call(['./configure', '--without-pcre'], cwd=directory)
	subprocess.call(['sudo', 'make'], cwd=directory)
	subprocess.call(['sudo', 'make', 'install'], cwd=directory)

	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'patchelf*'))[0]
	subprocess.call(['./configure'], cwd=directory)
	subprocess.call(['sudo', 'make', 'install'], cwd=directory)

	directory = '/usr/share/' + configDict['package_name'] + '/programs/'	
	subprocess.call(['wget', configDict['mscl_download']], cwd=directory)
	subprocess.call(['unzip', 'master.zip'], cwd=directory)
	subprocess.call(['mv', 'MSCL-master', '/usr/share/' + configDict['package_name'] + '/programs/MSCL-BUILT/'], cwd=directory)
	subprocess.call(['sudo', 'chmod', '777', 'MSCL-BUILT'], cwd=directory)

	directory = '/usr/share/' + configDict['package_name'] + '/programs/'
	subprocess.call(['cp', directory + '/MSCL-BUILT/LICENSE', '/usr/share/' + configDict['package_name']], cwd=directory)
	subprocess.call(['cp', directory + '/MSCL-BUILT/License_Boost.txt', '/usr/share/' + configDict['package_name']], cwd=directory)
	subprocess.call(['cp', directory + '/MSCL-BUILT/License_OpenSSL.txt', '/usr/share/' + configDict['package_name']], cwd=directory)


	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'boost*'))[0]
	subprocess.call(['./bootstrap.sh', '--with-libraries=system,filesystem,test'], cwd=directory)
	subprocess.call(['./b2', 'install', '--prefix=/usr/share/' + configDict['package_name'] + '/programs/', '-j2'], cwd=directory)

	
	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'boost*'))[0] + '/tools/build'
	subprocess.call(['./bootstrap.sh'], cwd=directory)
	subprocess.call(['./b2', 'install', '--prefix=/usr/share/' + configDict['package_name'] + '/programs/', '-j2'], cwd=directory)

	

#Builds MSCL
def buildMSCL(arg):
	directory = '/usr/share/' + configDict['package_name'] + '/programs/'
	if '--without-ssl' in arg:
		print 'Removing Openssl From Boost'
		call = 'echo using gcc\n:\thost\n:\tg++\n:\t<cxxflags>-I/usr/include/python' + configDict['python_version'] + '\n\t<cxxflags>-I/usr/share/' + configDict['package_name'] + '/programs/include\n\t<linkflags>-L/usr/share/' + configDict['package_name'] + '/programs/lib\n;'
	else:
		call = 'echo using gcc\n:\thost\n:\tg++\n:\t<cxxflags>-I/usr/include/python' + configDict['python_version'] + '\n\t<cxxflags>-I/usr/share/' + configDict['package_name'] + '/programs/include\n\t<cxxflags>-I/usr/include/openssl\n\t<linkflags>-L/usr/share/' + configDict['package_name'] + '/programs/lib\n;'
	
	with open('project-config.jam', 'w') as outfile:
		subprocess.call(call.split(), stdout=outfile)
	subprocess.call(['mv', 'project-config.jam', directory])

	directory = '/usr/share/' + configDict['package_name'] + '/programs/MSCL-BUILT'
	call = glob(os.path.join('/usr/share/' + configDict['package_name'] + '/programs/', 'boost*'))[0] + '/bjam'
	
	flags = ''
	for flag in arg:
		flags += flag + ' '
	
	print 'Flags:', flags
	if (configDict['python_version'] == 'None'):
		mscl_call = 'MSCL//stage_c++ release ' + flags +'-j2'
		subprocess.call(call.split() + mscl_call.split(), cwd=directory)
	else:
		subprocess.call(['mkdir', '-p', 'build/swig-python'], cwd=directory)
		
		mscl_call = 'MSCL//stage_python release' + arg +' -j2'

		subprocess.call(call.split() + mscl_call.split(), cwd=directory)
		subprocess.call(call.split() + mscl_call.split(), cwd=directory)
		
#Moves the required files to a different location 
def moveFiles():
	directory = '/usr/share/' + configDict['package_name'] + '/'
	subprocess.call(['mkdir', '-p', 'Boost'], cwd = directory)

	directory = '/usr/share/doc/'
	subprocess.call(['sudo', 'mkdir', '-p', configDict['package_name'] ], cwd = directory)
	subprocess.call(['sudo', 'chmod', '777', configDict['package_name']], cwd=directory)

	directory = '/usr/share/' + configDict['package_name'] + '/programs/'
	subprocess.call(['cp', directory + '/MSCL-BUILT/LICENSE','/usr/share/doc/' + configDict['package_name'] + '/'], cwd=directory)
	subprocess.call(['cp', directory + '/MSCL-BUILT/License_Boost.txt','/usr/share/doc/' + configDict['package_name'] + '/'], cwd=directory)
	subprocess.call(['cp', directory + '/MSCL-BUILT/License_OpenSSL.txt', '/usr/share/doc/' + configDict['package_name'] + '/'], cwd=directory)
	
	subprocess.call(['cp', '-r', '/usr/share/' + configDict['package_name'] + '/programs/lib', '/usr/share/' + configDict['package_name'] + '/Boost'])
	subprocess.call(['cp', '-r', '/usr/share/' + configDict['package_name'] + '/programs/include', '/usr/share/' + configDict['package_name'] + '/Boost'])
	

	if (configDict['python_version'] == 'None'):
		directory = '/usr/share/' + configDict['package_name'] + '/programs/MSCL-BUILT/MSCL/source/'
		os.chdir(directory)
		os.system('rsync -arv --prune-empty-dirs --include="*/" --include="*.h" --exclude="*" "./" /usr/share/' + configDict['package_name'] + '/source')
		subprocess.call(['cp', '/usr/share/' + configDict['package_name'] + '/programs/MSCL-BUILT/Output/C++/Release/libmscl.so', '/usr/share/' + configDict['package_name'] + '/'])

		subprocess.call(['patchelf', '--set-rpath', '/usr/share/' + configDict['package_name'] + '/Boost/lib', '/usr/share/' + configDict['package_name'] + '/libmscl.so'])
		
	else:
		files = glob(os.path.join('/usr/share/' +  configDict['package_name'] + '/programs/MSCL-BUILT/Output/', 'Python/*'))
		
		
		for file in files:
			call = 'cp -r ' + file + ' /usr/share/' + configDict['package_name']
			subprocess.call(call.split())
		
		call = 'patchelf --set-rpath /usr/share/' + configDict['package_name'] + '/Boost/lib /usr/share/' + configDict['package_name'] + '/_mscl.so'
		subprocess.call(call.split())

#Removes any programs/files that are not required
def cleanup():
	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'swig*'))[0]
	subprocess.call(['sudo', 'make', 'uninstall'], cwd=directory)

	directory =  glob(os.path.join( '/usr/share/' + configDict['package_name'] +'/programs/', 'patchelf*'))[0]
	subprocess.call(['sudo', 'make', 'uninstall'], cwd=directory)

	subprocess.call(['sudo', 'rm', '-r', 'programs'], cwd='/usr/share/' + configDict['package_name'])

def readConfigFile(configLoc):
	cfgFile = open(configLoc, "r")
	_parseConfig(cfgFile)

def _parseConfig(cfgFile):
	parser = ConfigParser.ConfigParser()
	parser.readfp(cfgFile)	

	configDict['package_name'] = parser.get("PACKAGE_INFO", "package_name")
	configDict['python_version'] = parser.get("PACKAGE_INFO", "python_version")

	configDict['boost_download'] = parser.get("PROGRAMS", "boost")
	configDict['swig_download'] = parser.get("PROGRAMS", "swig")
	configDict['mscl_download'] = parser.get("PROGRAMS", "mscl")
	configDict['patchelf_download'] = parser.get("PROGRAMS", "patchelf")

if __name__=="__main__":
	readConfigFile('config.cfg')
	update(sys.argv[1:])
	init()
	buildMSCL(sys.argv[1:])
	moveFiles()
	cleanup()




	




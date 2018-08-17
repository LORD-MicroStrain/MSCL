import subprocess
import ConfigParser

configDict = {}


def remove():
	subprocess.call(['sudo', 'rm', '-r', configDict['package_name']], cwd='/usr/share/')

	directory = '/usr/share/doc/'
	subprocess.call(['sudo','rm', '-r', configDict['package_name'] ], cwd = directory)
		
def readConfigFile(configLoc):
	cfgFile = open(configLoc, "r")
	_parseConfig(cfgFile)

def _parseConfig(cfgFile):
	parser = ConfigParser.ConfigParser()
	parser.readfp(cfgFile)	

	configDict['package_name'] = parser.get("PACKAGE_INFO", "package_name")


if __name__=="__main__":
	readConfigFile('config.cfg')
	remove()




	




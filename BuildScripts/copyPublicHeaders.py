import sys
import os
from shutil import copytree, ignore_patterns, rmtree
from os.path import join

debug = False

def main(args):
    if len(args) < 3:
        print "copyPublicHeaders.py copies all header (.h) files that have the string 'PUBLIC_HEADER' in their contents"
        print "Use: copyPublicHeaders.py sourceDirectory outputDirectory [options]"
        print "Available Options: -d :Prints out all the file names that are being copied."
        sys.exit(2)

    if len(args) > 3:
        if '-d' in args[3]:
            global debug
            debug = True

    print "(copyPublicHeaders.py) Copying Public Header Files..."

    copyAndOverwriteHeaders(args[1], args[2])

    #remove any empty directories that were created
    removeEmptyDirs(args[2])

    print "(copyPublicHeaders.py) Done."

def copyAndOverwriteHeaders(fromPath, toPath):
    if os.path.exists(toPath):
        rmtree(toPath)

    #copy all of the header files, ignoring files that don't have 'PUBLIC_HEADER' on their first line
    copytree(fromPath, toPath, ignore=findFilesToIgnore)

def findFilesToIgnore(path, names):

    privateHeaders = []

    #loop through all the file names
    for fileName in names:

        #only want to look at .h (header) files
        if '.h' in fileName:
            fullFilePath = path + "/" + fileName
            with open(fullFilePath, 'r') as f:
                
                fdata = f.read()
                
                if 'PUBLIC_HEADER' not in fdata:
                    privateHeaders.append(fileName)
                
        elif '.' in fileName:
            #throw out all .cpp and other files
            privateHeaders.append(fileName)

    return privateHeaders

def removeEmptyDirs(path):
    for root, dirs, files in os.walk(path, topdown=False):
        for name in dirs:
            fname = join(root, name)
            if not os.listdir(fname):   #check whether the directory is empty
                os.removedirs(fname)

if __name__ == "__main__":
    main(sys.argv)
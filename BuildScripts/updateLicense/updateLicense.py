# updates the copyright information for all files in the 'extensions' global variable

import sys
import os

excludeDirs = []
extensions = ".cpp", ".h"

def main(args):
    if len(args) < 4:
        print "updateLicense.py updates the copyright/license info for all .cpp and .h files."
        print "Usage: updateLicense.py parentDirectory oldCopyrightFile newCopyrightFile"
        print "As an optional 4th parameter, you can include a comma separated string of folders to exclude."
        sys.exit(2)
        
    print "(updateLicense.py) Updating license text..."
    
    global excludeDirs
        
    if len(args) > 4:
        excludeDirs = [os.path.normpath(i) for i in args[4].split(",")]
        
        print "Excluding",
        for dir in excludeDirs:
          print dir + " ",
          
        print " "

    oldTxt = file(args[2],"r+").read()
    newTxt = file(args[3],"r+").read()
    
    if oldTxt == newTxt:
      print "Copyright/License text hasn't changed!"
      sys.exit(2)

    recursive_traversal(args[1], oldTxt, newTxt)
    
    print "(updateLicense.py) Done."

def update_source(filename, oldcopyright, copyright):
    utfstr = chr(0xef)+chr(0xbb)+chr(0xbf)
    fdata = file(filename,"r+").read()
    isUTF = False
    if (fdata.startswith(utfstr)):
        isUTF = True
        fdata = fdata[3:]
    if (oldcopyright != None):
        if (fdata.startswith(oldcopyright)):
            fdata = fdata[len(oldcopyright):]
    if not (fdata.startswith(copyright)):
        print "updating " + filename
        fdata = copyright + fdata
        if (isUTF):
            file(filename,"w").write(utfstr+fdata)
        else:
            file(filename,"w").write(fdata)

def recursive_traversal(dir, oldcopyright, copyright):
    fns = os.listdir(dir)
    print "found directory: " + dir
    for fn in fns:
        fullfn = os.path.join(dir,fn)
        if (fullfn in excludeDirs):
            print "skipping " + fullfn
            continue
        if (os.path.isdir(fullfn)):
            recursive_traversal(fullfn, oldcopyright, copyright)
        else:
            if (fullfn.endswith(extensions)):
                update_source(fullfn, oldcopyright, copyright)

if __name__ == "__main__":
    main(sys.argv)
import sys
import os
import re
import glob

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKCYAN = '\033[96m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

ovr_aliases = {
      "CC": "221",
      "AA": "222",
      "RR": "223",
      "TT": "224",
      "VB": "225",
      "X1": "226",
      "X2": "227",
      "X3": "228",
      "X4": "229",
      "MM": "230",
      "RB": "231",
      "AH": "232",
      "CS": "233",
}

def filterByOverlay(symbolData, overlay = None):
   # if overlay == None, then filter to main exe
   filteredSymbolData = dict()
   for name in symbolData.keys():
      m = re.fullmatch("([A-Za-z0-9]{2})_.*", name)
      if m == None:
         if overlay == None:
            filteredSymbolData[name] = symbolData[name] #include in result
      elif m.group(1) in ovr_aliases:
         if ovr_aliases[m.group(1)] == overlay:
            filteredSymbolData[name] = symbolData[name] #include in result
   return filteredSymbolData

def budget(name, size, symbolData, verbose = False):
   #filterByOverlay(symbolData, "231")
   # OVRNUMBER_"Block"SUFFIX      "Block" is literal TODOTODOTODOTODOTODOTODOTODOTODOTODOTODO
   # OVRNUMBER_"Full"             "Full" is literal
   ovrfull = re.fullmatch("([0-9]+?)_Full", name) # group 1 is OVRNUMBER
   # OVRNUMBER_INDEX_NAME
   ovrindex = re.fullmatch("([0-9]+?)_([0-9]+?)_(.+?)", name) # group 1 is OVRNUMBER, group 2 is INDEX, group 3 is NAME
   # OVRNUMBER_INDEX-RANGE_NAME
   ovrindexrange = re.fullmatch("([0-9]+?)_([0-9]+?)-([0-9]+?)_(.+?)", name) # group 1 is OVRNUMBER, group 2 is STARTINDEX, group 3 is ENDINDEX, group 4 is NAME
   # NAMESPACE_INDEX_NAME
   nsindex = re.fullmatch("([A-Za-z].+?)_([0-9]+?)_(.+?)", name) # group 1 is NAMESPACE, group 2 is INDEX, group 3 is NAME
   # NAMESPACE_INDEX-RANGE_NAME
   nsindexrange = re.fullmatch("([A-Za-z].+?)_([0-9]+?)-([0-9]+?)_(.+?)", name) # group 1 is NAMESPACE, group 2 is STARTINDEX, group 3 is ENDINDEX, group 4 is NAME
   # otherwise, just compare names straightforwardly
   mcount = len([x for x in [ovrfull, ovrindex, ovrindexrange, nsindex, nsindexrange] if x != None])
   if (mcount > 1):
      print(f"{bcolors.HEADER}Item \"{name}\" adheres to multiple naming conventions, unable to associate and cannot calculate bytebudget")
   elif (mcount == 0):
      print(f"{bcolors.HEADER}Item \"{name}\" adheres to no naming conventions, unable to associate and cannot calculate bytebudget")
   else:
      if ovrfull != None: #Full OVR
         ovrnum = ovrfull.group(1)
         lookupName = name
         translateStart = {
            "221_Full": "OVR_Region1",
            "222_Full": "OVR_Region1",
            "223_Full": "OVR_Region1",
            "224_Full": "OVR_Region1",
            "225_Full": "OVR_Region1",
         }
         translateEnd = {
            "221_Full": "CC_EndOfFile",
            "222_Full": "AA_EndOfFile",
            "223_Full": "RR_EndOfFile",
            "224_Full": "TT_EndOfFile",
            "225_Full": "VB_EndOfFile",
         }
         ovrSymbolData = dict()
         if lookupName in translateStart:
            end = translateEnd[lookupName]
            if end in symbolData:
               ovrSymbolData[end] = symbolData[end]
            lookupName = translateStart[lookupName]
            ovrSymbolData[lookupName] = symbolData[lookupName]
         else:
            ovrSymbolData = filterByOverlay(symbolData, ovrnum)
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName] #assume 1 candidate for now
            if candidates[0] == len(sortedOvr) - 1: #candidate is the last one in the list
               print(f"{bcolors.WARNING}WARNING: Item \"{name}\" was interpreted as \"OVRNUMBER_Full\" and is the last known symbol in its region, cannot automatically compare to successor. (size = {size}). Compare it's size manually to ((location_of_last_function + size_of_last_function) - location_of_first_function) to determine bytebudget adherance.")
            else:
               ourself = sortedOvr[candidates[0]]
               next = sortedOvr[candidates[0] + 1]
               gap = next[1][0] - ourself[1][0]
               if gap < size:
                  print(f"{bcolors.FAIL}WARNING: Item \"{name}\" is overbudget (size = {size}) and clobbers {next[0]} by {size - gap}.")
               elif verbose:
                  if gap == size:
                     print(f"{bcolors.WARNING}Item \"{name}\" is *exactly* on budget.")
                  else:
                     print(f"{bcolors.OKGREEN}Item \"{name}\" is underbudget by {gap - size} bytes.")
         elif verbose:
            print(f"{bcolors.WARNING}Item \"{name}\" was interpreted as \"OVRNUMBER_Full\", but didn't find a viable candidate, cannot calculate bytebudget.")
      elif ovrindex != None: #Index into an OVR
         ovrnum = ovrindex.group(1)
         ind = ovrindex.group(2)
         n = ovrindex.group(3)
         #name = ovrindex.group(3)
         #if name in singular_byte_budget:
         #    if (file_size > singular_byte_budget[name]):
         #        print("Function: " + name + " in " + objectname + " over budget by " + str(file_size - singular_byte_budget[name]) + " bytes.")
         #else:
         #    print("Item \"" + objectfullname + "\" was interpreted as \"OVRNUMBER_INDEX_NAME\", but didn't find a viable candidate, unable to associate and cannot calculate bytebudget.")
      elif ovrindexrange != None: #Index range into an OVR
         #print("Item \"" + objectfullname + "\" was interpreted as \"OVRNUMBER_INDEX-RANGE_NAME\", but didn't find a viable candidate, unable to associate and cannot calculate bytebudget.")
         ovrnum = ovrindexrange.group(1)
         ind = ovrindexrange.group(2)
         eind = ovrindexrange.group(3)
         n = ovrindexrange.group(4)
      elif nsindex != None: #Single named file
         ns = nsindex.group(1)
         ind = nsindex.group(2)
         n = nsindex.group(3)
         lookupName = ns + "_" + n
         ovrSymbolData = filterByOverlay(symbolData, None) #main exe
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName] #assume 1 candidate for now
            #TODO: loop over candidates[0]+1/+2/+3... and list *all* the clobbered symbols
            if candidates[0] == len(sortedOvr) - 1: #candidate is the last one in the list
               print(f"{bcolors.WARNING}WARNING: Item \"{name}\" is the last known symbol in its region, cannot compare to successor.")
            else:
               ourself = sortedOvr[candidates[0]]
               next = sortedOvr[candidates[0] + 1]
               gap = next[1][0] - ourself[1][0]
               if gap < size:
                  print(f"{bcolors.FAIL}WARNING: Item \"{name}\" is overbudget and clobbers {next[0]} by {size - gap}.")
               elif verbose:
                  if gap == size:
                     print(f"{bcolors.WARNING}Item \"{name}\" is *exactly* on budget.")
                  else:
                     print(f"{bcolors.OKGREEN}Item \"{name}\" is underbudget by {gap - size} bytes.")
         elif verbose:
            print(f"{bcolors.WARNING}Item \"{name}\" was interpreted as \"NAMESPACE_INDEX_NAME\", but didn't find a viable candidate, cannot calculate bytebudget.")
      elif nsindexrange != None: #Range of things starting at a single named file
         #print("Item \"" + objectfullname + "\" was interpreted as \"NAMESPACE_INDEX-RANGE_NAME\", but didn't find a viable candidate, unable to associate and cannot calculate bytebudget.")
         ns = nsindexrange.group(1)
         ind = nsindexrange.group(2)
         eind = nsindexrange.group(3)
         n = nsindexrange.group(4)
      else:
          print(f"{bcolors.FAIL}This message should be impossible to appear. Tell TheUbMunster if this happens.")


   # if objectname in singular_byte_budget:
   #     if (file_size > singular_byte_budget[objectname]):
   #         print("Function: " + objectname + " over budget by " + str(file_size - singular_byte_budget[objectname]) + " bytes.")
   # else:
   #     print("Item \"" + objectfullname + "\" not a c.bin, didn't find any other viable candidate, unable to associate and cannot calculate bytebudget.")
   return

# def testGccSyms(gccSyms, symbols):
#    #this doesn't quite work because of overlays
#    success = True
#    seen = set()
#    #check gcc-syms for duplicate addresses
#    for gsym in gccSyms:
#       if gsym[0] in seen:
#          print("ERROR: duplicate address entry in gcc-syms for " + gsym[1])
#          success = False
#       else:
#          seen.add(gsym[0])
#    #check gcc-syms for duplicate symbols
#    seen.clear()
#    for gsym in gccSyms:
#       if gsym[1] in seen:
#          print("ERROR: duplicate symbol entry in gcc-syms for " + gsym[1])
#          success = False
#       else:
#          seen.add(gsym[1])
#    #check syms for duplicate addresses
#    seen.clear()
#    for sym in symbols:
#       if sym[0] in seen:
#          print("ERROR: duplicate address entry in syms for " + sym[1])
#          success = False
#       else:
#          seen.add(sym[0])
#    #check syms for duplicate symbols
#    seen.clear()
#    for sym in symbols:
#       if sym[1] in seen:
#          print("ERROR: duplicate symbol entry in syms for " + sym[1])
#          success = False
#       else:
#          seen.add(sym[1])

#    for gsym in gccSyms:
#       if all(gsym[1] != x[1] for x in symbols):
#          print("ERROR: gcc-syms symbol " + gsym[1] + " is not present in syms")
#          success = False
#       for sym in symbols:
#          if (gsym[1] == sym[1] and gsym[0] != sym[0]): #symbol matches but address doesn't
#             print("ERROR: gcc-syms symbol " + gsym[1] + " address mismatch with syms")
#             success = False
#    return success

def main():
   #arg 0 is .py, arg 1 is gccsyms, arg 2 is syms, arg 3 is /output
   argv = sys.argv
   if len(argv) == 1:
      argv.append("D:/source/c/psx-modding-toolchain/games/theubm-ctr-modsdk/symbols/gcc-syms926.txt")
      argv.append("D:/source/c/psx-modding-toolchain/games/theubm-ctr-modsdk/symbols/syms926.txt")
      argv.append("D:/source/c/psx-modding-toolchain/games/theubm-ctr-modsdk/decompile/output/")
      argv.append("-v")
   verbose = argv.__contains__("-v")
   if "-v" in argv:
      argv.remove("-v")
   else:
      print("Reminder: call byteBudget.bat with the `-v` argument for verbose results")
   if len(argv) != 4:
      print("ERROR: improper number of arguments to byteBudget's main.py")
      exit(-1)
   
   #this file is made with 926 (ntsc-u) in mind

   print("WARNING!!! This tool is not perfect, there are a few circumstances it will not be useful:")
   print("\t* if the functionality of a function being clobbered is implemented elsewhere, budget() will fail")
   print("\t* OVR_Full.c's are assumed to be linked to the same address as the first function in that overlay")
   print("\t* if gcc-/syms926.txt is inaccurate (duplicate entries, incorrect addresses, name collisions etc.), this tool will be inaccurate")
   print("\t* if there are more symbols in the original binary subsequent to another symbol, but not in gcc-/syms.926.txt (clobbered without telling you)")

   #gcc-syms
   gccsyms_filename = argv[1]
   buff = str()
   with open(gccsyms_filename, "r") as file:
      buff = file.read()
   matches = re.findall("^\s*([a-zA-Z_][a-zA-Z0-9_]*?)\s*=\s*(0x[0-9A-Fa-f]+);", buff, re.MULTILINE)
   gccSyms = []
   for match in matches:
      symbol = match[0]
      address = match[1]
      gccSyms.append((int(address.strip(), 16), symbol.strip()))
   gccSyms.sort(key=lambda x: x[0])

   #syms
   syms_filename = argv[2]
   buff = str()
   with open(syms_filename, "r") as file:
      buff = file.read()
   matches = re.findall("^\s*([0-9A-Fa-f]{8})\s+([a-zA-Z_][a-zA-Z0-9_]+?)[^a-zA-Z0-9_]", buff, re.MULTILINE) #this regex will fail if there are /**/ multiline comments or if there is more than one entry per line
   syms = []
   for match in matches:
      address = "0x" + match[0]
      symbol = match[1]
      syms.append((int(address.strip(), 16), symbol.strip()))
   syms.sort(key=lambda x: x[0])

   if verbose:
      print("gcc-syms has " + str(len(gccSyms)) + " entries, and syms has " + str(len(syms)) + " entries.")

   #if not testGccSyms(gccSyms, syms): #ensures that no gcc/syms entry mismatches an address
   #   print("Unable to perform bytebudget calculation.")
   #   exit(-1)

   symbolData = dict() #(name, (address, isUsed))
   
   for gsym in gccSyms:
      symbolData[gsym[1]] = (gsym[0], True)
   for sym in syms:
      if all(x != sym[1] for x in symbolData.keys()):
         symbolData[sym[1]] = (sym[0], False)

   object_files = glob.glob(argv[3] + "*")
   for object in object_files:
      file_size = os.path.getsize(object)
      objectfullname = object.replace("\\", "/").split("/")[-1] #get filename from filepath
      if (objectfullname.endswith("c.bin")):
         objectname = objectfullname[:len(objectfullname) - len("c.bin")]
         budget(objectname, file_size, symbolData, verbose)
      else:
         objectname = objectfullname[:len(objectfullname) - len(".bin")] # not a c.bin
         print(objectname + " is not a cbin")
         #budget(objectname, file_size, symbolData, verbose)
   print("\nPress any key to exit.")
   input()

main()
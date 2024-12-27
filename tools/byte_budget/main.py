import sys
import os
import re
import glob

#yellow: exactly matches bytebudget
#green: between 90%-100% bytebudget
#yellow green: less than 90% bytebudget (silent clobbering)
#red: above bytebudget
#magenta: unable to interpret
#light blue: exactly matches bytebudget (for large block)
#royal blue: 90%-100% bytebudget (for large block)
#inbetween blue: less than 80% bytebudget (silent clobbering)
#orange: important to note
#bold & underlined: headings
class ccolor:
   YELLOW = '\x1b[38;5;226m'
   GREEN = '\x1b[38;5;46m'
   YELLOWGREEN = '\x1b[38;5;190m'
   RED = '\x1b[38;5;196m'
   MAGENTA = '\x1b[38;5;164m'
   BLUE = '\x1b[38;5;57m'
   IBBLUE = '\x1b[38;5;129m'
   ORANGE = '\x1b[38;5;208m'
   WHITE = '\x1b[37m'

#nonverbose
#print overbudget items, list of clobbered

#verbose print everything:
#  * previous neighbor (symbol)
#  * ourself (symbol, size)
#  * clobber amount, list of subsequent clobbered symbols, info of (batches of) symbols of clobbered symbols in overlay
#  * next neighbor (symbol)
#  * disclaimers about this item (e.g., if this is a "OVR_Full" item, then note that any ND functions that aren't decomped will obviously not point to the relocated symbols in this overlay)

processedSymbols = dict()

class SymbolName:
   def __init__(self, namespace, index, endIndex, name, ovrNum):
      self.namespace = namespace
      self.index = index
      self.endIndex = endIndex
      self.name = name
      self.ovrNum = ovrNum
   def __str__(self):
      if self.namespace != None:
         return f"{self.namespace}_{self.name}"
      else:
         if (self.ovrNum != None):
            return f"{self.ovrNum}_{self.name}"
         else:
            return self.name
   def __hash__(self):
      return hash(str(self))
   def __eq__(self, other):
      return (self.namespace, self.name) == (other.namespace, other.name)
   def __ne__(self, other):
      return not(self == other)
   def reconstructFileName(self):
      rfn = ""
      if (self.ovrNum != None):
         rfn += f"{self.ovrNum}_"
         if (self.index != None):
            rfn += f"{self.index}_"
         if (self.endIndex != None):
            rfn += f"{self.endIndex}_"
         if (self.namespace != None):
            rfn += f"{self.namespace}_"
         if (self.name != None):
            rfn += f"{self.name}.c"
      else:
         if (self.namespace != None):
            rfn += f"{self.namespace}_"
         if (self.index != None):
            rfn += f"{self.index}_"
         if (self.endIndex != None):
            rfn += f"{self.endIndex}_"
         if (self.name != None):
            rfn += f"{self.name}.c"
      return rfn


class SymbolInfo:
   def __init__(self, ourselfSymbolName, previousName, nextName, ourselfSymbolResponsibilityCount, ourselfActualSizeBytes, ourselfCaveSizeBytes, notes = None, verboseOnly = True): #clobberNameList,
      self.ourselfSymbolName = ourselfSymbolName
      self.previousName = previousName
      self.nextName = nextName
      self.ourselfSymbolResponsibilityCount = ourselfSymbolResponsibilityCount
      self.ourselfActualSizeBytes = ourselfActualSizeBytes
      self.ourselfCaveSizeBytes = ourselfCaveSizeBytes
      self.notes = "" if notes == None else notes
      self.verboseOnly = verboseOnly

   def getBudgetColor(self):
      if (self.ourselfSymbolResponsibilityCount == 1):
         budgetColor = ccolor.GREEN
      else:
         budgetColor = ccolor.BLUE
      budgetRatio = float(self.ourselfActualSizeBytes) / float(0.01 if self.ourselfCaveSizeBytes == None else self.ourselfCaveSizeBytes)
      if (budgetRatio > 1):
         budgetColor = ccolor.RED
      elif (budgetRatio >= 0.9 and budgetRatio <= 1):
         if (self.ourselfSymbolResponsibilityCount == 1):
            budgetColor = ccolor.YELLOWGREEN
         else:
            budgetColor = ccolor.IBBLUE
      if (self.ourselfActualSizeBytes == self.ourselfCaveSizeBytes):
         if (self.ourselfSymbolResponsibilityCount == 1):
            budgetColor = ccolor.YELLOWGREEN
         else:
            budgetColor = ccolor.IBBLUE
      return budgetColor

   def getBudgetMessage(self):
      budgetMessage = "significantly underbudget:"
      budgetRatio = float(self.ourselfActualSizeBytes) / float(0.01 if self.ourselfCaveSizeBytes == None else self.ourselfCaveSizeBytes)
      if (budgetRatio > 1):
         budgetMessage = "overbudget:"
      elif (budgetRatio >= 0.9 and budgetRatio <= 1):
         budgetMessage = "underbudget:"
      if (self.ourselfActualSizeBytes == self.ourselfCaveSizeBytes):
         budgetMessage = "exactly on budget:"
      return budgetMessage

   def __str__(self):
      budgetMessage = self.getBudgetMessage()
      budgetColor = self.getBudgetColor()
      return f"""{ccolor.WHITE}* {budgetColor}{self.ourselfSymbolName} is {budgetMessage}
      {ccolor.WHITE}\t- Byte Budget: {budgetColor}{self.ourselfActualSizeBytes}{ccolor.WHITE} / {"[unknown]" if self.ourselfCaveSizeBytes == None else self.ourselfCaveSizeBytes}
      {ccolor.WHITE}\t- Reconstructed filename: {self.ourselfSymbolName.reconstructFileName()}
      {ccolor.WHITE}\t- Interpreted namespace: {self.ourselfSymbolName.namespace}
      {ccolor.WHITE}\t- Previous neighbor: {self.previousName}
      {ccolor.WHITE}\t- Next neighbor: {self.nextName}
      {ccolor.WHITE}\t- Notes: {"[None]" if self.notes == None else self.notes}"""

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
      if m != None and m.group(1) in ovr_aliases:
         if ovr_aliases[m.group(1)] == overlay:
            filteredSymbolData[name] = symbolData[name] #include in result
      else:
         if overlay == None:
            filteredSymbolData[name] = symbolData[name] #include in result
   return filteredSymbolData

def budget(name, size, symbolData, verbose = False):
   # OVRNUMBER_"Block"SUFFIX      "Block" is literal TODOTODOTODOTODOTODOTODOTODOTODOTODOTODO

   # OVRNUMBER_"Full"             "Full" is literal
   ovrfull = re.fullmatch("([0-9]+?)_((?:Full)|(?:Defrag))", name) # group 1 is OVRNUMBER, group 2 is ?NAME?
   # NAMESPACE_"Full"
   #nsfull = re.fullmatch("([A-Za-z]+?)_((?:Full)|(?:Defrag))", name) # group 1 is NAMESPACE, group 2 is ?NAME?
   # OVRNUMBER_INDEX_NAME
   ovrindex = re.fullmatch("([0-9]+?)_([0-9]+?)_([A-Za-z].+?)", name) # group 1 is OVRNUMBER, group 2 is INDEX, group 3 is NAME
   # OVRNUMBER_INDEX_RANGE_NAME
   ovrindexrange = re.fullmatch("([0-9]+?)_([0-9]+?)_([0-9]+?)_([A-Za-z].+?)", name) # group 1 is OVRNUMBER, group 2 is STARTINDEX, group 3 is ENDINDEX, group 4 is NAME
   # NAMESPACE_INDEX_NAME
   nsindex = re.fullmatch("([A-Za-z]+?)_([0-9]+?)_([A-Za-z].+?)", name) # group 1 is NAMESPACE, group 2 is INDEX, group 3 is NAME
   # NAMESPACE_INDEX_RANGE_NAME
   nsindexrange = re.fullmatch("([A-Za-z]+?)_([0-9]+?)_([0-9]+?)_([A-Za-z].+?)", name) # group 1 is NAMESPACE, group 2 is STARTINDEX, group 3 is ENDINDEX, group 4 is NAME
   # otherwise, just compare names straightforwardly
   mcount = len([x for x in [ovrfull, ovrindex, ovrindexrange, nsindex, nsindexrange] if x != None])
   if (mcount > 1):
      print(f"{ccolor.MAGENTA}Item \"{name}\" adheres to [multiple] naming conventions, unable to associate and cannot calculate bytebudget")
   elif (mcount == 0):
      print(f"{ccolor.MAGENTA}Item \"{name}\" adheres to [no] naming conventions, unable to associate and cannot calculate bytebudget")
   else:
      # ===============================================================================================================
      if ovrfull != None: #Full OVR
         ovrnum = ovrfull.group(1)
         blockname = ovrfull.group(2)
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

         sn = SymbolName(None, None, None, blockname, ovrnum)
         processedSymbols[sn] = SymbolInfo(sn, None, None, 0, size, None)

         processedSymbols[sn].notes += f"Item \"{name}\" was interpreted as \"OVRNUMBER_Full\""

         lookupName = sn.ovrNum + "_" + sn.name

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
            if (len(candidates) == 0):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had no valid lookup candidate."
            if (len(candidates) > 1):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had a name collision during lookup."
            else:
               previ = candidates[0] - 1
               if (previ > 0):
                  sprev = sortedOvr[previ]
                  processedSymbols[sn].previousName = sprev[0]
               lastPlusOnei = candidates[0] + 1
               if (lastPlusOnei < len(sortedOvr)):
                  sLastPlusOne = sortedOvr[lastPlusOnei]
                  sourself = sortedOvr[candidates[0]]
                  processedSymbols[sn].nextName = sLastPlusOne[0]
                  gap = sLastPlusOne[1][0] - sourself[1][0]
                  processedSymbols[sn].ourselfCaveSizeBytes = gap
                  if (processedSymbols[sn].ourselfCaveSizeBytes < processedSymbols[sn].ourselfActualSizeBytes):
                     processedSymbols[sn].verboseOnly = False
         elif verbose:
            processedSymbols[sn].verboseOnly = False
            processedSymbols[sn].notes += f" {ccolor.ORANGE}[WARNING]: but didn't find a viable candidate, cannot calculate bytebudget.\n\tCompare it's size manually to ((location_of_last_function + size_of_last_function) - location_of_first_function) to determine bytebudget adherance."
      # ===============================================================================================================
      elif ovrindex != None: #Index into an OVR
         ovrnum = ovrindex.group(1)
         ind = ovrindex.group(2)
         n = ovrindex.group(3)

         sn = SymbolName(None, ind, None, n, ovrnum)
         processedSymbols[sn] = SymbolInfo(sn, None, None, 1, size, None)

         processedSymbols[sn].notes += f"Item \"{name}\" was interpreted as \"OVRNUMBER_INDEX_NAME\""

         lookupName = sn.name

         ovrSymbolData = filterByOverlay(symbolData, ovrnum)
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName]
            if (len(candidates) == 0):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had no valid lookup candidate."
            elif (len(candidates) > 1):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had a name collision during lookup."
            else:
               previ = candidates[0] - 1
               if (previ > 0):
                  sprev = sortedOvr[previ]
                  processedSymbols[sn].previousName = sprev[0]
               nexti = candidates[0] + 1
               if (nexti < len(sortedOvr)):
                  snext = sortedOvr[nexti]
                  sourself = sortedOvr[candidates[0]]
                  processedSymbols[sn].nextName = snext[0]
                  gap = snext[1][0] - sourself[1][0]
                  processedSymbols[sn].ourselfCaveSizeBytes = gap
                  if (processedSymbols[sn].ourselfCaveSizeBytes < processedSymbols[sn].ourselfActualSizeBytes):
                     processedSymbols[sn].verboseOnly = False
               else:
                  processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" is the last known symbol in its region, cannot compare to successor."
         elif verbose:
            processedSymbols[sn].verboseOnly = False
            processedSymbols[sn].notes += f" {ccolor.ORANGE}[WARNING]: but didn't find a viable candidate, cannot calculate bytebudget."
      # ===============================================================================================================
      elif ovrindexrange != None: #Index range into an OVR
         ovrnum = ovrindexrange.group(1)
         ind = ovrindexrange.group(2)
         eind = ovrindexrange.group(3)
         n = ovrindexrange.group(4)
         irange = (int(eind) - int(ind)) + 1

         sn = SymbolName(None, ind, eind, n, ovrnum)
         processedSymbols[sn] = SymbolInfo(sn, None, None, irange, size, None)

         processedSymbols[sn].notes += f"Item \"{name}\" was interpreted as \"OVRNUMBER_INDEX_RANGE_NAME\""

         lookupName = sn.name

         ovrSymbolData = filterByOverlay(symbolData, ovrnum)
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName]
            if (len(candidates) == 0):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had no valid lookup candidate."
            elif (len(candidates) > 1):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had a name collision during lookup."
            else:
               previ = candidates[0] - 1
               if (previ > 0):
                  sprev = sortedOvr[previ]
                  processedSymbols[sn].previousName = sprev[0]
               lastPlusOnei = candidates[0] + irange
               if (lastPlusOnei < len(sortedOvr)):
                  sLastPlusOne = sortedOvr[lastPlusOnei]
                  sourself = sortedOvr[candidates[0]]
                  processedSymbols[sn].nextName = sLastPlusOne[0]
                  gap = sLastPlusOne[1][0] - sourself[1][0]
                  processedSymbols[sn].ourselfCaveSizeBytes = gap
                  if (processedSymbols[sn].ourselfCaveSizeBytes < processedSymbols[sn].ourselfActualSizeBytes):
                     processedSymbols[sn].verboseOnly = False
               else:
                  processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" spans a range larger than its known region, cannot compare to successors."
         elif verbose:
            processedSymbols[sn].verboseOnly = False
            processedSymbols[sn].notes += f" {ccolor.ORANGE}[WARNING]: but didn't find a viable candidate, cannot calculate bytebudget."
      # ===============================================================================================================
      elif nsindex != None: #Single named file
         ns = nsindex.group(1)
         ind = nsindex.group(2)
         n = nsindex.group(3)

         sn = SymbolName(ns, ind, None, n, None)
         processedSymbols[sn] = SymbolInfo(sn, None, None, 1, size, None)

         processedSymbols[sn].notes += f"Item \"{name}\" was interpreted as \"NAMESPACE_INDEX_NAME\""

         lookupName = sn.namespace + "_" + sn.name

         ovrSymbolData = filterByOverlay(symbolData, None) # None = main exe
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName]
            if (len(candidates) == 0):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had no valid lookup candidate."
            elif (len(candidates) > 1):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had a name collision during lookup."
            else:
               previ = candidates[0] - 1
               if (previ > 0):
                  sprev = sortedOvr[previ]
                  processedSymbols[sn].previousName = sprev[0]
               nexti = candidates[0] + 1
               if (nexti < len(sortedOvr)):
                  snext = sortedOvr[nexti]
                  sourself = sortedOvr[candidates[0]]
                  processedSymbols[sn].nextName = snext[0]
                  gap = snext[1][0] - sourself[1][0]
                  processedSymbols[sn].ourselfCaveSizeBytes = gap
                  if (processedSymbols[sn].ourselfCaveSizeBytes < processedSymbols[sn].ourselfActualSizeBytes):
                     processedSymbols[sn].verboseOnly = False
               else:
                  processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" is the last known symbol in its region, cannot compare to successor."
         elif verbose:
            processedSymbols[sn].verboseOnly = False
            processedSymbols[sn].notes += f" {ccolor.ORANGE}[WARNING]: but didn't find a viable candidate, cannot calculate bytebudget."
      # ===============================================================================================================
      elif nsindexrange != None: #Range of things starting at a single named file
         ns = nsindexrange.group(1)
         ind = nsindexrange.group(2)
         eind = nsindexrange.group(3)
         n = nsindexrange.group(4)
         irange = (int(eind) - int(ind)) + 1

         sn = SymbolName(ns, ind, eind, n, None)
         processedSymbols[sn] = SymbolInfo(sn, None, None, irange, size, None)

         processedSymbols[sn].notes += f"Item \"{name}\" was interpreted as \"NAMESPACE_INDEX_RANGE_NAME\""

         lookupName = sn.namespace + "_" + sn.name

         ovrSymbolData = filterByOverlay(symbolData, None)
         if lookupName in ovrSymbolData:
            sortedOvr = list(ovrSymbolData.items())
            sortedOvr.sort(key=lambda x: x[1])
            candidates = [i for i in range(len(sortedOvr)) if sortedOvr[i][0] == lookupName] #assume 1 candidate for now
            if (len(candidates) == 0):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had no valid lookup candidate."
            elif (len(candidates) > 1):
               processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" had a name collision during lookup."
            else:
               previ = candidates[0] - 1
               if (previ > 0):
                  sprev = sortedOvr[previ]
                  processedSymbols[sn].previousName = sprev[0]
               lastPlusOnei = candidates[0] + irange
               if (lastPlusOnei < len(sortedOvr)):
                  sLastPlusOne = sortedOvr[lastPlusOnei]
                  sourself = sortedOvr[candidates[0]]
                  processedSymbols[sn].nextName = sLastPlusOne[0]
                  gap = sLastPlusOne[1][0] - sourself[1][0]
                  processedSymbols[sn].ourselfCaveSizeBytes = gap
                  if (processedSymbols[sn].ourselfCaveSizeBytes < processedSymbols[sn].ourselfActualSizeBytes):
                     processedSymbols[sn].verboseOnly = False
               else:
                  processedSymbols[sn].notes += f"\n{ccolor.ORANGE}[WARNING]: Item \"{lookupName}\" spans a range larger than its known region, cannot compare to successors."
         elif verbose:
            processedSymbols[sn].verboseOnly = False
            processedSymbols[sn].notes += f" {ccolor.ORANGE}[WARNING]: but didn't find a viable candidate, cannot calculate bytebudget."
      # ===============================================================================================================
      else:
          print(f"{ccolor.RED}This message should be impossible to appear. Tell TheUbMunster if this happens.")
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
   if not verbose:
      print("Reminder: call byteBudget.bat with the `-v` argument for verbose results")
   if "-v" in argv:
      argv.remove("-v")
   if len(argv) != 4:
      print("ERROR: improper number of arguments to byteBudget's main.py")
      exit(-1)
   
   #this file is made with 926 (ntsc-u) in mind

   print("WARNING!!! This tool is not perfect, there are a few circumstances it will not be useful:")
   print("\t* if the functionality of a function being clobbered is implemented elsewhere, budget() will fail")
   print("\t* OVR_Full.c's are assumed to be linked to the same address as the first function in that overlay")
   print("\t* if gcc-/syms926.txt is inaccurate (duplicate entries, incorrect addresses, name collisions etc.), this tool will be inaccurate")
   print("\t* if there are more symbols in the original binary subsequent to another symbol, but not in gcc-/syms.926.txt (clobbered without telling you)")
   print("\t* if it's overbudget when fragmented, it may or may not be overbudget defragged (See ElimBG_Defrag.c + assoc for example)")
   print("\t* if the name of a symbol (filename) does not match the link location (function name/address)")
   print("\t* if a group of symbols is in the same \"memory context\" (i.e., overlay) but aren't in the same namespace (i.e., don't share the same prefix), they won't be compared")

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
      print(f"{ccolor.GREEN}gcc-syms has {len(gccSyms)} entries, and syms has {len(syms)} entries.\n")

   #if not testGccSyms(gccSyms, syms): #ensures that no gcc/syms entry mismatches an address
   #   print("Unable to perform bytebudget calculation.")
   #   exit(-1)

   symbolData = dict() #(name, (address, isUsed))

   #todo: fix the necessary files to remove all name conflicts
   #todo: have the boolean variable in symbolData init to false, then have it set to true when encountered by budget()
   #then enumerate over all symbols that were not interacted with by budget and print a list of every symbol not being linked to
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
         print(f"{ccolor.MAGENTA}Item \"{objectname}\" is not a cbin, cannot byteBudget")
         #budget(objectname, file_size, symbolData, verbose)
   for symbol in processedSymbols.keys():
      si = processedSymbols[symbol]
      if (verbose):
         print(si)
      elif (si.verboseOnly == False):
         print(f"{ccolor.WHITE}{si.ourselfSymbolName.reconstructFileName()} bytebudget: {si.ourselfActualSizeBytes} / {si.ourselfCaveSizeBytes}")
   print(f"\n{ccolor.WHITE}Press any key to exit.")
   input()

main()
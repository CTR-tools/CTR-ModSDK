#===================================================================

# budget_calc.py <filename> [-s] [--silent]
# generates a budget list for symbol lists found in CTR-ModSDK\symbols
# opens up notepad by default, use -s or --silent to suppress

#===================================================================

import os
import sys

#===================================================================

def processLine(line):

    # get rid of comments
    line = line.split('//')[0].strip()

    if line == "":
        return None

    # assume splitting
    if '=' in line:
        data = line.split('=')
    else:
        data = line.split(' ')

    #strip stuff
    data[0] = data[0].strip().replace(';', '').replace('0x', '')
    data[1] = data[1].strip().replace(';', '').replace('0x', '')

    # not enough fields
    if len(data) != 2:
        return None

    # assume order
    if "800" in data[0] and len(data[0]) == 8:
        addr = int("0x" + data[0], 0)
        func = data[1]
    else:
        addr = int("0x" + data[1], 0)
        func = data[0]

    return (func, addr)

#===================================================================

def processFile(filename):
    result = []

    # load all lines
    with open(filename) as input:
        lines = [line.rstrip() for line in input]

    # populate results with key/value tuples
    for line in lines:
        res = processLine(line)
        if res is not None:
            result.append(res)

    # sort the list based on the address
    result.sort(key=lambda a: a[1])

    outname = '{}_budget.txt'.format(filename)

    # dump findings to the file
    with open(outname, "w") as output:
        for i in range(0, len(result)-1):
            final = '{}\t{}\t{}\n'.format(
                hex(result[i][1]),
                result[i + 1][1] - result[i][1],
                result[i][0]
            )

            output.write(final);
    
    return outname

#===================================================================

def main():
    if len(sys.argv) > 1:
        filename = sys.argv[1]
    else:
        print('Usage: budget_calc.py <filename> [-s|--silent]')
        print('This script expects a path to symbols list text file.')
        exit()

    try:
        outname = processFile(filename)

        if not any(x in ['-s', '--silent'] for x in sys.argv):
            os.system('notepad {}'.format(outname))

    except Exception as err:
        print("Unexpected error: {}, {}".format(err, type(err)))
        raise

    print('Done.')

#===================================================================

main()
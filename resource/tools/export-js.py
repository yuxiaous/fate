import sys
import os
import xlrd
# import getopt
# import json
# import string

reload(sys)
sys.setdefaultencoding( "utf-8" )

_show_log = False
_is_dir = True
_input = "../template"
_output = "../GamePublish/config"

_namespace = "configdb"

if(len(sys.argv) == 3):
    _input = sys.argv[1]
    _output = sys.argv[2]

def handleValue(value):
    if(isinstance(value, (int, float))):
        if(value % 1 == 0.0):
            value = int(value)
        return str(value)

    if(isinstance(value, unicode)):
        if(value.find('\n') != -1):
            value = value.replace('\n','\\n')
        return value.strip()

    return value

def genJsObject(row_data, headers, obj_name):
    obj_string = ""

    # find key
    key = handleValue(row_data[0])
    for i in range(len(headers)):
        if(headers[i] == "key"):
            key = handleValue(row_data[i])
            break
    
    if(key != ''):
        # obj header
        keys = key.split('.')
        obj_header = _namespace + "." + obj_name
        for i in range(len(keys)-1):
            key = keys[i]
            obj_header += "['" + key + "']"
            obj_string += "%s = %s || {}\n" % (obj_header, obj_header)

        # obj content
        key = keys[len(keys)-1]
        obj_string += obj_header + "['" + key + "'] = {\n"

        for i in range(len(headers)):
            header = headers[i]
            value = row_data[i]

            if(header == ''):
                continue

            if(value == ''):
                value = 'undefined'

            if(isinstance(header, (int, float))):
                header = '"' + handleValue(header) + '"'

            if(isinstance(value, unicode)):
                value = '"' + handleValue(value) + '"'

            obj_string += "\t" + str(header) + ": " + str(value) + ",\n"

        obj_string += "};\n"

    return obj_string

def genJsString(sheet_data, obj_name):
    out_string = "//Auto gen file\n\n"

    # namespace
    if(_namespace != ''):
        out_string += "var " + _namespace + " = " + _namespace + " || {};\n\n"
        out_string += _namespace + "." + obj_name + " = {};\n\n"

    comment = sheet_data.row_values(0)
    header = sheet_data.row_values(1)

    for i in range(2, sheet_data.nrows):
        row_data = sheet_data.row_values(i)

        obj_string = genJsObject(row_data, header, obj_name)
        if(len(obj_string) > 0):
            out_string += obj_string + "\n"

    return out_string


exportSheetName = u'main'
def exportFile(input_file, output_file, obj_name):
    print input_file, '--->', output_file

    xls_data = xlrd.open_workbook(input_file)

    # check sheet name
    is_main_sheet_exist = False
    sheet_names = xls_data.sheet_names();
    for i in range(len(sheet_names)):
        sheet_name = sheet_names[i]
        if(sheet_name == exportSheetName):
            is_main_sheet_exist = True
    if(is_main_sheet_exist == False):
        print u'Error: No sheet named', exportSheetName
        return

    # check sheet rows number
    sheet_data = xls_data.sheet_by_name(exportSheetName)
    if(sheet_data.nrows < 3):
        print u'Error: Number of rows must >= 3'
        return

    out_string = genJsString(sheet_data, obj_name)

    if(_show_log):
        print out_string

    f = open(output_file, 'w')
    f.write(out_string.encode('utf-8'))
    f.close()

# exportFile("model.xlsx", "model.js")

exportExt = ['.xlsx', '.xls']
def main(input, output):
    if(_is_dir):
        # create dir
        if not os.path.isdir(output):
            os.makedirs(output, 0777)
        
        for root, dirs, files in os.walk(input):
            for filename in files:
                # remove temp file
                if(filename.startswith('~$')):
                    continue

                # need export
                isExport = False
                for ext in exportExt:
                    if(filename.endswith(ext)):
                        isExport = True
                if(isExport == False):
                    continue


                # input_file
                input_file = os.path.join(root, filename)

                # output_file
                se = os.path.splitext(filename)
                obj_name = se[0]
                output_file = obj_name + 'db.js'
                output_file = os.path.join(output, output_file)

                # export
                exportFile(input_file, output_file, obj_name)
    else:
        exportFile(input, output)

main(_input, _output)





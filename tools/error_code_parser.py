import json
import sys
import re

error_name_space = "net_error_code"


def ParseError(data):
    out_string = ''

    code = data[0]
    name = data[1]
    desc = data[2]

    out_string += error_name_space + '.' + name + ' = ' + str(code) + ';\n'
    out_string += error_name_space + '[' + str(code) + '] = {\n'
    out_string += '\tcode: ' + str(code) + ',\n'
    out_string += '\tdesc: "' + desc + '"\n'
    out_string += '};\n'

    return out_string


reload(sys)  
sys.setdefaultencoding('utf-8')

out_js_file = open('protocol/error_code_generated.js', 'w')
out_js_file.write('////////////////// Auto generated, DO NOT modify manually //////////////////\n\n')
out_js_file.write('var ' + error_name_space + ' = {};\n\n')


with open("error_code_define.json") as json_file:
    json_data = json.load(json_file)

    for data in json_data:
        out_string = ParseError(data)
        out_js_file.write(out_string)
        out_js_file.write("\n")
        pass

out_js_file.close()

print '-------------------------- Success ----------------------------'



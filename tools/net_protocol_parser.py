import json
import sys

net_handler_name = "net_protocol_handlers"
cs_handler_prefix = "SEND_"
sc_handler_prefix = "ON_"


def ParseCS(name, code, schemes):
	out_string = ''
	out_string += net_handler_name + '.' + cs_handler_prefix + name + ' = function(obj) {\n'

	# asserts
	for i in range(len(schemes)):
		scheme = schemes[i]
		out_string += '\tcc.assert(obj.{1} != undefined, "{0}.{1} is undefined.");\n'.format(name, scheme[1])


	out_string += '\t_SendFunc(' + str(code) + ', obj);\n'

	out_string += '};\n'
	return out_string

def ParseSC(name, code, schemes):
	out_string = ''
	out_string += '_BindFunc(' + str(code) + ', function(obj) {\n'

	# asserts
	for i in range(len(schemes)):
		scheme = schemes[i]
		out_string += '\tcc.assert(obj.{1} != undefined, "{0}.{1} is undefined.");\n'.format(name, scheme[1])

	out_string += '\t' + net_handler_name + '.' + sc_handler_prefix + name + '(obj);\n'
	out_string += '});\n'
	return out_string

def ParseProtocol(name, json):
	out_string = ''

	# protocol description
	out_string += '// @protocol ' + json['desc'] + '\n'

	# param description
	proto_schemes = json['schemes']
	for i in range(len(proto_schemes)):
		scheme = proto_schemes[i]
		out_string += '// @param {' + scheme[0] + '} ' + scheme[1] + ', ' + scheme[2] + '\n'

	# function
	proto_code = json['code']
	proto_type = json['type']
	out_string +=  '{0}.{1} = {2};\n'.format(net_handler_name, name, proto_code)

	if(proto_type == 'CS'):
		out_string += ParseCS(name, proto_code, proto_schemes)
	elif(proto_type == 'SC'):
		out_string += ParseSC(name, proto_code, proto_schemes)

	return out_string


reload(sys)  
sys.setdefaultencoding('utf-8')

out_js_file = open("protocol/net_protocol_generated.js", 'w')
out_js_file.write("////////////////// Auto generated, DO NOT modify manually //////////////////\n\n")
out_js_file.write('var ' + net_handler_name + ' = {};\n\n')
out_js_file.write('var _SendFunc = net.send.bind(net);\n')
out_js_file.write('var _BindFunc = net.registerCallback.bind(net);\n\n')

with open("net_protocol_define.json") as json_file:
	json_data = json.load(json_file)
	
	for key in json_data:
		out_string = ParseProtocol(key, json_data[key])
		out_js_file.write(out_string)
		out_js_file.write("\n")

out_js_file.close()

print '-------------------------- Success ----------------------------'

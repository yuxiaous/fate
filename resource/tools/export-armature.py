import sys
import os
import zipfile

def unzip(in_file, out_dir):
    # print "in_file: " + in_file
    # print "out_dir: " + out_dir

    basename = os.path.basename(in_file)
    # print "basename: " + basename

    # output_dir
    se = os.path.splitext(basename)
    output_dir = os.path.join(out_dir, se[0])
    # print "output_dir: " + output_dir

    print in_file + " ---> " + output_dir

    # create dir
    if not os.path.isdir(output_dir):
        os.makedirs(output_dir, 0777)

    zfile = zipfile.ZipFile(in_file,'r')
    for filename in zfile.namelist():
        data = zfile.read(filename)
        file = open(os.path.join(output_dir, filename), 'w+b')
        file.write(data)
        file.close()
    pass

def main(input_dir, output_dir):
    for root, dirs, files in os.walk(input_dir):
        for filename in files:
            # print "root: " + root
            # print "filename: " + filename

            # input_file
            in_file = os.path.join(root, filename)
            # print "in_file: " + in_file

            # export
            unzip(in_file, output_dir)
    pass



main("../armatures", "../GamePublish/res/armatures")





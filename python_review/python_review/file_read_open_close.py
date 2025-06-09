"""
open(name,model,encoding)

name = path of file

model = read 'r' read an exiting file;
write 'w' create a new file or rewrite an exiting file;
append 'a' create a new file or append content at the end of the exiting file;

encoidng = "UTF-8"

"""

file = open("sex.txt",'r',encoding="UTF-8")
print(f"the first 10 bytes of the file: {file.read(10)}")
file.seek(0)
print(f"read the whole file: {file.read()}") # return value is string
file.seek(0)

"""
# 将指针移动到指定的字节位置，例如第100个字节
    file.seek(100)
    
file.seek(offset, whence)
offset: 表示相对于 whence 的偏移量（以字节为单位）。
whence: 可选，表示相对于哪种位置进行偏移，有以下三种值：
0（默认）：表示从文件的开头开始计算偏移。
1：表示从文件的当前位置开始计算偏移。
2：表示从文件的末尾开始计算偏移
"""


print(f"read all lines from the file: {file.readlines()}") # return value is a list, each line is an element in the list in order.
file.seek(0)
print(f"read one line of the file: {file.readline()}")


# loop read
for line in file:
    print(f" the line of the file: {line}")

# file close, very important !!!!!!!!!
file.close()

with open("yellow.txt",'w',encoding="UTF-8") as f:
    # "with open() as" can close the file, after the comment in it completed
    f.write("Hello World")
    f.write("\n")
    f.write("come, baby, come, baby")
    f.write("\n")
    f.flush()
    # f.write() will write the text into buffer area
    # f.flush() writes the text in the buffer area into the .txt file
with open("sex.txt",'a',encoding="UTF-8") as f:
    f.write("Hello World\n")
    f.write("I was ok\n")
    f.write("but that that want to say could be\n")
    f.flush()

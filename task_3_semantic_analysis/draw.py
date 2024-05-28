from nltk.tree import *
from nltk.draw.tree import TreeView
from PIL import Image

f = open("output.txt", "r")
data = f.read()
tree2 = Tree.fromstring(data, brackets='{}')
TreeView(tree2)._cframe.print_to_file('output.ps')
Image.open('output.ps').save('output.png')
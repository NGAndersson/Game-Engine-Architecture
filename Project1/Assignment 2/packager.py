import sys, getopt, os
from shutil import move

def main(argv):
	inputfile = ''
	outputfile = ''
	guid = ''
	try:
		opts, args = getopt.getopt(argv, "hi:g:o:",["ifile=", "ofile=", "guid="])
	except getopt.GetoptError:
		print ('packager.py -i <inputfile> -g <guid> -o <outputfile>')
		sys.exit(2)
	for opt, arg in opts:
		if opt == '-h':
			print('test.py -i <inputfile> -g <guid> -o <outputfile>')
			sys.exit()
		elif opt in ("-i", "--ifile"):
			inputfile = arg
		elif opt in ("-o", "--ofile"):
			outputfile = arg
		elif opt in ("-g", "--guid"):
			guid = arg
	print('Input file is', inputfile)
	print('Output file is', outputfile)
	print('Guid is', guid)
	
	try:
		o = open(outputfile, "rb")
	except FileNotFoundError: 	#if file does not exist, create it and put a '0' on the first line (nr of files)
		o = open(outputfile, "wb")
		o.write("0\nHEADER END\n".encode())
		o.close()
		o = open(outputfile, "rb")
	
	header = []
	
	for line in o:
		if b'HEADER END' in line:
			header.append(("HEADER END\n").encode())
			break
		else: 
			header.append(line)
	
	nrOfFiles = int(header[0])
	for i in range(1, nrOfFiles+1): 		#Checking if guid already exists in package
		if header[i].split()[0] == guid:
			print("A file with that guid already exists. Shutting down.")
			exit(2)
	
	if nrOfFiles > 0:
		byteOffset = int(header[nrOfFiles].split()[1]) + int(header[nrOfFiles].split()[2]) +1	#Offset+size of N is the offset of N+1
	else:
		byteOffset = 0 
		
	headerstring = (guid + " " + str(byteOffset) + " " + str(os.path.getsize(inputfile)) + '\n').encode()
	header.insert(nrOfFiles+1, headerstring)
	header[0] = (str(nrOfFiles + 1) + '\n').encode()
	
	t = open("temp", "wb")
	for line in header:
		t.write(line)
	for line in o:
		t.write(line)
	o.close()
	t.write(open(inputfile, "rb").read())
	t.write(b'\n')
	t.close()
	move("temp", outputfile)
	
	#t = open(outputfile, "rb")
	#data = t.read()
	#print(data.decode())
	
	#o = open("testpic.png", "wb")
	#o.write(open(inputfile, "rb").read())
	#o.close()
	
if __name__ == "__main__":
	main(sys.argv[1:])
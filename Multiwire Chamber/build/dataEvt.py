#Creamos el archivo
fCreate = open("dataEvt.txt", "w")
for i in range(0, 101, 1):
	#fCreate.write(str(i)+" 0\n")
	fCreate.write("0\n")

fCreate.close()

#Lo abrimos y lo leemos
fOpen = open("dataEvt.txt", "r")
dataEvt = fOpen.readlines() 

fOpen.close()

#Leemos los datos
fOpenData = open("stuff.txt", "r")

dataCount = fOpenData.read()

fOpenData.close()

rep = [];
for e in range(0, 101, 1):
	rep.append(dataCount.count(str(e)))

for n in range(0, 101, 1):
	#dataEvt[n] = str(n)+" "+str(rep[n]) + '\n'
	dataEvt[n] = str(rep[n]) + '\n'
	
fWrite = open("dataEvt.txt", "w")
fWrite.writelines(dataEvt)

fWrite.close()

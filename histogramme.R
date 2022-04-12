modelname1 = "hist1.txt"
modelname2 = "hist2.txt"
data1 = read.table(modelname1)
data2 = read.table(modelname2)
pdf(file="histogramme.pdf")

attach(data1)
emission = V1
hist(emission,breaks=25,xlab= "Temps d'emission", ylab= "Occurences",col="red",main= "Nombre d'occurences de e1 en fonction du temps d'emission")
abline(v = mean(V1),col = "blue")

attach(data2)
emission = V1
hist(emission,breaks=25,xlab= "Temps d'emission", ylab= "Occurences",col="red",main= "Nombre d'occurences de e2 en fonction du temps d'emission")
abline(v = mean(V1),col = "blue")
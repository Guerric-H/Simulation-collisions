modelname1 = "hist1.txt"
modelname2 = "hist2.txt"
data1 = read.table(modelname1)
data2 = read.table(modelname2)
pdf(file="histogramme.pdf")

attach(data1)
emission = V1
hist(emission,breaks=25,xlab= "Temps d'émission", ylab= "Occurences",col="red",main= "Nombre d'occurences de e1 \nen fonction du temps d'émission")
abline(v = mean(V1),col = "blue")


legend(
    "topright",
     legend = paste("moyenne de temps d'emission = ", formatC(mean(V1), digits = 3) ) ,
     col = "blue",
     cex = 1 )

attach(data2)
emission = V1
hist(emission,breaks=25,xlab= "Temps d'émission", ylab= "Occurences",col="red",main= "Nombre d'occurences de e2 \nen fonction du temps d'émission")
abline(v = mean(V1),col = "blue")

legend("topright",
     legend = paste("moyenne de temps d'emission = ", formatC(mean(V1), digits = 3) ) ,
     col = "blue",
     cex = 1 )
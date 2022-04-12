modelname = "standard.txt"
data = read.table(modelname)
attach(data)
pdf(file="standard.pdf")

temps = V1
e1 = V2
e2 = V3
e3 = V4
e4 = V5
e5 = V6
e6 = V7
e7 = V8

plot(temps,e1,type = "l",xlab = "Temps", ylab = "Probabilité de collision",main = "Probabilité de collision de chaque état à l'instant t", col = "red",ylim = c(0,1),xlim = c(0,11500))
lines(temps,e2,type = "l",col = "blue")
lines(temps,e3,type = "l",col = "green")
lines(temps,e4,type = "l",col = "yellow")
lines(temps,e5,type = "l",col = "purple")
lines(temps,e6,type = "l",col = "black")
lines(temps,e7,type = "l",col = "orange")


text(x = 10000, 
     y = 1.0,
     labels = "e1 = _____",
     col = "red",
     cex = 1 )

text(x = 10000, 
     y = 0.95,
     labels = "e2 = _____",
     col = "blue",
     cex = 1 )

text(x = 10000, 
     y = 0.9,
     labels = "e3 = _____",
     col = "green",
     cex = 1 )

text(x = 10000, 
     y = 0.85,
     labels = "e4 = _____",
     col = "yellow",
     cex = 1 )

text(x = 10000, 
     y = 0.80,

     labels = "e5 = _____",
     col = "purple",
     cex = 1 )

text(x = 10000, 
     y = 0.75,
     labels = "e6 = _____",
     col = "black",
     cex = 1 )

text(x = 10000, 
     y = 0.70,
     labels = "e2 = _____",
     col = "orange",
     cex = 1 )

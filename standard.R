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

plot(temps,e1, type = "l", xlab = "Temps", ylab = "Proba de collisions",main = "Probabilité de collision de chaque état à l'instant t", col = "red",xlim = c(0,11500), ylim = c(0,1))
lines(temps,e2,type = "l",col = "blue")
lines(temps,e3,type = "l",col = "green")
lines(temps,e4,type = "l",col = "yellow")
lines(temps,e5,type = "l",col = "purple")
lines(temps,e6,type = "l",col = "black")
lines(temps,e7,type = "l",col = "orange")

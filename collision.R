modelname = "collisions.txt"
data = read.table(modelname)
attach(data)
pdf(file="collision.pdf")

proba = V1
moy_etat = V2

plot(proba, 
     type = "p",
    pch = 21,
    cex = 0.3,
    xlab = "K (nombre de capteurs actifs)", 
    ylab = "Probabilité de collision",
    main = "Probabilité de collision moyenne pour K capteurs", 
    col = "red", 
    bg = "red",
    ylim = c(0,1))
abline(h=0.7,col="blue")
abline(v=60,col="grey",lty = 5, lwd = 1)
abline(v=70,col="grey",lty = 5, lwd = 1)
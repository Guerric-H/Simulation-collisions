modelname = "collisions.txt"
data = read.table(modelname)
attach(data)
pdf(file="collision.pdf")

proba = V1

plot(proba, 
    type = "l", 
    xlab = "K (nombre de capteurs actifs)", 
    ylab = "Proba de collisions",
    main = "Probabilité de collision moyenne pour K capteurs", 
    col = "red", 
    xlim = c(0,100), 
    ylim = c(0,1))
abline(h=0.7,col="blue")
locator()
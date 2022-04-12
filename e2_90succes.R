modelname = "collisions.txt"
data = read.table(modelname)
attach(data)
pdf(file="e2_90succes.pdf")

moy_etat = V2

plot(moy_etat, 
    type = "l",
    lty = 3, 
    lwd = 2,
    xlab = "K (nombre de capteurs actifs)", 
    ylab = "Probabilité de succès de e1 et e2 sur le total de transmission",
    main = "Probabilité de succès de transmission en au plus 2 tentatives \n en fonction du nombre de capteurs", 
    col = "red", 
    ylim = c(0,1))
abline(h=0.9,col="blue")
abline(v= 20,lty = 5, lwd = 1, col="grey")
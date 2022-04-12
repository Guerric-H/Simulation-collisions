modelname = "confiance.txt"
data = read.table(modelname)
attach(data)
pdf(file="confiance.pdf")

proba = V1
IC = t.test(proba)

plot(proba,type = "h",xlab = "Numéro d'exécution",ylab = "Proba collision e2", col= "red")
abline(h=IC$conf.int[1],col="blue")
abline(h=IC$conf.int[2],col="blue")
# Created By Cole Keffel, Cole Stewert, Kevin Scutaru


userName = input("Please enter your name: ")
numShare = int(input("Please enter the number of shares you would like to purchase: "))
pricePerShare = float(input("How much are paying per share: "))
salePrice = float(input("How much are you selling each share: "))
commissionPrice = float(input("What percentage of commision is charged by the broker?: "))

totalPricePaid = numShare * pricePerShare												#Total Price of stock
purchaseCommission = totalPricePaid * (commissionPrice / 100)								#Amount of commission paid 
soldPrice = numShare * salePrice														#Total price when sold 
soldCommission = soldPrice * (commissionPrice / 100)										#Total price of commission when selling
equity = soldPrice - totalPricePaid - purchaseCommission - soldCommission						# equity gained or lost when selling

print("\n\n-----------------------------------------")
print(userName)
print("Total Price Paid:", " ${:.2f}".format(totalPricePaid), sep='')
print("Total Commission Paid when purchasing:", " ${:.2f}".format(purchaseCommission), sep='')
print("Total Price Sold:", " ${:.2f}".format(soldPrice), sep='')

if equity < 0:
        equity *= -1

print("Total Commission Paid when sold:", " ${:.2f}".format(soldCommission), sep='')

if soldPrice > totalPricePaid:														#Determine whether you made or lost equity 
	print(userName, " made", " ${:.2f}".format(equity), sep='') 
elif soldPrice < totalPricePaid:
	print(userName, " lost", " ${:.2f}".format(equity), sep='')

#Cole Keffel, Kevin Andor, Cole Stewart
#Assignment 7

def displayGreater(list, n): #Checks to see if a sale is greater than the specified 'n'. If so, it prints the value for that day.
    for num in list:
        if n < num:
            print(num, 'is greater than ', n)

dayWeek = ['Sunday', 'Monday', 'Tuesday', 'Wednesday', 'Thursday', 'Friday', 'Saturday']
daySalesList = []
weekTotalSales = 0

try: #Asks for a sale in a particular day of the week and calculates the total sales
    for day in dayWeek:
        statement = print('Daily sales for: ' , day)
        dailySales = float(input())
        daySalesList.append(dailySales)
        weekTotalSales += dailySales
except Exception as err:
    print(err)

print('Weekly sales: ', weekTotalSales, '\n')
print('--------------------')

displayGreater(daySalesList, 30)

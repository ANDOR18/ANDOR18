USE AdventureWorksLT2012
GO




Select FirstName, LastName, SalesPerson
From SalesLT.Customer
GO

Select FirstName, LastName, SalesPerson
From SalesLT.Customer
Where LastName like 'l%'
GO

Select FirstName, LastName, CompanyName
From SalesLT.Customer
GO

Select Name, ProductCategoryID
From SalesLT.Product
Where ProductCategoryID between 5 and 10
GO

Select Name
From SalesLT.ProductCategory
Order by Name DESC
GO

Select Color, Name
From SalesLT.Product
Where Color like 'Red'
GO
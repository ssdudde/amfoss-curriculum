#1.Variables and Data Types
##Assignment
>For making a shopping cart I would first use String,int data types mainly.I might use array for some rare cases like including multiple items under one bigger group. Then would use boolean to know wheter the item is bought or no.
###Challenge
>Here when age=1; and Age=2; the java script treats both the variables as two different variable and returns false because both are different variables and 1!=2
####Gotchas
>1.Another coommon type of gotcha is "==" vs "===" in cases like 12 == '12' it return true as javascript coerces them to same data type and compares the value but '===' strictly compares both the value and data type so in 12 === '12' it returns false
>2.If we add a number to string then we end with string ,example 1+'1' then output would be like '11'.
>3.NaN(Not a Number) is not equal to itself and if we use isNaN("") or isNaN([]) then javascript coerces them into number data type and then return true.
>4.When new array is created it is created with empty items so we need to manually intialize it.
>5.0.1+0.2 !==0.3 as java using floating-point arithemetic so leads to precision errors. 

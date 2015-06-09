#!/bin/bash

checkForErrors()
  {  
  if [ $? != 0 ]
  then
    echo "An error has occured during this operation, please fix this problem before testing again."
    exit 1
  fi
  }

compareFiles()
  {
  if [ $(diff $1 $2 | wc -l) -ne 0 ]
  then
    echo "  The expected output of this operation does not match output of your application, below is a list of the differences between your applications output and the expected output."
    diff $1 $2
    exit 1
  fi
  checkForErrors
  }

compareInvoice()
  {
  echo "    Compare these two outputs (refer to diff manual):"
  diff $1 $2
  echo -n "    Do these two match in all but date (format must be the same, values can be different) [y/n]: "
  read desc
  if [ $desc != "y" ]
  then
    echo "    Please correct your invoice output before testing again."
    exit 1
  fi
  }

testPhase()
  {
  echo "Testing Application Phase $1..."
  
  echo "  Running Application..."
  assign3 < "testPackage/inst$1.txt" > _toutput
  checkForErrors
  
  echo "  Comparing GUI outputs..."
  compareFiles _toutput "testPackage/out$1.txt"
  rm _toutput


  echo "  Comparing inventory.txt outputs..."
  compareFiles inventory.txt "testPackage/iexp$1.txt"

  echo "  Comparing invoice.txt outputs..."
  compareInvoice invoice.txt "testPackage/nexp$1.txt"
  ##compareFiles invoice.txt "testPackage/nexp$1.txt"

  echo "  Comparing warnings.txt outputs..."
  compareFiles warnings.txt "testPackage/wexp$1.txt"

  echo "Testing Phase $1 Complete!"
  echo ""
  }

echo "Welcome to the IPC144 A3 Tester"
echo ""

echo "Resetting Files..."
echo "  Resetting inventory.txt..."
echo "11678532|Kosher beef|0|11.99
18394621|Large eggs|21|4.99
83664729|Smucker's Double Fruit jam|9|3.49
98563042|Rougemont Juice|1|2.50
64029473|Whiskas Temptations cat treats|0|3.00
93658572|Bick's Baby Dills|0|2.99
73193482|Ms. Vicki's Sea Salt and Vinegar|5|1.49
73193421|Ms. Vicki's Sea Salt and Vinegar Family Pack|12|2.99
72537183|Ms. Vicki's Barbecue|24|1.49
35120176|No Name Sausage|3|4.99
82391432|1L Nielsen Milk Carton|9|1.49
27183946|4L Nielsen Milk Bag|16|4.49
18273462|Bounty Paper Towel 12 rolls|11|8.88
12639271|Chapman's Super Sandwhich 12's|17|2.99
18279472|Whole Chicken|19|1.88
63524921|Lay's Potato Chips|27|2.88
18726392|Blueberries Pint Or Raspberries|6|1.88
73928514|Snuggle Fabric Softener|8|6.88
34267182|Larsen Wieners|2|1.88
15538920|Schneiders Lunchmates|16|1.88
18892634|Boneless Blade Steak|20|4.88
15244291|Chicken Drumstick or Thigh|12|2.88
16299302|Boneless Pork Loin Combo Chops|1|4.88
17728466|Schneiders Oktoberfest Sausage|9|1.88
88172939|Raw Schrimp|23|5.88
11293791|Sunrise Shave Black Forest Ham|11|1.88
18928392|Romain Lettuce|6|0.88
17266399|Whole White Mushrooms|43|2.88
88192663|Field Cucumbers|21|0.88
19829302|Cauliflower|12|1.88
87499202|PC Cheesecake|8|5.88
19027732|Minute Maid Juice 1.75L|15|1.88
99177290|Sunny D Citrus Punch|17|1.88
99028374|Brunswick Sardines 100g|23|0.88
43928930|Red Rose Orange Pekoe Tea|21|5.88
72354829|Bick's Pickles|13|2.88
63294792|Delissio Rising Crust|26|7.88
00188304|Pantene 375mL|15|3.88
99102774|Huggies Giant Pack Diapers|27|27.88
45394851|Astro Yogurt|18|1.88" > inventory.txt
checkForErrors

echo "  Resetting warnings.txt..."
rm warnings.txt 2> _garbageLand 
touch warnings.txt
checkForErrors

echo "  Resetting invoice.txt..."
rm invoice.txt 2> _garbageLand
touch invoice.txt
checkForErrors

rm _garbageLand

echo "Resetting files successful..."
echo ""

echo "Compiling program..."
gcc assign3.c -o assign3
checkForErrors

echo "Compilation successful..."
echo ""

testPhase 1
testPhase 2
testPhase 3

perc="80%"

if [ $# -gt 0 ]
then
  if [ $1 == "withValidation" ]
  then
    testPhase 4
    perc="100%"
  fi
fi

echo "Congraduations, your application passes the test! ($perc)"
echo "Be sure that your code follows the style guidelines and is well commented!"
echo "Please submit your file to BlackBoard!"



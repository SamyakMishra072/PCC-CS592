read -p "Enter a year: " y
if [ $y -le 0 ]; then
        echo "INVALID INPUT"
elif [ $((y%400)) -eq 0 ]; then
        echo "LEAP YEAR"
elif [ $((y%100)) -eq 0 ]; then
        echo "NOT A LEAP YEAR"
elif [ $((y%4)) -eq 0 ]; then
        echo "LEAP YEAR"
else
        echo "NOT A LEAP YEAR"
fi

~

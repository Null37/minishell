while [ 1 ]
do
   echo "update";date +%T > che1.txt
git add * && git commit -F che1.txt && git push
rm che1.txt
   sleep 10
done
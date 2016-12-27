
echo "kill old process ... </br>"
killall eurorun
#echo "removing old data <br>"
#rm -rf data/*
echo "update database </br>"
sh get_csv_file.sh
echo "Running Program </br>"
nice -n 10 cpulimit -l 60 ./eurorun

echo "Test mail from postfix" | mail -s "EuroMillions sent more info" qivolt@qivolt.com
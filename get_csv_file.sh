#http://www.lotoideas.com/euromillones-resultados-historicos-de-todos-los-sorteos/
wget wget --no-check-certificate --output-document=test.csv  'https://docs.google.com/spreadsheet/pub?key=0AhqMeY8ZOrNKdEFUQ3VaTHVpU29UZ3l4emFQaVZub3c&output=csv' 
#
tac test.csv > test1.csv
sed '$ d' test1.csv > test2.csv
sed -i '1s/.*/data,c1,c2,c3,c4,c5,s,e1,e2/' test2.csv
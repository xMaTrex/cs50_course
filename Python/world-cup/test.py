import csv
import sys
import random

# Ensure correct usage
if len(sys.argv) != 2:
    sys.exit("Usage: python tournament.py FILENAME")

teams = []
# TODO: Read teams into memory from file
f = open(sys.argv[1]) # open file -> 2018m.csv or 2019w.csv
reader = csv.DictReader(f) # each row of file -> dict
# like: {"team": "Uruguay", "rating": 976}
for row in reader:
    dict = {"team": row["team"], "rating": int(row["rating"])}
    teams.append(dict)
    #print(dict)
print(teams)
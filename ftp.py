
import argparse
import json


parser = argparse.ArgumentParser(description="this Tool can do fuzzing for password \nand it can download all files or sepcifec file")
parser.add_argument('-o', '--option', help="FTP option [FUZZ (to do brut force on password), DIR (todoawnload file)]")
parser.add_argument('-u', '--user', help="FTP user name", required=True)
parser.add_argument('-p', '--password', help="FTP password", required=False)
parser.add_argument('-l', '--list', help="FTP List password", required=False)
parser.add_argument('-f', '--file', help="Name file", required=False)
parser.add_argument('-IN', '--ip', help="FTP ip and port exampl 10.10.10.10:21", required=True)

args = parser.parse_args()

def openFile(data) :
    with open(".rq.json", "w") as file:
        json.dump(data, file)

if args.option == "FUZZ" :
    FUZZ = dict(option = "FUZZ", user = args.user, list = args.list)
    list = args.ip.split(":")
    FUZZ.update(dict(ip = list[0], port = list[1]))
    print(FUZZ)
    openFile(FUZZ)
elif args.option == "DIR" :
    FUZZ = dict(option = "DIR", user = args.user, password = args.password, file = args.file)
    list = args.ip.split(":")
    FUZZ.update(dict(ip = list[0], port = list[1]))
    print(FUZZ)
    openFile(FUZZ)



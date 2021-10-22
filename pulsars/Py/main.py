import pandas as pd
import json


def main():
    data = pd.read_csv('new_psrcat.txt', sep=" ", header=None, dtype=str)
    dict = {}
    temp = {}
    keys = []
    for i in range(len(data)):
        if data[0][i] != "@" and data[0][i] not in keys:
            keys.append(data[0][i])
    print(keys)

    for i in keys:
        temp[i] = "Nan"
    for i in range(len(data)):
        if data[0][i] != "@":
            temp[data[0][i]] = data[1][i]
        else:
            name = temp["PSRJ"]
            dict[name] = {}
            for j in temp:
                dict[name][j] = temp[j]
            temp.clear()
    file = open("psrcat.json", "w")
    json.dump(dict, file)
    file.close()
    print(dict["J2339-0533"])


if __name__ == '__main__':
    main()

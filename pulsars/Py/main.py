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
    # print(keys)

    for i in keys:
        temp[i] = "Nan"
    # print(temp["P0"])
    for i in range(len(data)):
        if data[0][i] != "@":
            temp[data[0][i]] = data[1][i]
        else:
            name = temp["PSRJ"]
            dict[name] = {}
            for j in temp:
                dict[name][j] = temp[j]
            temp.clear()
            for j in keys:
                temp[j] = "Nan"
    for i in dict:
        print(len(dict[i]))

    file = open("psrcat.json", "w")
    json.dump(dict, file)
    file.close()
    # print("P0" in dict["J0007+7303"])


if __name__ == '__main__':
    main()

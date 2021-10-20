import openpyxl
import numpy as np
import matplotlib.pyplot as plt


# месторасположение эксель таблицы
excel_files = ['/Users/dmitr/Desktop/MIPT/3 семак/Лабы/test.xlsx']

# название листа в эксель таблице
Sheet = 'Sheet1'


class Figure(object):
    def __init__(self, X, Y, s, n, q):
        # МНК для y = kx + b
        def equation1(x, y):
            xy = []
            sqr_x = []
            sqr_y = []
            for j in range(len(x)):
                xy.append(x[j] * y[j])
                sqr_x.append(x[j] ** 2)
                sqr_y.append(y[j] ** 2)
            k1 = (np.mean(xy) - np.mean(x) * np.mean(y)) / (np.mean(sqr_x) - np.mean(x) ** 2)
            b1 = np.mean(y) - k1 * np.mean(x)
            sk1 = round(np.sqrt(
                ((np.mean(sqr_y) - np.mean(y) ** 2) / (np.mean(sqr_x) - np.mean(x) ** 2) - k1 ** 2) / (len(x) - 2)), 4)
            sb = round(sk1 * np.std(x), 4)
            return round(k1, 3), round(b1, 3), sk1, sb

        # МНК для y = kx
        def equation2(x, y):
            xy = []
            sqr_x = []
            sqr_y = []
            for j in range(len(x)):
                xy.append(x[j] * y[j])
                sqr_x.append(x[j] ** 2)
                sqr_y.append(y[j] ** 2)
            k1 = np.mean(xy) / np.mean(sqr_x)
            sk1 = np.sqrt((np.mean(sqr_y) / np.mean(sqr_x) - k1 ** 2) / (len(x) - 1))
            return round(k1, 3), round(sk1, 3)

        self.values_Y = []
        self.values_X = []
        self.index = q
        self.constant = 0
        self.sig_constant = 0

        # считываем данные
        for file in excel_files:
            workbook = openpyxl.load_workbook(file)
            worksheet = workbook[Sheet]
            for i in range(s, n + s):
                cell_value2 = worksheet[X + str(i)].value
                cell_value1 = worksheet[Y + str(i)].value
                self.values_X.append(cell_value2)
                self.values_Y.append(cell_value1)

        # обработка данных
        if q == 1:
            self.tangent, self.constant, self.sig_tangent, self.sig_constant = equation1(self.values_X, self.values_Y)
            k = self.tangent
            b = self.constant
            s_k = self.sig_tangent
            s_b = self.sig_constant
            p, v = np.polyfit(self.values_X, self.values_Y, deg=1, cov=True)
            p_f = np.poly1d(p)
            self.polyfit = p_f
            print('y =', k, 'x +', b)
            print('sigma k = ', s_k)
            print('sigma b = ', s_b)
            print('polyfit y = ', p_f)

        elif q == 2:
            self.tangent, self.sig_tangent = equation2(self.values_X, self.values_Y)
            k = self.tangent
            s_k = self.sig_tangent
            print('y =', k, 'x')
            print('sigma_k = ', s_k)

    # строим графики
    def graph(self, x, y, lab, c):
        q = self.index
        plt.ylabel(y)
        plt.xlabel(x)
        # погрешности
        # plt.errorbar(self.values_X, self.values_Y, 0.1, 0.1, 'none')
        plt.scatter(self.values_X, self.values_Y, color=c, s=15)
        if q == 1:
            plt.plot(self.values_X, self.polyfit(self.values_X), label=lab)  # color =
        elif q == 2:
            new_y = []
            for i in self.values_X:
                new_y.append(i * self.tangent)
            plt.plot(self.values_X, new_y, label=lab)  # color =
        plt.legend(loc='best')  # bbox_to_anchor=(0, 1.25)


def main():
    colors = ['tab:blue', 'tab:orange', 'tab:green',
              'tab:red', 'tab:purple', 'tab:brown', 'tab:pink',
              'tab:gray', 'tab:olive', 'tab:cyan']  # цвета
    x = ['A']  # столбцы, где хранятся аргументы функции
    y = ['B', 'C', 'D']  # столбцы, где хранятся значения функции
    x_label = ['Test x']  # обозначения аргументов функции
    y_label = ['Test y']  # обозначения значения функции
    label = ['Test label']  # обозначения для каждого построенного графика
    tit = ['Test title']  # общее название графиков
    """ "1" если y = kx + b, "2" если y = kx"""
    ind = [2]  # используемый метод в соответствующем графике
    start = [1]  # номер начальной ячейки
    data = [9]  # количество точек в соответствующем графике
    numb = 3  # количество графиков

    for i in range(numb):
        fig = Figure(x[0], y[i], start[0], data[0], ind[0])
        fig.graph(x_label[0], y_label[0], label[0], colors[i])
        plt.title(tit[0])
        """
        Если нужно несколько линий в одном графике убери табуляцию
        со следующих двух строк, иначе каждая линия будет построена 
        отдельно.
        """
        plt.grid()
        # сохранение картинок с графиками
        # plt.savefig('Test.png', dpi=300)
        plt.show()


if __name__ == "__main__":
    main()

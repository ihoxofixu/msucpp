import geometry
import autotest


def get_data(filename):
    error = 0
    try:
        fin = open(filename, "r")
        line_cnt = 0
        data1 = []
        data2 = []
        flag = 0
        for line in fin.readlines():
            line_cnt += 1
            if len(line) == 1:
                if line_cnt < 3:
                    raise Exception("Sorry. The amount of dots in a figure must be 3 or more, please try again")
                flag = 1
                linecnt = 0
            else:
                try:
                    x, y = map(float, line.split())
                    if flag:
                        data2.append(geometry.Dot(x, y))
                    else:
                        data1.append(geometry.Dot(x, y))
                except ValueError:
                    fin.close()
                    error += 1
                if error:
                    raise Exception("Sorry. Wrong format of input data. Each line must contain two float values.")
        fin.close()
    except FileNotFoundError:
        error += 1
    if error:
        raise FileNotFoundError("Sorry. No such file, please try again.")
    return data1, data2


autotest.Autotest()
filename = input("filename: ")
dots1, dots2 = get_data(filename)
ans = geometry.min_distance_between_figures(dots1, dots2)
print("The answer is:", ans)

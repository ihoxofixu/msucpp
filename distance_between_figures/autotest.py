import geometry


def test1():
    ans = geometry.det(1, 2, 3, 4)
    if ans == -2:
        print("TEST  1: CORRECT")
    else:
        print("TEST  1: WRONG")


def test2():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(3, 4)
    ans = geometry.distance_between_dots(a, b)
    if ans == 5:
        print("TEST  2: CORRECT")
    else:
        print("TEST  2: WRONG")


def test3():
    a = geometry.Dot(1, 1)
    e1 = geometry.Dot(0, 0)
    e2 = geometry.Dot(0, 2)
    ans = geometry.distance_between_dot_and_line_segment(a, e1, e2)
    if ans == 1:
        print("TEST  3: CORRECT")
    else:
        print("TEST  3: WRONG")


def test4():
    a = geometry.Dot(1, 1)
    e1 = geometry.Dot(0, 0)
    e2 = geometry.Dot(0, 1)
    ans = geometry.distance_between_dot_and_line_segment(a, e1, e2)
    if ans == 1:
        print("TEST  4: CORRECT")
    else:
        print("TEST  4: WRONG")


def test5():
    a = geometry.Dot(0, 0)
    e1 = geometry.Dot(3, 4)
    e2 = geometry.Dot(10, 10)
    ans = geometry.distance_between_dot_and_line_segment(a, e1, e2)
    if ans == 5:
        print("TEST  5: CORRECT")
    else:
        print("TEST  5: WRONG")


def test6():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(0, 1)
    c = geometry.Dot(0, 0)
    d = geometry.Dot(0, 2)
    ans = geometry.distance_between_line_segments(a, b, c, d)
    if ans == 0:
        print("TEST  6: CORRECT")
    else:
        print("TEST  6: WRONG")


def test7():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(0, 1)
    c = geometry.Dot(1, 0)
    d = geometry.Dot(1, 1)
    ans = geometry.distance_between_line_segments(a, b, c, d)
    if ans == 1:
        print("TEST  7: CORRECT")
    else:
        print("TEST  7: WRONG")


def test8():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(0, -1)
    c = geometry.Dot(3, 4)
    d = geometry.Dot(10, 10)
    ans = geometry.distance_between_line_segments(a, b, c, d)
    if ans == 5:
        print("TEST  8: CORRECT")
    else:
        print("TEST  8: WRONG")


def test9():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(1, 1)
    c = geometry.Dot(0, 1)
    d = geometry.Dot(1, 0)
    ans = geometry.distance_between_line_segments(a, b, c, d)
    if ans == 0:
        print("TEST  9: CORRECT")
    else:
        print("TEST  9: WRONG")


def test10():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(1, 0)
    c = geometry.Dot(1, 1)
    d = geometry.Dot(0, 1)
    ans = geometry.distance_between_line_segments(a, b, c, d)
    if ans == 1:
        print("TEST 10: CORRECT")
    else:
        print("TEST 10: WRONG")


def test11():
    a = geometry.Dot(0, 0)
    b = geometry.Dot(0, 1)
    c = geometry.Dot(1, 0)
    d = geometry.Dot(1, 1)
    e = geometry.Dot(1, 2)
    f = geometry.Dot(2, 1)
    ans = geometry.min_distance_between_figures([a, b, c], [d, e, f])
    if abs(ans - 0.707) < geometry.accuracy:
        print("TEST 11: CORRECT")
    else:
        print("TEST 11: WRONG")


def Autotest():
    test1()
    test2()
    test3()
    test4()
    test5()
    test6()
    test7()
    test8()
    test9()
    test10()
    test11()

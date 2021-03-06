import matplotlib.pyplot as plt
import numpy as np
# paso
h = 0.01

# número de pasos
N = 1000

# t
#t = np.array([i * h for i in range(N)])
t = [i * h for i in range(N)]

# número máximo de argumentos para las funciones, y funciones
m = 2

# inicialización del diccionario de argumentos
keys_arg = ["w_{}".format(i) for i in range(1, m + 1)]
d_arg = {}



# definir todas las funciones!!!
# def f_i(t_j = t_j, **kwargs):

# def f_1(t_j, **kwargs):
#     return -4 * kwargs["w_1"] + 3 * kwargs["w_2"] + 6
#
# def f_2(t_j , **kwargs):
#     return -2.4 * kwargs["w_1"] + 1.6 * kwargs["w_2"] +3.6

mu = 1

def f_1(t_j, **kwargs):
    return -kwargs["w_2"] + kwargs["w_1"]* (mu - kwargs["w_1"]**2 - kwargs["w_2"]**2)
def f_2(t_j, **kwargs):
    return kwargs["w_1"] + kwargs["w_2"]* (mu - kwargs["w_1"]**2 - kwargs["w_2"]**2)


# tupla de funciones
t_functions = (f_1, f_2) #f_3,...., f_m

#w_0 = [0,0]
w_0 = [7.,8.]
#w = np.zeros((N, 2))
#w[0] = w_0
w = [w_0]

def iteration_RK(t_functions, N, h, w_0, keys_arg):
    t = [i * h for i in range(N)]
    d_arg = {}
    w = [w_0]

    for j in range(N-1):
        k_1 = []
        k_2 = []
        k_3 = []
        k_4 = []

        # k_1
        l = 0
        for k in keys_arg:
            d_arg[k] = w[j][l]
            l += 1
        for i in range(m):
            k_1.append(h * t_functions[i](t[j], **d_arg))

        # k_2
        l = 0
        for k in keys_arg:
            d_arg[k] = w[j][l] + k_1[l] / 2
            l += 1
        for i in range(m):
            k_2.append(h*t_functions[i](t[j] + h/2, **d_arg))

        # k_3
        l = 0
        for k in keys_arg:
            d_arg[k] = w[j][l] +k_2[l] / 2
            l += 1
        for i in range(m):
            k_3.append(h*t_functions[i](t[j] + h/2, **d_arg))

        # k_4
        l = 0
        for k in keys_arg:
            d_arg[k] = w[j][l] +k_3[l]
            l += 1
        for i in range(m):
            k_4.append(h*t_functions[i](t[j] + h, **d_arg))


        w_i = []
        for i in range(m):
            w_i.append(w[j][i] + (k_1[i] + 2 * k_2[i] + 2 * k_3[i] + k_4[i]) / 6)

        #print(j)
        # print(k_1)
        # print(k_2)
        # print(k_3)
        # print(k_4)
        #print(w_i)
        w.append(w_i)

    return w





w = iteration_RK(t_functions, N, h, w_0, keys_arg)
plt.plot([z[0] for z in w],[z[1] for z in w])
# plt.plot(t, [z[0] for z in w])
# plt.plot(t, [z[1] for z in w])
# plt.xlabel("tiempo")
# plt.ylabel("W")
plt.show()

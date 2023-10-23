import matplotlib.pyplot as plt
import matplotlib.animation as animation
import math
import time
import os

# Variável que armazena o ID do CAR_A
CAR_A = 82  # Substitua pelo ID desejado

# Variável que armazena o ID do CAR_B
CAR_B = 118  # Substitua pelo ID desejado

# Função para ler as coordenadas do arquivo
def ler_coordenadas():
    x = []
    y = []
    legendas = []
    velocidades = {}
    angulos = {}

    if os.path.getsize("coordinates.txt") == 0:  # Verifica se o arquivo está vazio
        return x, y, legendas, velocidades, angulos

    with open("coordinates.txt", 'r') as arquivo:
        for linha in arquivo:
            linha = linha.strip()
            if linha:
                coordenadas = linha.split()
                if len(coordenadas) == 5:
                    x.append(float(coordenadas[0]))
                    y.append(float(coordenadas[1]))
                    id_legenda = int(coordenadas[4])
                    legendas.append(id_legenda)
                    velocidades[id_legenda] = float(coordenadas[2])
                    angulos[id_legenda] = float(coordenadas[3])
    return x, y, legendas, velocidades, angulos

# Função para calcular a velocidade relativa entre CAR_A e CAR_B
def calcular_velocidade_relativa(velocidades, CAR_A, CAR_B):
    if CAR_A in velocidades and CAR_B in velocidades:
        return abs(velocidades[CAR_A] - velocidades[CAR_B])
    return None

# Função de atualização do gráfico
def atualizar_grafico(i):
    plt.clf()  # Limpa o gráfico anterior
    x, y, legendas, velocidades, angulos = ler_coordenadas()

    if not x:  # Verifica se a lista de coordenadas está vazia
        plt.xlabel('X Coordinate')
        plt.ylabel('Y Coordinate')
        plt.title('Neighboring cars (Waiting for data)')
        return

    posicao_x = x[0]
    posicao_y = y[0]
    raio = 200.0

    verde_x = []
    verde_y = []
    verde_legendas = []
    azul_x = []
    azul_y = []
    azul_legendas = []
    vermelho_x = []
    vermelho_y = []
    vermelho_legendas = []

    for j in range(1, len(x)):
        distancia = math.sqrt((x[j] - posicao_x) ** 2 + (y[j] - posicao_y) ** 2)
        if distancia <= raio:
            azul_x.append(x[j])
            azul_y.append(y[j])
            azul_legendas.append(legendas[j])
        else:
            vermelho_x.append(x[j])
            vermelho_y.append(y[j])
            vermelho_legendas.append(legendas[j])

    # Configura a cor de fundo da tela
    fig.patch.set_facecolor('mediumseagreen')

    # Cria uma linha conectando todos os pontos
    plt.plot(x, y, color='white', marker='.', markersize=10, label='Path')

    # Cria o gráfico de dispersão para os pontos verdes, azuis e vermelhos, com suas respectivas legendas
    plt.scatter(posicao_x,  posicao_y,  label=f'My position',                 color='green', marker='d')
    plt.scatter(azul_x,     azul_y,     label='Close to (-'+str(raio)+'m)',   color='blue', marker='o')
    plt.scatter(vermelho_x, vermelho_y, label='Far (+'+str(raio)+'m)',        color='red', marker='x')

    for j in range(len(azul_x)):
        plt.annotate(f'({azul_legendas[j]})', (azul_x[j], azul_y[j]), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='blue')

    for j in range(len(vermelho_x)):
        plt.annotate(f'({vermelho_legendas[j]})', (vermelho_x[j], vermelho_y[j]), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='red')

    # Encontra as coordenadas de CAR_A
    if CAR_A in legendas:
        index_a = legendas.index(CAR_A)
        car_a_x = x[index_a]
        car_a_y = y[index_a]
        plt.annotate(f'({CAR_A})', (car_a_x, car_a_y), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='green')

    # Encontra as coordenadas de CAR_B
    if CAR_B in legendas:
        index_b = legendas.index(CAR_B)
        car_b_x = x[index_b]
        car_b_y = y[index_b]
        plt.annotate(f'({CAR_B})', (car_b_x, car_b_y), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='green')

    # Traça uma linha conectando CAR_A e CAR_B com a legenda da velocidade relativa
    if CAR_A in legendas and CAR_B in legendas:
        plt.plot([car_a_x, car_b_x], [car_a_y, car_b_y], color='darkred', linewidth=2)
        velocidade_relativa = calcular_velocidade_relativa(velocidades, CAR_A, CAR_B)
        if velocidade_relativa is not None:
            plt.text((car_a_x + car_b_x) / 2, (car_a_y + car_b_y) / 2, f'{velocidade_relativa:.2f} m/s', fontsize=12, color='darkred')

    # Adiciona rótulos aos eixos
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title('Neighboring cars')
    plt.legend()

# Criação do gráfico inicial
fig = plt.figure()
ani = animation.FuncAnimation(fig, atualizar_grafico, interval=1000)  # Intervalo em milissegundos (1 segundo)
plt.show()


import matplotlib.pyplot as plt
import matplotlib.animation as animation
import math
import time
import os

# Função para ler as coordenadas do arquivo
def ler_coordenadas():
    x = []
    y = []
    legendas = []
    
    if os.path.getsize("coordinates.txt") == 0:  # Verifica se o arquivo está vazio
        return x, y, legendas
    
    with open("coordinates.txt", 'r') as arquivo:
        for linha in arquivo:
            linha = linha.strip()
            if linha:
                coordenadas = linha.split()
                if len(coordenadas) == 3:
                    x.append(float(coordenadas[0]))
                    y.append(float(coordenadas[1]))
                    legendas.append(coordenadas[2])
    return x, y, legendas

# Função de atualização do gráfico
def atualizar_grafico(i):
    plt.clf()  # Limpa o gráfico anterior
    x, y, legendas = ler_coordenadas()
    
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
    
    # Cria o gráfico de dispersão para os pontos verdes, azuis e vermelhos, com suas respectivas legendas
    plt.scatter(posicao_x,  posicao_y,  label=f'My position',                 color='green', marker='d')
    plt.scatter(azul_x,     azul_y,     label='Close to (-'+str(raio)+'m)',   color='blue', marker='o')
    plt.scatter(vermelho_x, vermelho_y, label='Far (+'+str(raio)+'m)',        color='red', marker='x')
    
    for j in range(len(azul_x)):
        plt.annotate(f'({azul_legendas[j]})', (azul_x[j], azul_y[j]), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='blue')
    
    for j in range(len(vermelho_x)):
        plt.annotate(f'({vermelho_legendas[j]})', (vermelho_x[j], vermelho_y[j]), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='red')
    
    plt.annotate(f'({legendas[0]})', (posicao_x, posicao_y), textcoords="offset points", xytext=(0, 10), ha='center', fontsize=8, color='green')
    
    # Adiciona rótulos aos eixos
    plt.xlabel('X Coordinate')
    plt.ylabel('Y Coordinate')
    plt.title('Neighboring cars')
    plt.legend()

# Criação do gráfico inicial
fig = plt.figure()
ani = animation.FuncAnimation(fig, atualizar_grafico, interval=1000)  # Intervalo em milissegundos (1 segundo)
plt.show()


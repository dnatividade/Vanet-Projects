# 008 The Telephone Game - CAR sends the message to its neighbor, which forwards it to the next neighbor, until it reaches the last vehicle ![projects-Veins](https://img.shields.io/badge/projects-Veins-blue)

>O veículo de de ID 16 (node[0]) envia uma ensagem para o proximo veiculo da fila, ID 22 (node[1]), que reencaminha essa mensagem para o proximo até chegar no último veículo da simulação.
Os nós permanecem retransmitindo a mensagem a cada 2 segundos até que o destino envie de volta uma confirmação de recebimento.
O endereço do nó vizinho é encontrado somando 6 em seu ID (esta é uma caracterisca do simulador).
Os veículos entram na via na cor vermelho e, ao receber a mensagem, mudam sua cor para verde, amarelo, azul ou branco. É feito um rodizio das cores, para cada veículo.
 
>Vehicle ID 16 (node[0]) sends a message to the next vehicle in the queue, ID 22 (node[1]), which forwards this message to the next one until reaching the last vehicle in the simulation.
The nodes continue to retransmit the message every 2 seconds until the destination sends back an acknowledgment.
The neighboring node's address is found by adding 6 to its ID (this is a simulator feature).
Vehicles enter the road in red and, upon receiving the message, change their color to green, yellow, blue or white. A color rotation is done for each vehicle.

![the-telephone-game](img/008.gif)
---

```
@dnat
```


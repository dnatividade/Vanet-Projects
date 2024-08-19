# 007 CAR send msg to another car via RSU ![projects-Veins](https://img.shields.io/badge/projects-Veins-blue)

>O veículo de ID 16 (node[0]) quer enviar uma mensagem para o veículo de de ID 286 (node[45]), mas este ainda não entrou na via. Então, o primeiro veículo envia a mensagem para a RSU que retransmite para o segundo veículo.
Todos os nós permanecem enviando a mensagem a cada 2 segundos até que o destino envie de volta uma confirmação de recebimento.
 
>Vehicle ID 16 (node[0]) wants to send a message to vehicle ID 286 (node[45]), but this vehicle has not yet entered the lane. Then, the first vehicle sends the message to the RSU which relays it to the second vehicle.
All nodes continue sending the message every 2 seconds until the destination sends back an acknowledgment.
---

```
@dnat
```


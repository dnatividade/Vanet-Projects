# 006 RSU send msg via "fake" multicast ![projects-Veins](https://img.shields.io/badge/projects-Veins-blue)

>A RSU envia mensagens via broadcast, mas apenas os veículos selecionados processam a menssagem. Foi criado na mensagem, um campo do tipo string chamada multicastAddr, no qual é enviado varios IDs de veículos separados por ';'. Quando o veículo recebe a mensagem, ele verifica se o seu ID está na lista, caso positivo um circulo verde será colocado em volta do veículo.
 
>The RSU sends messages via broadcast, but only selected vehicles process the message. A string field called multicastAddr was created in the message, in which several vehicle IDs separated by ';' are sent. Upon receiving the message, the vehicle checks whether its ID is on the list, if so, a green circle will be placed around the vehicle.
---

```
@dnat
```


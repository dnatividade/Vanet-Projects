//obtém uma lista com todas as vias que o veículo ira passar

//cria uma lista de strings
std::list<std::string> routeIDs;
//limpa a lista criada
routeIDs.clear();
//obtem a rota do veículo
routeIDs = traciVehicle->getPlannedRoadIds();


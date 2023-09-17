//@dnat
// Get a list of all roads the vehicle will travel on
std::list<std::string> routeIDs; //create string list
routeIDs.clear(); //clear list
routeIDs = traciVehicle->getPlannedRoadIds(); //get vehicle route


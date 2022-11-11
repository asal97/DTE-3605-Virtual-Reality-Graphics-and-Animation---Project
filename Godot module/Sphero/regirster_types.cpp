/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "Sphero.h"

void register_Sphero_types() {
	ClassDB::register_class<Sphero>();
}

void unregister_Sphero_types() {
	//Nothing to do here in this example.
}

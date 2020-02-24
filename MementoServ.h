#pragma once
#include "Memento.h"
#include <fstream>
class MementoServ
{
	Memento memento;
public:
	void save(const Composite& composite) {
		composite.set_memento(memento);
	}
	void load(Composite& composite) {
		composite.get_memento(memento);
	}

	void save_to_file(Composite& composite)
	{
		composite.save_to_file(memento);
	}
};


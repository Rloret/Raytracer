#pragma once

#include "Collidable.h"

class Collidable_List : public ICollidable {
public:
	Collidable_List() {};
	Collidable_List(ICollidable** list, int size) {
		this->List = list;
		this->Size = size;
	}

	virtual bool IntersectedBy(const Ray& r, float min, float max, HitInformation& hitInfo) override {
		HitInformation auxiliar_hitinfo;
		bool hitanything = false;
		double closest_yet = max;

		for (int i = 0; i < Size; i++)
		{
			if (List[i]->IntersectedBy(r, min, closest_yet, auxiliar_hitinfo)) {
				hitanything = true;
				if (auxiliar_hitinfo.t < closest_yet) {
					closest_yet = auxiliar_hitinfo.t;
					hitInfo = auxiliar_hitinfo;
				}
			}
		}
		return hitanything;
	}

	ICollidable** List;
	int Size;
};

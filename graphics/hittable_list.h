//
// Created by Oliver Zhang on 2021-01-16.
//

#ifndef PATHTRACED_FLIGHT_SIM_HITTABLE_LIST_H
#define PATHTRACED_FLIGHT_SIM_HITTABLE_LIST_H


#include "hittable.h"

#include <memory>
#include <vector>

using std::shared_ptr;
using std::make_shared;

class HittableList : public Hittable {
public:
    HittableList() = default;

    explicit HittableList(const shared_ptr<Hittable> &object) { add(object); }

    void clear() { objects.clear(); }

    void add(const shared_ptr<Hittable> &object) { objects.push_back(object); }

    bool hit(const Ray3d &r, double t_min, double t_max, HitRecord &rec) const override;

public:
    std::vector<shared_ptr<Hittable>> objects;
};



#endif //PATHTRACED_FLIGHT_SIM_HITTABLE_LIST_H

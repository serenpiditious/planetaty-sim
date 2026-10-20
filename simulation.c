#include <raylib.h>
#include <raymath.h>
#include "./include/simulation.h"

void updatePlanetHistory(Planet *planet){
        for (int i = TRAIL_SIZE - 1 ; i > 0 ;i--){
                planet->history[i] = planet->history[i - 1];
        }
        planet->history[0] = planet->position;
}
// scales vector dir by scale
Vector3 scaleAndAdd(Vector3 vec, Vector3 dir, float scale){
    return Vector3Add(vec, Vector3Scale(dir, scale));
}

// collision formula from newtonian mechanics
float collision_vel(float u1, float u2, float mass1, float mass2, float e){
    return ((mass1 - e * mass2) * u1 + (1 + e) * mass2 * u2) / (mass1 + mass2);
}

// calculates vector acceleration of curr_planet
void update_acc(Planet* curr_planet, Planet* planets, int planet_num){
    Planet planet;
    Vector3 dir_vector;
    float dist;
    float force;
    Vector3 acc = (Vector3) {0.0f, 0.0f, 0.0f};
    for (int i = 0; i < planet_num; i++){
        if (curr_planet != planets + i){
            planet = planets[i];
            // points from curr_planet to planet
            dir_vector = Vector3Subtract(planet.position, curr_planet -> position);
            dist = Vector3Length(dir_vector);
            force = (G * planet.mass) / (dist * dist);
            acc = scaleAndAdd(acc, Vector3Normalize(dir_vector), force);
        }
    }
    curr_planet->acceleration = acc;
}

// updates vel first, then pos of planet
void update_pos_vel(Planet* planet, float deltaTime){
    planet->velocity = scaleAndAdd(planet->velocity, planet->acceleration, deltaTime);
    planet->position = scaleAndAdd(planet->position, planet->velocity, deltaTime);
}

// sets positions of pro and bono so they don't overlap, and calculates their new velocities
void collision(Planet *pro, Planet *bono, float e){
    // points from pro to bono
    Vector3 unit_dir = Vector3Normalize(Vector3Subtract(bono->position, pro->position));
    bono->position = scaleAndAdd(pro->position, unit_dir, pro->radius + bono->radius);

    // velocity along normal
    float u_pro = Vector3DotProduct(pro->velocity, unit_dir);
    float u_bono = Vector3DotProduct(bono->velocity, unit_dir);

    // velocity along tangent
    Vector3 perp_pro = scaleAndAdd(pro->velocity, unit_dir, - u_pro);
    Vector3 perp_bono = scaleAndAdd(bono->velocity, unit_dir, - u_bono);

    //velocity after collision along normal
    float v_pro = collision_vel(u_pro, u_bono, pro->mass, bono->mass, e);
    float v_bono = collision_vel(u_bono, u_pro, bono->mass, pro->mass, e);

    pro->velocity = scaleAndAdd(perp_pro, unit_dir, v_pro);
    bono->velocity = scaleAndAdd(perp_bono, unit_dir, v_bono);
}

// updates acc, vel, pos and checks for collisions
void physics(SimState *state, float e){
    int planet_num =state->planet_num;
    Planet *planets = state->planets;
    float deltaTime = state->deltaTime;

    for (int i = 0; i < state->planet_num; i++){
        Planet *curr_planet = planets + i;
        update_acc(curr_planet, planets, planet_num);
        // printf("%f,%f,%f",plan_list[i].velocity.x, plan_list[i].velocity.y, plan_list[i].velocity.z);
    }

    for (int i = 0; i < planet_num; i++){
        Planet *curr_planet = planets + i;
        update_pos_vel(curr_planet, deltaTime);
		updatePlanetHistory(state->planets + i);

        // printf("%f,%f,%f",plan_list[i].velocity.x, plan_list[i].velocity.y, plan_list[i].velocity.z);

        // checks if two planets are colliding
        for (int j = i; j < planet_num; j++){
            float min_dist = curr_planet -> radius + planets[j].radius;
            if (Vector3Distance(curr_planet -> position, planets[j].position) <= min_dist){
                collision(curr_planet, planets + j, e);
            }
        }
	}
    state->planets = planets;
}

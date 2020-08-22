#include <api.h>

void Reference_get_ref() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_ref_after_add() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_add(world, e, Velocity);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_ref_after_remove() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    ecs_add(world, e, Velocity);
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_remove(world, e, Velocity);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_ref_after_delete() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t dummy = ecs_new(world, Position);
    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_delete(world, dummy);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_ref_after_realloc() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_dim_type(world, ecs_type(Position), 1000);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_ref_staged() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_staging_begin(world);

    ecs_set(world, e, Position, {30, 40});

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 30);
    test_int(p->y, 40);

    ecs_staging_end(world, false);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 30);
    test_int(p->y, 40);

    ecs_fini(world);
}

void Reference_get_ref_after_new_in_stage() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_staging_begin(world);

    ecs_new(world, Position);

    ecs_set(world, e, Position, {30, 40});

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 30);
    test_int(p->y, 40);

    ecs_staging_end(world, false);

    p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 30);
    test_int(p->y, 40);

    ecs_fini(world);
}

void Reference_get_ref_monitored() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_set(world, 0, Position, {10, 20});
    ecs_new_w_entity(world, ECS_CHILDOF | e);
    
    ecs_ref_t ref = {0};
    const Position *p = ecs_get_ref(world, &ref, e, Position);
    test_assert(p != NULL);
    test_int(p->x, 10);
    test_int(p->y, 20);

    ecs_fini(world);
}

void Reference_get_nonexisting() {
    ecs_world_t *world = ecs_init();

    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);

    ecs_entity_t e = ecs_new(world, Position);
    
    ecs_ref_t ref = {0};
    const Velocity *p = ecs_get_ref(world, &ref, e, Velocity);
    test_assert(p == NULL);

    ecs_fini(world);
}

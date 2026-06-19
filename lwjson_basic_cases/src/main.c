// create json with array, string, bollean data -- form
//  with error handling
// output:
//  {"first_array":[10,20,30],"second_array":[100,200,300],"device":"STM32","enabled":true}

#include "lwjson/lwjson.h"
#include <stdio.h>

int main(void) {

    const char* json =
        "{\"first_array\":[10,20,30],"
        "\"second_array\":[100,200,300],"
        "\"device\":\"STM32\","
        "\"val_p\":56,"
        "\"enabled\":true}";

    lwjson_t lw;
    lwjson_token_t tokens[32];

    lwjson_init(&lw, tokens, 32);

    if (lwjson_parse(&lw, json) != lwjsonOK) {
        printf("Parse failed\n");
        return -1;
    }

    /* device */
    const lwjson_token_t* t;

    t = lwjson_find(&lw, "device");
    if (t != NULL && t->type == LWJSON_TYPE_STRING) {
        printf("device = %.*s\n",
               (int)t->u.str.token_value_len,
               t->u.str.token_value);
    }

    /* val_p */
    t = lwjson_find(&lw, "val_p");
    if (t != NULL && t->type == LWJSON_TYPE_NUM_INT) {
        printf("val_p = %u\n",
               (uint32_t)t->u.num_int);
    }

    /* enabled */
    t = lwjson_find(&lw, "enabled");
    if (t != NULL) {
        if (t->type == LWJSON_TYPE_TRUE) {
            printf("enabled = true\n");
        } else if (t->type == LWJSON_TYPE_FALSE) {
            printf("enabled = false\n");
        }
    }

    /* first_array */
    int first_array[3];

    const lwjson_token_t* arr;

    arr = lwjson_find(&lw, "first_array");

    if (arr != NULL && arr->type == LWJSON_TYPE_ARRAY) {

        const lwjson_token_t* item = arr->u.first_child;

        for (int i = 0; i < 3 && item != NULL; i++) {

            first_array[i] = item->u.num_int;

            item = item->next;
        }

        printf("first_array = %d %d %d\n",
               first_array[0],
               first_array[1],
               first_array[2]);
    }

    /* second_array */
    int second_array[3];

    arr = lwjson_find(&lw, "second_array");

    if (arr != NULL && arr->type == LWJSON_TYPE_ARRAY) {

        const lwjson_token_t* item = arr->u.first_child;

        for (int i = 0; i < 3 && item != NULL; i++) {

            second_array[i] = item->u.num_int;

            item = item->next;
        }

        printf("second_array = %d %d %d\n",
               second_array[0],
               second_array[1],
               second_array[2]);
    }

    lwjson_free(&lw);

    return 0;
}

/*
You can also access a specific array element using lwjson_find():

t = lwjson_find(&lw, "first_array.#0"); // 10
t = lwjson_find(&lw, "first_array.#1"); // 20
t = lwjson_find(&lw, "first_array.#2"); // 30
printf("%lld\n", t->u.num_int);

*/

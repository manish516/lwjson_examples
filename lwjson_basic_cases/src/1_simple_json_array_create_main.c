// create json in array form
// output:
// --> {"first_array":[10,20,30],"second_array":[10,20,30]}

#include "lwjson/lwjson.h"
#include "lwjson/lwjson_serializer.h"
#include <stdio.h>
#include <string.h>

int main() {
  // json init
  char json[256];

  lwjson_serializer_t ser;
  lwjson_serializer_init(&ser, json, sizeof(json));
  lwjson_serializer_start_object(&ser, NULL, 0);
  //====== full json structure begin

  // first array
  lwjson_serializer_start_array(&ser, "first_array", strlen("first_array"));
  lwjson_serializer_add_int(&ser, NULL, 0, 10);
  lwjson_serializer_add_int(&ser, NULL, 0, 20);
  lwjson_serializer_add_int(&ser, NULL, 0, 30);
  lwjson_serializer_end_array(&ser);

  // 2nd array
  lwjson_serializer_start_array(&ser, "second_array", strlen("second_array"));
  lwjson_serializer_add_int(&ser, NULL, 0, 10);
  lwjson_serializer_add_int(&ser, NULL, 0, 20);
  lwjson_serializer_add_int(&ser, NULL, 0, 60);
  lwjson_serializer_end_array(&ser);

  //======= full json structure end

  lwjson_serializer_end_object(&ser);

  printf("%s", json);
}

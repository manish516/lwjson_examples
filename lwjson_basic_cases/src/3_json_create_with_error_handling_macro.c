// create json with array, string, bollean data -- form
//  with error handling
// output:
//  {"first_array":[10,20,30],"second_array":[100,200,300],"device":"STM32","enabled":true}

#include "lwjson/lwjson.h"
#include "lwjson/lwjson_serializer.h"

#include <stdio.h>
#include <string.h>

#define JSON_BUF_SIZE 256
// #define JSON_BUF_SIZE 2

#define CHECK(x)                   \
  do {                             \
    if ((res = (x)) != lwjsonOK)   \
      goto error;                  \
  } while (0)

int main(void) {
  char json[JSON_BUF_SIZE];
  size_t len = 0;

  lwjsonr_t res;
  lwjson_serializer_t ser;

  /* Initialize serializer */
  CHECK(lwjson_serializer_init(&ser, json, sizeof(json)));

  /* Root object */
  CHECK(lwjson_serializer_start_object(&ser, NULL, 0));

  /* first_array */
  CHECK(lwjson_serializer_start_array(&ser, "first_array", strlen("first_array")));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 10));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 20));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 30));
  CHECK(lwjson_serializer_end_array(&ser));

  /* second_array */
  CHECK(lwjson_serializer_start_array(&ser, "second_array", strlen("second_array")));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 100));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 200));
  CHECK(lwjson_serializer_add_int(&ser, NULL, 0, 300));
  CHECK(lwjson_serializer_end_array(&ser));
  /* Add some normal fields */
  CHECK(lwjson_serializer_add_string(&ser, "device", strlen("device"), "STM32", strlen("STM32")));
  CHECK(lwjson_serializer_add_bool(&ser, "enabled", strlen("enabled"), 1));

  /* End root object */
  CHECK(lwjson_serializer_end_object(&ser));

  /* Finalize -- getting final len value of json*/
  CHECK(lwjson_serializer_finalize(&ser, &len));

  /* Add terminating NULL */
  if (len >= sizeof(json)) {
    printf("Buffer too small for terminator\n");
    return -1;
  }

  json[len] = '\0';

  printf("JSON length = %zu\n", len);
  printf("%s\n", json);

  return 0;

error:
  if (res == lwjsonERRBUF) {
    printf("ERROR: JSON buffer too small\n");
  } else {
    printf("ERROR: lwjson error = %d\n", res);
  }
  return -1;
}

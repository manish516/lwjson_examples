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

int main(void) {
  char json[JSON_BUF_SIZE];
  size_t len = 0;

  lwjsonr_t res;
  lwjson_serializer_t ser;

  /* Initialize serializer */
  res = lwjson_serializer_init(&ser, json, sizeof(json));
  if (res != lwjsonOK) {
    printf("Init failed\n");
    return -1;
  }

  /* Root object */
  res = lwjson_serializer_start_object(&ser, NULL, 0);
  if (res != lwjsonOK)
    goto error;

  /* first_array */
  res = lwjson_serializer_start_array(&ser, "first_array", strlen("first_array"));
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 10);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 20);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 30);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_end_array(&ser);
  if (res != lwjsonOK)
    goto error;

  /* second_array */
  res = lwjson_serializer_start_array(&ser, "second_array", strlen("second_array"));
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 100);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 200);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_int(&ser, NULL, 0, 300);
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_end_array(&ser);
  if (res != lwjsonOK)
    goto error;

  /* Add some normal fields */
  res = lwjson_serializer_add_string(&ser, "device", strlen("device"), "STM32", strlen("STM32"));
  if (res != lwjsonOK)
    goto error;

  res = lwjson_serializer_add_bool(&ser, "enabled", strlen("enabled"), 1);
  if (res != lwjsonOK)
    goto error;

  /* End root object */
  res = lwjson_serializer_end_object(&ser);
  if (res != lwjsonOK)
    goto error;

  /* Finalize -- getting final len value of json*/
  res = lwjson_serializer_finalize(&ser, &len);
  if (res != lwjsonOK)
    goto error;

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

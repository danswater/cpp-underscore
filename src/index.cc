#include <nan.h>
#include "Underscore.h"

NAN_MODULE_INIT(InitModule) {
  Underscore::Init(target);
}

NODE_MODULE(myModule, InitModule);
#include <nan.h>

class Underscore : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  static NAN_METHOD(New);
  static NAN_METHOD(Map);

  static Nan::Persistent<v8::FunctionTemplate> constructor;
};
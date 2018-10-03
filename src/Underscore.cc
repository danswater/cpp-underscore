#include "Underscore.h"

Nan::Persistent<v8::FunctionTemplate> Underscore::constructor;

NAN_MODULE_INIT(Underscore::Init) {
  v8::Local<v8::FunctionTemplate> ctor = Nan::New<v8::FunctionTemplate>(Underscore::New);
  constructor.Reset(ctor);
  ctor->InstanceTemplate()->SetInternalFieldCount(1);
  ctor->SetClassName(Nan::New("Underscore").ToLocalChecked());

  Nan::SetPrototypeMethod(ctor, "map", Map);

  target->Set(Nan::New("Underscore").ToLocalChecked(), ctor->GetFunction());
}

NAN_METHOD(Underscore::New) {
  Underscore* underscore = new Underscore();
  underscore->Wrap(info.Holder());

  info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(Underscore::Map) {
  if (!info[1]->IsFunction()) {
    return Nan::ThrowError(Nan::New("Underscore::Map - expected second arg to be a function").ToLocalChecked());
  }

  v8::Local<v8::Array> jsArr = v8::Local<v8::Array>::Cast(info[0]);
  if (!info[0]->IsArray() || jsArr->Length() == 0) {
    v8::Local<v8::Array> empty = Nan::New<v8::Array>(0);
    return info.GetReturnValue().Set(empty);
  }

  v8::Local<v8::Function> cbFunc = v8::Local<v8::Function>::Cast(info[1]);
  Nan::Callback *callback = new Nan::Callback(cbFunc);

  std::vector<v8::Local<v8::Value>> vec;
  for (unsigned int i = 0; i < jsArr->Length(); i++) {
    v8::Local<v8::Value> jsElement = jsArr->Get(i);
    vec.push_back(jsElement);
  }

  v8::Local<v8::Array> jsArr2 = Nan::New<v8::Array>(vec.size());
  for (unsigned int i = 0; i < jsArr2->Length(); i++) {
    v8::Local<v8::Value> object = vec.at(i);
    v8::Local<v8::Value> argv[1];
    argv[0] = object;
    
    Nan::AsyncResource resource("underscore::map");
    v8::Local<v8::Value> cbResult = callback->Call(1, argv, &resource).ToLocalChecked();
        
    jsArr->Set(i, cbResult);
  }

  info.GetReturnValue().Set(jsArr);
}
#define _DEFAULT_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <fcntl.h>

#include "napi.h"

Napi::Value PipeSync(const Napi::CallbackInfo& args)
{
	Napi::Env env = args.Env();

    int pipefd[2];
	if (pipe(pipefd) != 0) {
		Napi::TypeError::New(env, std::string("pipe():") + strerror(errno)).ThrowAsJavaScriptException();

		return env.Undefined();
	}
    if (fcntl(pipefd[0], F_SETFD, FD_CLOEXEC) != 0) {
		Napi::TypeError::New(env, std::string("fcntl():") + strerror(errno)).ThrowAsJavaScriptException();

		return env.Undefined();
    }
    if (fcntl(pipefd[1], F_SETFD, FD_CLOEXEC) != 0) {
		Napi::TypeError::New(env, std::string("fcntl():") + strerror(errno)).ThrowAsJavaScriptException();

		return env.Undefined();
    }
    Napi::Object obj = Napi::Object::New(env);
    obj.Set("readfd", pipefd[0]);
    obj.Set("writefd", pipefd[1]);
	return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
	exports.Set(Napi::String::New(env, "pipeSync"), Napi::Function::New(env, PipeSync));

	return exports;
}

NODE_API_MODULE(pipe, Init);

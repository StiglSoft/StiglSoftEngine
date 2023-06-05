#include <iostream>
#include <vector>
#include <string>
#include <dlfcn.h>
#include "file.cpp"
#include "../stigengine.h"

void* loadDynamicLibrary(const std::string& filename) {
    void* libraryHandle = dlopen(filename.c_str(), RTLD_LAZY);
    if (!libraryHandle)
        err(-1,"Failed to load the script: %s, %s",filename, dlerror());
    return libraryHandle;
}
vector<void*> loadScripts(){
    vector<void*> scripts;
    for(string s : getFilesInDirectory("./","so")){
        std::cout << "Loading script: " << s << std::endl;
        void* script = loadDynamicLibrary(s);
        scripts.push_back(script);
    }
    return scripts;
}
void ExecuteUpdates(vector<void*> handles){
    for(void* handle : handles){
        typedef void (*UpdateFunc)();
        UpdateFunc update = reinterpret_cast<UpdateFunc>(dlsym(handle, "update"));
        if (!update)continue;
        update();
    }
}
void ExecuteKeyboard(vector<void*> handles, char ch){
    for(void* handle : handles){
        typedef void (*KeyboardFunc)(char key);
        KeyboardFunc keyboard = reinterpret_cast<KeyboardFunc>(dlsym(handle, "keyboard"));
        if (!keyboard)continue;
        keyboard(ch);
    }
}
void ExecuteStartups(vector<void*> handles, ScriptData* sd){
    for(void* handle : handles){
        typedef void (*StartupFunc)(ScriptData* sd);
        StartupFunc startup = reinterpret_cast<StartupFunc>(dlsym(handle, "start"));
        if (!startup)continue;
        startup(sd);
    }
}
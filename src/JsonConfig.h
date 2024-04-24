#ifndef JsonConfig_h
#define JsonConfig_h
#include <Arduino.h>
#include "FS.h"
#include "FFat.h"

#include <ArduinoJson.h>

class JsonConfig
{
public:
    JsonConfig();
    void begin(const char *filename);
    void save();
    void load();
    void set(const char *key, const char *value);
    void set(const char *key, int value);
    void set(const char *key, float value);
    void set(const char *key, bool value);
    void setDetectType(const char *key, const char *value);
    const char *get(const char *key);
    int getInt(const char *key);
    float getFloat(const char *key);
    bool getBool(const char *key);
    bool exists(const char *key);
    void remove(const char *key);
    void setIfNotExists(const char *key, const char *value);
    void setIfNotExists(const char *key, int value);
    void setIfNotExists(const char *key, float value);
    void setIfNotExists(const char *key, bool value);
    // return the json string
    String toString();
    void clear();
    DynamicJsonDocument &getDoc();
    void loadJson(DynamicJsonDocument &jsonDoc);
    void loadJson(String jsonString);

private:
    const char *_filename;
    DynamicJsonDocument _doc;
};

#endif

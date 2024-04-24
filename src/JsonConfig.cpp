#include <JsonConfig.h>

// Path: lib/JsonConfig/JsonConfig.cpp

JsonConfig::JsonConfig() : _doc(1024) // Initialize _doc with a size of 1024
{
}

void JsonConfig::begin(const char *filename)
{
    _filename = filename;
    if (!FFat.begin(true))
    {
        Serial.println("FFat Mount Failed");
        return;
    }
    if (!FFat.exists(_filename))
    {
        save();
    }
    load();
}

void JsonConfig::save()
{
    if (!FFat.begin(true))
    {
        Serial.println("FFat Mount Failed");
        return;
    }
    File file = FFat.open(_filename, "w");
    if (!file)
    {
        Serial.println("Failed to open file for writing");
        return;
    }
    serializeJson(_doc, file);
    file.close();
}

DynamicJsonDocument &JsonConfig::getDoc()
{
    return _doc;
}

void JsonConfig::load()
{
    File file = FFat.open(_filename, "r");
    if (!file)
    {
        Serial.println("Failed to open file for reading");
        return;
    }
    deserializeJson(_doc, file);
    file.close();
}

void JsonConfig::set(const char *key, const char *value)
{
    _doc[key] = value;
}

void JsonConfig::set(const char *key, int value)
{
    _doc[key] = value;
}

void JsonConfig::set(const char *key, float value)
{
    _doc[key] = value;
}

void JsonConfig::set(const char *key, bool value)
{
    _doc[key] = value;
}

const char *JsonConfig::get(const char *key)
{
    return _doc[key];
}

int JsonConfig::getInt(const char *key)
{
    return _doc[key];
}

float JsonConfig::getFloat(const char *key)
{
    return _doc[key];
}

bool JsonConfig::getBool(const char *key)
{
    return _doc[key];
}

bool JsonConfig::exists(const char *key)
{
    return _doc.containsKey(key);
}

void JsonConfig::setIfNotExists(const char *key, const char *value)
{
    if (!exists(key))
    {
        set(key, value);
    }
}

void JsonConfig::setIfNotExists(const char *key, int value)
{
    if (!exists(key))
    {
        set(key, value);
    }
}

void JsonConfig::setIfNotExists(const char *key, float value)
{
    if (!exists(key))
    {
        set(key, value);
    }
}

String JsonConfig::toString()
{
    String output;
    serializeJson(_doc, output);
    return output;
}

void JsonConfig::setIfNotExists(const char *key, bool value)
{
    if (!exists(key))
    {
        set(key, value);
    }
}

void JsonConfig::remove(const char *key)
{
    _doc.remove(key);
}

void JsonConfig::clear()
{
    _doc.clear();
}

void JsonConfig::loadJson(DynamicJsonDocument &jsonDoc)
{

    // Iterate through the JSON object and set key-value pairs
    JsonObject jsonObject = jsonDoc.as<JsonObject>();
    for (JsonPair keyValue : jsonObject)
    {
        // check the type of the value
        if (keyValue.value().is<int>())
        {
            int value = keyValue.value().as<int>();
            const char *key = keyValue.key().c_str();
            String output = "Setting ";
            output += key;
            output += " to ";
            output += value;

            set(key, value);
        }
        else if (keyValue.value().is<bool>())
        {
            bool value = keyValue.value().as<bool>();
            const char *key = keyValue.key().c_str();
            String output = "Setting ";
            output += key;
            output += " to ";
            output += value;

            set(key, value);
        }

        else if (keyValue.value().is<float>())
        {
            float value = keyValue.value().as<float>();
            const char *key = keyValue.key().c_str();
            String output = "Setting ";
            output += key;
            output += " to ";
            output += value;

            set(key, value);
        }
        else if (keyValue.value().is<const char *>())
        {
            const char *value = keyValue.value().as<const char *>();
            const char *key = keyValue.key().c_str();
            String output = "Setting ";
            output += key;
            output += " to ";
            output += value;

            set(key, value);
        }
    }
    save();
}

void JsonConfig::loadJson(String jsonString)
{
    DynamicJsonDocument jsonDoc(1024);
    deserializeJson(jsonDoc, jsonString);
    loadJson(jsonDoc);
}

void JsonConfig::setDetectType(const char *key, const char *value)
{
    bool isDigit = true;
    for (int i = 0; value[i] != '\0'; i++)
    {
        if (!isdigit(value[i]))
        {
            isDigit = false;
            break;
        }
    }

    if (isDigit)
    {
        set(key, atoi(value));
    }
    else if (value[0] == 't' || value[0] == 'f')
    {
        set(key, value[0] == 't');
    }
    else
    {
        set(key, value);
    }
}
/* 
 * File:   Settings.h
 * Author: Richard Greene
 *
 * Handles storage, retrieval, and reset of settings.
 * 
 * Created on June 4, 2014, 12:34 PM
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#include <string>
#include <map>

#include <boost/property_tree/ptree.hpp>

#include <Logger.h>

#define SETTINGS (PrinterSettings::Instance())

/// The class that handles configuration and print options
class Settings 
{
public:
    Settings(std::string path);
    virtual ~Settings();
    void Load(const std::string &filename);
    void Save(const std::string &filename);
    void Save();
    void RestoreAll();
    void Restore(const std::string key);
    void Refresh();
    void Set(const std::string key, const std::string value);
    int GetInt(const std::string key);
    std::string GetString(const char* key);
    double GetDouble(const std::string key);
    bool GetBool(const std::string key);
    void SetErrorHandler(IErrorHandler* handler) { _errorHandler = handler; }
    
protected:
    // don't allow construction without supplying file name
    Settings();
    boost::property_tree::ptree _settingsTree;
    std::string _settingsPath;
    std::map<std::string, std::string> _defaultsMap;
    IErrorHandler* _errorHandler;
};

/// Singleton for sharing settings among all components
class PrinterSettings : public Settings
{
public:
    static Settings& Instance();
    
private:
    PrinterSettings();
    PrinterSettings(std::string path);
    PrinterSettings(PrinterSettings const&);
    PrinterSettings& operator=(PrinterSettings const&);
    ~PrinterSettings();
};
#endif	/* SETTINGS_H */


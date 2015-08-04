#pragma once
#include <ofMain.h>

class ksFileLoader
{
    
public:
    // [construction]
    ksFileLoader();
    ~ksFileLoader();

    // [function]
    void init();
    void loadFile(string filePath);
    
    string getName(int i);
    string getBaseName(int i);
    string getExtension(int i);
    float getSize(int i);
    
    int countFiles();
	
	ofFile& getFile(int i);
	vector<ofFile>& getFiles();
private:
    ofDirectory directory;
    vector<ofFile> files;
    
private:
    // [properities]
    vector<string> fileNames;
    vector<string> fileBaseNames;
    vector<string> fileExtension;
    vector<float> fileSizes;
    
};

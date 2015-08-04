#include <ks/utility/ksFileLoader.h>
#include <ks/utility/ksLog.h>

#ifndef KS_FILELOADER_DEBUG 
//#define KS_FILELOADER_DEBUG
#endif

ksFileLoader::ksFileLoader(){
    directory.listDir("");
    directory.sort(); // in linux the file system doesn't return file lists ordered in alphabetical order
    
    //allocate the vector to have as many ofImages as files
    if( directory.size() ){
        files.assign(directory.size(), ofFile());
    }
}

ksFileLoader::~ksFileLoader(){

}

void ksFileLoader::init(){


	cout<<"init successfully! \n";

}



void ksFileLoader::loadFile(string filePath){

    files.clear();
    fileNames.clear();
    fileBaseNames.clear();
    fileExtension.clear();
    fileSizes.clear();
    
    directory.listDir(filePath);
	directory.sort();

    files.assign(directory.size(), ofFile());
    
    if(!directory.size()){
		ksLog("Error: The directory %s is empty", filePath.c_str());
	}

	for (int i = 0; i < (int)directory.size(); ++i)
	{
		/* code */
//		cout<<"File num : " <<i<<endl;
//		cout<<"   getPath = "<<directory.getPath(i)<<endl;

		ofFile tempFile(directory.getPath(i));
        string tempFileName = tempFile.getFileName();
        string tempExtension = tempFile.getExtension();
        string tempFileBaseName = tempFile.getBaseName();
        float tempFileSize = tempFile.getSize()/1024/1024;
#ifdef KS_FILELOADER_DEBUG 
		cout<<"file Name: "<<tempFile.getFileName()<<endl;
		cout<<"file Size: "<<tempFile.getSize()<<endl;
#endif
		files.push_back(tempFile);
		fileNames.push_back(tempFileName);
        fileBaseNames.push_back(tempFileBaseName);
        fileExtension.push_back(tempExtension);
		fileSizes.push_back(tempFileSize);

		//files.push_back(tempFile);
	}

#ifdef KS_FILELOADER_DEBUG 
	//    cout<<"directory file[0] Name: " << directory.getFile(1).getFileName()<<endl;
	cout<<endl<<endl<<"directory Size: "<<directory.getFiles().size()<<endl;
#endif


}

string ksFileLoader::getName(int i){
	return fileNames[i];
} 

float ksFileLoader::getSize(int i){
	return fileSizes[i];

}

string ksFileLoader::getExtension(int i)
{
    return fileExtension[i];
}

string ksFileLoader::getBaseName(int i)
{
    return fileBaseNames[i];
}

int ksFileLoader::countFiles() {
    return directory.getFiles().size();
}

ofFile& ksFileLoader::getFile(int i)
{
	return files[i];
}

vector<ofFile>& ksFileLoader::getFiles()
{
	return files;
}

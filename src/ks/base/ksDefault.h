#ifndef KS_DEFAULT_H
#define KS_DEFAULT_H

#include <ofMain.h>

class ksResource;

class ksDefault
{
public:
	static ksDefault* getInstance();

private:
	// 不可删除 不可复制 不可自己创建实例
	ksDefault();
	ksDefault(const ksDefault&){}
	~ksDefault(){}
	ksDefault& operator=(const ksDefault& event) const{}

	void init();

	// 向资源中心添加默认配置资源
	ksResource* resources;
};

#endif
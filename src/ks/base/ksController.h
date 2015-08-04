#ifndef KS_CONTROLLER_H
#define KS_CONTROLLER_H

//xml
#include <ofXml.h>

#include <vector>
#include <ks/utility/ksSettings.h>

class ksBase;
class ksDefault;
class ksResource;

class ksController
{
public:
	static ksController* getInstance();

	// 根据脚本信息初始化ks列表
	void initKsLists();

	std::vector<ksBase*>& getKsLists();

	void add(ksBase* object);

	void setSelected(int index);

	ksBase *getSelected();

private:
	// 不可删除 不可复制 不可自己创建实例
	ksController();
	ksController(const ksController&){}
	~ksController(){}
	ksController& operator=(const ksController& event) const{}

    // 初始化指定类型万花筒资源
	void initKsResources(const char* ksName, ksBase* base);

	// 万花筒实例对象
	std::vector<ksBase*> ksLists;

	// 当前需要渲染的万花筒
	ksBase *selected;

	// 脚本文件读取
	ofXml xml;

	// 默认配置
	ksDefault *defaults;

    // 资源配置中心
    ksResource *resources;
};

#endif
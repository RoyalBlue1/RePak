#pragma once


struct RuiAssetHeader_v30_t {
	PagePtr_t name;
	PagePtr_t dataStructInitData;
	PagePtr_t transformData;
	float elementWidth;
	float elementHeight;
	float elementWidthRatio;
	float elementHeightRatio;
	PagePtr_t argNames;
	PagePtr_t argClusters;
	PagePtr_t args;
	short argumentCount; // number of slots for arguments. not all are used. has to be power of 2
	short mappingCount;
	uint16_t dataStructSize;
	uint16_t dataStructInitSize;
	uint16_t styleDescriptorCount;
	uint16_t unknown;
	uint16_t renderJobCount;
	uint16_t argClusterCount;
	PagePtr_t styleDescriptors;
	PagePtr_t renderJobData; 
	void* valueMappings; // maps values to others through linar/quadradic regression

};

